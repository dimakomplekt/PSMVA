// opencv_to_sdl.cpp

// =========================================================================================== IMPORT

#include "opencv_to_sdl.h"

// =========================================================================================== IMPORT


// Basic translator of the cv::Mat type to the SDL_Texture
// rescale passed sdl_texture and copy bitmap of Mat to the bitmam of SDL_Texture
void translate_cv_mat_to_sdl_texture(cv::Mat* cv_mat, SDL_Texture*& sdl_texture, SDL_Renderer* renderer)
{

    // 1. Check input

    if (cv_mat == nullptr || cv_mat->empty())
    {
        return; 
    }


    // 2. Get the sizes

    int width = cv_mat->cols;
    int height = cv_mat->rows;


    // 3. Convert color format. OpenCV uses BGR by default.
    // Translate it to the RGBA (or RGB, in dependence of sdl_texture)

    cv::Mat rgba_mat;

    if (cv_mat->channels() == 3) 
    {
        cv::cvtColor(*cv_mat, rgba_mat, cv::COLOR_BGR2BGRA);
    } 

    else if (cv_mat->channels() == 1) 
    {
        cv::cvtColor(*cv_mat, rgba_mat, cv::COLOR_GRAY2RGBA);
    } 

    else 
    {
        rgba_mat = *cv_mat; // 4 channels mode
    }


    // 4. Check sdl_texture - if there is no sdl_texture, or frame size have been changed - reallocate

    bool need_recreate = false;

    if (sdl_texture == nullptr)
    {
        need_recreate = true;
    } 
    else
    {
        float tex_w = 0.0f, tex_h = 0.0f;

        // Compare sizes
        if (SDL_GetTextureSize(sdl_texture, &tex_w, &tex_h)) 
        {
            // Need recreate
            if (static_cast<int>(tex_w) != width || static_cast<int>(tex_h) != height) 
            {
                SDL_DestroyTexture(sdl_texture);

                sdl_texture = nullptr;
                need_recreate = true;
            }
        }
    }

    if (need_recreate) 
    {
        sdl_texture = SDL_CreateTexture(

            renderer,
            SDL_PIXELFORMAT_RGBA8888,       // For format: cv::COLOR_BGR2BGRA
            SDL_TEXTUREACCESS_STREAMING,    // For texture renew with high frequency
            width,
            height

        );
        
        if (sdl_texture == nullptr)
        {
            SDL_Log("Can't create SDL texture: %s", SDL_GetError());
            return;
        }
    }

    if (!sdl_texture)
    {
        std::cout << SDL_GetError() << std::endl;
    }


    // Get ID of the texture properties
    SDL_PropertiesID props = SDL_GetTextureProperties(sdl_texture);

    if (props != 0)
    {
        SDL_PixelFormat format = static_cast<SDL_PixelFormat>(
            SDL_GetNumberProperty(
                props,
                SDL_PROP_TEXTURE_FORMAT_NUMBER,
                SDL_PIXELFORMAT_UNKNOWN));
    
        std::cout << SDL_GetPixelFormatName(format) << std::endl;
    }


    // 5. Copy pixels from cv::Mat to SDL_Texture

    void* texture_pixels = nullptr;
    int texture_pitch = 0;


    if (sdl_texture == nullptr)
    {
        std::cout << "Texture for translation is nullptr!" << std::endl;
    }


    // Block texture for write operation
    if (SDL_LockTexture(sdl_texture, nullptr, &texture_pixels, &texture_pitch))
    {
        SDL_ConvertPixels(
    
            width,
            height,
    
            // Equal to basic format of OpenCV
            SDL_PIXELFORMAT_BGR24,
            cv_mat->data,
            cv_mat->step,
    
            // Target basic format for SDL
            SDL_PIXELFORMAT_RGBA8888,
            texture_pixels,
            texture_pitch
    
        );
    
        SDL_UnlockTexture(sdl_texture);
    }
    else 
    {
        SDL_Log("Can't block the texture: %s", SDL_GetError());
    }

}
