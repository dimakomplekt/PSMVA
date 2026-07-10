// opencv_to_sdl.cpp

// =========================================================================================== IMPORT

#include "opencv_to_sdl.h"

// =========================================================================================== IMPORT


// Basic translator of the cv::Mat type to the SDL_Texture
// rescale passed sdl_texture and copy bitmap of Mat to the bitmam of SDL_Texture
void translate_cv_mat_to_sdl_texture(cv::Mat* cv_mat, SDL_Texture*& sdl_texture, SDL_Renderer* renderer)
{

    /**
     *
     * OPENCV CV::MAT TO SDL_TEXTURE TRANSLATION WORKFLOW
     * ============================================================================
     * This pipeline efficiently uploads 2D image data processed by OpenCV (CPU/RAM)
     * into an optimized SDL_Texture managed by the graphics driver (GPU/VRAM).
     *
     *
     * STEP 1: PARAMETER BINDING & API INPUTS
     *
     * - cv::Mat* cv_mat          : Passed via raw pointer to prevent heavy object copying.
     * - SDL_Texture*& sdl_texture: Passed as a reference to a pointer (*&). This allows
     *                              the function to directly allocate, destroy, or update
     *                              the original texture variable in the outer scope.
     * - SDL_Renderer* renderer   : The hardware rendering context tied to the GPU,
     *                              required to manage and allocate VRAM blocks.
     *
     *
     * STEP 2: PIPELINE PROTECTION (INPUT VALIDATION)
     *
     * - Checks if the pointer is null or if the matrix container is empty (e.g., failed
     *   camera frame capture or EOF). Safely returns early to prevent crash/segfault.
     *
     *
     * STEP 3: GEOMETRY EXTRACTION
     *
     * - Extracts image dimensions where 'cols' maps to width and 'rows' maps to height.
     *   These values define the explicit spatial configuration for the GPU texture.
     *
     *
     * STEP 4: ADAPTIVE VRAM LIFECYCLE MANAGEMENT (SMART RECYCLING)
     *
     * - First Frame/Null Check : If texture is null, triggers an allocation flag.
     * - Resolution Change Check: Uses SDL_GetTextureSize to check current VRAM bounds.
     *                            If user resizes the window or video stream changes resolution,
     *                            it calls SDL_DestroyTexture to free VRAM (preventing leaks),
     *                            sets pointer to null, and triggers reallocation.
     * - SDL_CreateTexture      : Allocates memory on GPU with two critical performance flags:
     *   -> SDL_PIXELFORMAT_RGBA8888  : Native, optimized 32-bit hardware format (4 bytes/pixel).
     *   -> SDL_TEXTUREACCESS_STREAMING: Tells the GPU driver that data changes every frame,
     *                                 optimizing the memory path for high-frequency updates.
     *
     *
     * STEP 5: BUS TRANSIT, COLOR ALIGNMENT & UNLOCK (THE TRANSIT LAYER)
     *
     * - SDL_LockTexture   : GPU memory is inaccessible to the CPU. Locking allocates a temporary
     *                       staging buffer in system RAM, returning 'texture_pixels' (write-pointer)
     *                       and 'texture_pitch' (the exact byte-length of a row including GPU padding).
     * - SDL_ConvertPixels : A highly optimized, hardware-accelerated memory blitter. It reads
     *                       directly from cv_mat->data using cv_mat->step (source pitch), maps the
     *                       native OpenCV color channel layout (e.g., BGR24) to the target format 
     *                       (RGBA8888), automatically flips color channels on the fly, fixes row 
     *                       alignment padding, and writes to the staging buffer.
     * - SDL_UnlockTexture : Locks off CPU access, flags the driver, and triggers a direct DMA 
     *                       transfer over the PCIe bus, committing raw pixels straight into VRAM.
     *
     */

    // 1. Check input

    if (cv_mat == nullptr || cv_mat->empty())
    {
        return; 
    }


    // 2. Get the sizes

    int width = cv_mat->cols;
    int height = cv_mat->rows;


    /*
    
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
    
    */

    // 3. Check sdl_texture - if there is no sdl_texture, or frame size have been changed - reallocate

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


    // 4. Copy pixels from cv::Mat to SDL_Texture

    void* texture_pixels = nullptr;
    int texture_pitch = 0;


    if (sdl_texture == nullptr)
    {
        std::cout << "Texture for translation is nullptr!" << std::endl;
    }


    /*
    
    // Block texture for write operation
    if (SDL_LockTexture(sdl_texture, nullptr, &texture_pixels, &texture_pitch))
    {
        SDL_ConvertPixels(
    
            width,
            height,
    
            // Equal to basic format of OpenCV
            SDL_PIXELFORMAT_ARGB8888
            rgba_mat.data,
            rgba_mat.step,
    
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
    
    */

    // Block texture
    if (SDL_LockTexture(sdl_texture, nullptr, &texture_pixels, &texture_pitch))
    {
        // Dynamic format check
        SDL_PixelFormat src_format = SDL_PIXELFORMAT_UNKNOWN;
        
        if (cv_mat->channels() == 3) src_format = SDL_PIXELFORMAT_BGR24;          // Default OpenCV color
        else if (cv_mat->channels() == 1) src_format = SDL_PIXELFORMAT_INDEX8;    // Specific (grayscale)
        else if (cv_mat->channels() == 4) src_format = SDL_PIXELFORMAT_BGRA32;    // Format with alpha

        
        SDL_ConvertPixels(
            
            width,
            height,
            
            src_format,                   // SDL format equal, which equal to current OpenCV format
            cv_mat->data,                 // Original data
            cv_mat->step,                 // Original step
            
            SDL_PIXELFORMAT_RGBA8888,     // Target format
            texture_pixels,               // Target pixels
            texture_pitch                 // Target pitch
            
        );
    
        SDL_UnlockTexture(sdl_texture);
    }

    else 
    {
        SDL_Log("Can't block the texture: %s", SDL_GetError());
    }

}
