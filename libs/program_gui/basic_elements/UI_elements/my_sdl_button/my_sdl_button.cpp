// my_sdl_button.cpp

// =========================================================================================== IMPORT

#include "my_sdl_button.h"


// =========================================================================================== IMPORT


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR

My_SDL_button::My_SDL_button()
{
    // Basic settings setter

    // Types

    this->click_access_type  = BUTTON_DEFAULT_CLICK_PERMISSION;

    this->set_gui_type(STATIC_BUTTON_GUI);


    // Callbacks nullptr

    this->extern_click_permission = {};
    this->on_hover = {};
    this->on_click = {};
    this->get_required_palette = {};

    // Data

    this->hovered = false;

    this->click_permission = true;
    this->clicked = false;
    this->clicked_tmp = false;

    this->push_mode_on = true;
    this->press_offset = 0;

    this->current_element_state = DEFAULT_BS;

    this->set_size(100, 50);

    this->x_render_point = this->width_size / 2;
    this->y_render_point = this->height_size / 2;

    this->reset_boundaries_points();
    

    this->border_width_size = 5;
    this->border_radius_size = 15;

    this->set_shadow_offset(5, -5);
    this->shadow_scale_factor = 1.0f;

    this->current_form = ROUNDED_RECTANGLE_EF;

    this->font_size = 12; 

    this->font_path = "C:/creator/it/programs/cpp/PSMVA/libs/program_gui/basic_elements/content/ttf_fonts/Amiga_forever_pro.ttf"; // Need another logic
    this->ttf_font_link = nullptr;

    this->content = "But";

    this->content_w = 0;
    this->content_h = 0;

    this->content_dirty = true;


    // ===== Default pallette =====

    this->set_opacity(255);


    // Базовые цвета
    this->set_background_color_1(hex_to_sdl_color("#fd3108", 255)); // #fd3108
    this->set_border_color_1({23, 23, 23, 255});    // #f0e7d6
    this->set_content_color_1({23, 23, 23, 255});
    this->set_shadow_color_1({230, 212, 42, 255});

    // Hover (наведение мыши)
    this->set_background_color_hovered_1({240, 231, 214, 255});
    this->set_border_color_hovered_1({23, 23, 23, 255});
    this->set_content_color_hovered_1({23, 23, 23, 255});
    this->set_shadow_color_hovered_1({220, 220, 200, 255});

    // Clicked (нажатие)
    this->set_background_color_clicked_1({150, 120, 180, 255}); 
    this->set_border_color_clicked_1({232, 222, 42, 255});
    this->set_content_color_clicked_1({232, 222, 42, 255});
    this->set_shadow_color_clicked_1({140, 122, 180, 255});


    // Nulled 2nd pallette
    this->set_background_color_2({0, 0, 0, 0});
    this->set_border_color_2({0, 0, 0, 0});
    this->set_content_color_2({0, 0, 0, 0});
    this->set_shadow_color_2({0, 0, 0, 0});

    this->set_background_color_hovered_2({0, 0, 0, 0});
    this->set_border_color_hovered_2({0, 0, 0, 0});
    this->set_content_color_hovered_2({0, 0, 0, 0});
    this->set_shadow_color_hovered_2({0, 0, 0, 0});

    this->set_background_color_clicked_2({0, 0, 0, 0});
    this->set_border_color_clicked_2({0, 0, 0, 0});
    this->set_content_color_clicked_2({0, 0, 0, 0});
    this->set_shadow_color_clicked_2({0, 0, 0, 0});


    this->current_pallette_number = 1;

    content_texture = nullptr;
}


My_SDL_button::~My_SDL_button()
{
    // TODO: Realization with panels linked list clear (both side registration) or just siple comment about 
    // destructor workflow rules - basic destructor from global space or My_SDL_panel.button_delete method
    // only for buttons inside panels

    // Textures destructors
    if (content_texture) SDL_DestroyTexture(content_texture);
}

// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR


// =========================================================================================== MAIN LOGIC

void My_SDL_button::update()
{
    // Hover check
    this->hover_check();

    // Hover logic
    if (this->hovered)
    {
        // Hover logic by the callback
        if (this->on_hover) this->on_hover();

        if (!this->clicked_tmp)
            this->current_element_state = HOVERED_BS;

        this->content_dirty = true; // For update

        // New click or release check  
        this->clicked = this->click_check();
    }
    else
    {
        // Clicked flags reset with hover ending (blocks the click logic without hovering)
        this->clicked = false;
        this->clicked_tmp = false; 

        if (!this->clicked_tmp) // Only without press
            this->current_element_state = DEFAULT_BS;
    }


    // Click with hover check with the click permission logic by the button access type


    if (this->click_access_type == BUTTON_DEFAULT_CLICK_PERMISSION)
        if (this->hovered && this->clicked)
            if (!this->clicked_tmp) 
            {
                this->clicked_tmp = true;

                this->current_element_state = CLICKED_BS;

                this->content_dirty = true; // For update
            }

    // There can not be anything instead of BUTTON_EXTERN_CLICK_PERMISSION
    else if (this->click_access_type == BUTTON_EXTERN_CLICK_PERMISSION)
    {
        // Permission check by the callback
        if (this->extern_click_permission)
        {
            this->click_permission = this->extern_click_permission();

            // Clicked logic by the callback if the permission obtained
            if (this->click_permission)
                if (this->hovered && this->clicked)
                    // Clicked logic by the callback
                    if (!this->clicked_tmp)
                    {
                        this->clicked_tmp = true;

                        this->current_element_state = CLICKED_BS;

                        this->content_dirty = true; // For update
                    }

            else
            {
                // Block repeats and reset
                this->clicked_tmp = false;
            }
        }
        else 
        {
            // Error handler
            std::cerr << "No callback for the button access status check! Click can't be handled!" << std::endl;
            return;
        }
    }

    // Pallette check callback 
    if (get_required_palette)
    {
        int new_pallette_number = get_required_palette();
            
        if (new_pallette_number != this->current_pallette_number)
        {
            this->current_pallette_choose(new_pallette_number);

            this->content_dirty = true; // For update
        }
    }

    // If we press and then release - reset permission
    if (!this->clicked && this->clicked_tmp) 
    {
        // One callback call after release
        if ((this->click_access_type == BUTTON_DEFAULT_CLICK_PERMISSION || this->click_permission)
        && this->on_click)
        {
            this->on_click();
        }


        // Block repeats and reset
        this->clicked_tmp = false;
        this->current_element_state = DEFAULT_BS; 
    }
}


void My_SDL_button::push_mode_switch()
{
    this->push_mode_on = !this->push_mode_on;
}


void My_SDL_button::set_access_type(button_access_type new_access_type)
{
    // Error handling for invalid access type
    if (new_access_type != BUTTON_DEFAULT_CLICK_PERMISSION && new_access_type != BUTTON_EXTERN_CLICK_PERMISSION)
    {
        std::cerr << "Invalid button access type. Access type not changed." << std::endl;
        return;
    }

    // New type setting
    else this->click_access_type = new_access_type;
}


void My_SDL_button::hover_check()
{
    // Compare element boundaries_points data with GI_mouse singleton current mouse position data

    int curr_x = static_cast<int>(std::round(App_mouse.get_x()));
    int curr_y = static_cast<int>(std::round(App_mouse.get_y()));

    
    if (curr_x >= this->boundaries_points.left_boundary &&
        curr_x <= this->boundaries_points.right_boundary &&
        curr_y <= this->boundaries_points.bottom_boundary &&
        curr_y >= this->boundaries_points.top_boundary) 
        
        // Mouse inside the element zone 
        this->hovered = true;
    
    else 

        // Mouse outside the element zone
        this->hovered = false;
}


bool My_SDL_button::click_check()
{
    // Click status by GI_mouse singleton
    return App_mouse.lb_clicked();
}


void My_SDL_button::reset_boundaries_points()
{
    this->boundaries_points.left_boundary = this->x_render_point - this->width_size / 2;
    this->boundaries_points.right_boundary = this->x_render_point + this->width_size / 2;
    this->boundaries_points.top_boundary = this->y_render_point - this->height_size / 2;
    this->boundaries_points.bottom_boundary = this->y_render_point + this->height_size / 2;
}


void My_SDL_button::reset_current_form()
{
    float half_w = this->width_size / 2.0f;
    float half_h = this->height_size / 2.0f;

    if (this->border_radius_size >= half_w && this->border_radius_size >= half_h)
        this->current_form = CIRCLE_EF;         

    else if (this->border_radius_size > 0)
        this->current_form = ROUNDED_RECTANGLE_EF; 
         
    else
        this->current_form = RECTANGLE_EF;           
}

// =========================================================================================== MAIN LOGIC



// =========================================================================================== GUI

// Main render method

void My_SDL_button::render(SDL_Renderer* renderer)
{
    // Local color variables for final rendering
    SDL_Color background_color;
    SDL_Color border_color;
    SDL_Color content_color;
    SDL_Color shadow_color;


    // Current pallette define logic
    
    if (this->gui_type == STATIC_BUTTON_GUI)
    {
        this->current_pallette_number = 1;
    }


    // Pallette switch-case
    switch (this->current_pallette_number)
    {

        case 1:
            // Basic
            if (this->current_element_state == DEFAULT_BS)
            {
                background_color = this->background_color_1;
                border_color = this->border_color_1;
                content_color = this->content_color_1;
                shadow_color = this->shadow_color_1;
            }

            // Hovered
            else if (this->current_element_state == HOVERED_BS)
            {
                background_color = this->background_color_hovered_1;
                border_color = this->border_color_hovered_1;
                content_color = this->content_color_hovered_1;
                shadow_color = this->shadow_color_hovered_1;
            }

            // Clicked
            else if (this->current_element_state == CLICKED_BS)
            {
                background_color = this->background_color_clicked_1;
                border_color = this->border_color_clicked_1;
                content_color = this->content_color_clicked_1;
                shadow_color = this->shadow_color_clicked_1;
            }    

            break;

        case 2:
            // 2nd pallette
            if (this->current_element_state == DEFAULT_BS)
            {
                background_color = this->background_color_2;
                border_color = this->border_color_2;
                content_color = this->content_color_2;
                shadow_color = this->shadow_color_2;
            }

            // Hovered
            else if (this->current_element_state == HOVERED_BS)
            {
                background_color = this->background_color_hovered_2;
                border_color = this->border_color_hovered_2;
                content_color = this->content_color_hovered_2;
                shadow_color = this->shadow_color_hovered_2;
            }

            // Clicked
            else if (this->current_element_state == CLICKED_BS)
            {
                background_color = this->background_color_clicked_2;
                border_color = this->border_color_clicked_2;
                content_color = this->content_color_clicked_2;
                shadow_color = this->shadow_color_clicked_2;
            }    

            break;
    
        default:

            break;
    }
    

    // GLOBAL element opacity implementation
    float opacity_scaler = this->opacity / 255.0f;

    background_color.a = static_cast<uint8_t>(std::round(background_color.a * opacity_scaler));
    border_color.a = static_cast<uint8_t>(std::round(border_color.a * opacity_scaler));
    content_color.a = static_cast<uint8_t>(std::round(content_color.a * opacity_scaler));
    shadow_color.a = static_cast<uint8_t>(std::round(shadow_color.a * opacity_scaler));
    

    // Press offset for push simulation

    if (this->current_element_state != CLICKED_BS) this->press_offset = 0;


    // Figures to build data calculation


    // TODO: CATCH CALCULATION BUG!!!!!!!!!

    // Render points

    int sw_cx = this->x_render_point + shadow_offset_x;
    int sw_cy = this->y_render_point + shadow_offset_y;

    int br_cx = this->x_render_point;
    int br_cy = this->y_render_point;

    int bd_cx = this->x_render_point;
    int bd_cy = this->y_render_point;


    // Sizes 

    unsigned int sw_w = static_cast<unsigned int>(std::round((this->width_size - this->press_offset) * this->shadow_scale_factor));
    unsigned int sw_h = static_cast<unsigned int>(std::round((this->height_size - this->press_offset) * this->shadow_scale_factor));

    unsigned int br_w = this->width_size - this->press_offset; 
    unsigned int br_h = this->height_size - this->press_offset;

    int bg_w_signed = (int)this->width_size - this->press_offset - 2 * (int)this->border_width_size;
    int bg_h_signed = (int)this->height_size - this->press_offset - 2 * (int)this->border_width_size;
    
    unsigned int bg_w = std::max(0, bg_w_signed);
    unsigned int bg_h = std::max(0, bg_h_signed);

    unsigned int sw_r = static_cast<unsigned int>(std::round(this->border_radius_size * this->shadow_scale_factor));
    unsigned int br_r = this->border_radius_size;

    int bg_r_signed = (int)this->border_radius_size - (int)this->border_width_size;
    unsigned int bg_r = std::max(0, bg_r_signed);

    
    // Incrementation of the press offset at every render repeat

    if (this->current_element_state == CLICKED_BS)
    {
        if (this->push_mode_on && this->press_offset <= 5)
        {
            this->press_offset += 1;

            if (this->font_size - this->press_offset >= 10)
            {
                this->set_ttf_font_link(TTF_OpenFont(this->font_path.c_str(), this->font_size - this->press_offset));
            }
        }
    }
    else
    {
        this->press_offset = 0;
        this->set_ttf_font_link(TTF_OpenFont(this->font_path.c_str(), this->font_size));
    }


    // Render 3 figures (shadow (border sizes * scaler), border and background (width or hight - 2 * border_width)) 
    // by their sizes, with use of current colors and render point (center-center)
    if (this->current_form == RECTANGLE_EF)
    {
        // SHADOW
        rectangle_draw_by_color(sw_cx, sw_cy, sw_w, sw_h, shadow_color, renderer);

        // BORDER
        rectangle_draw_by_color(br_cx, br_cy, br_w, br_h, border_color, renderer);

        // BACKGROUND
        rectangle_draw_by_color(bd_cx, bd_cy, bg_w, bg_h, background_color, renderer);
    }

    else if (this->current_form == ROUNDED_RECTANGLE_EF)
    {
        // SHADOW
        rounded_rectangle_draw_by_color(sw_cx, sw_cy, sw_w, sw_h, sw_r, shadow_color, renderer);

        // BORDER
        rounded_rectangle_draw_by_color(br_cx, br_cy, br_w, br_h, br_r, border_color, renderer);

        // BACKGROUND
        rounded_rectangle_draw_by_color(bd_cx, bd_cy, bg_w, bg_h, bg_r, background_color, renderer);
    }

    else if (this->current_form == CIRCLE_EF)
    {
        // SHADOW
        circle_draw_by_color(sw_cx, sw_cy, sw_w / 2, shadow_color, renderer);

        // BORDER
        circle_draw_by_color(br_cx, br_cy, br_w / 2, border_color, renderer);

        // BACKGROUND
        circle_draw_by_color(bd_cx, bd_cy, bg_w / 2, background_color, renderer);
    }


    // Content draw by SDL ttf

    this->update_content_texture(renderer, content_color);


    if (this->content_texture)
    {
        SDL_FRect dst;

        dst.w = this->content_w;
        dst.h = this->content_h;

        dst.x = this->x_render_point - dst.w / 2.0f;
        dst.y = this->y_render_point - dst.h / 2.0f;

        SDL_RenderTexture(renderer, content_texture, nullptr, &dst);
    }
}


void My_SDL_button::update_content_texture(SDL_Renderer* renderer, SDL_Color new_color)
{
    // SDL ttf workflow

    if (!this->content_dirty) return;


    if (!this->ttf_font_link) 
    {
        std::cerr << "Font load error!" << SDL_GetError() << std::endl;
        return;
    }

    if (this->content.empty()) return;

    // Old texture clear
    if (this->content_texture)
    {
        SDL_DestroyTexture(this->content_texture);
        this->content_texture = nullptr;
    }


    SDL_Color color = new_color; // By passed pallette 

    SDL_Surface* surface = TTF_RenderText_Blended(
        this->ttf_font_link,
        this->content.c_str(),
        0,
        color
    );

    if (!surface) return;

    this->content_texture = SDL_CreateTextureFromSurface(renderer, surface);

    this->content_w = surface->w;
    this->content_h = surface->h;

    SDL_DestroySurface(surface);

    this->content_dirty = false;
}


// GUI type setter 

void My_SDL_button::set_gui_type(button_gui_type new_gui_type)
{
    // Error handling for invalid GUI type
    if (new_gui_type != STATIC_BUTTON_GUI && new_gui_type != DYNAMIC_BUTTON_GUI)
    {
        std::cerr << "Invalid button GUI type. GUI type not changed." << std::endl;
        return;
    }

    // New type setting
    else this->gui_type = new_gui_type;
}


void My_SDL_button::current_pallette_choose(unsigned int new_pallette_number)
{
    if (new_pallette_number == 0 || new_pallette_number > PALLETTES_QUANTITY)
    {
        std::cerr << "Invalid pallette number. Element pallette ain' changed." << std::endl;
        return;
    }

    this->current_pallette_number = new_pallette_number;
}


// Render point setter and getters

void My_SDL_button::set_render_point(int x_cc_rp, int y_cc_rp)
{
    this->x_render_point = x_cc_rp;
    this->y_render_point = y_cc_rp;

    this->reset_boundaries_points();
}


int My_SDL_button::get_x_render_point() const { return this->x_render_point; }

int My_SDL_button::get_y_render_point() const { return this->y_render_point; }


// Size setters and getters

void My_SDL_button::set_size(unsigned int new_width, unsigned int new_height)
{
    this->width_size = new_width;
    this->height_size = new_height;

    this->reset_boundaries_points();

    this->reset_current_form();
}


unsigned int My_SDL_button::get_width_size() const { return this->width_size; }

unsigned int My_SDL_button::get_height_size() const { return this->height_size; }


// Styling setters

void My_SDL_button::set_border_width_size(unsigned int new_size)
{
    if (new_size > this->width_size / 2 || 
        new_size > this->height_size / 2 ||
        (this->border_radius_size != 0 && new_size > (this->border_radius_size - 1)))
    {
        std::cerr << "Wrong border size value pass! Border width size ain't changed" << std::endl;
        return;
    }

    this->border_width_size = new_size;
}

void My_SDL_button::set_border_radius(unsigned int new_size)
{
    if (new_size > this->width_size / 2 || new_size > this->height_size / 2)
    {
        std::cerr << "Wrong radius size value pass! Border radius size ain't changed" << std::endl;
        return;
    }

    this->border_radius_size = new_size;

    this->reset_current_form();
}


void My_SDL_button::set_shadow_offset(int new_x_offset, int new_y_offset)
{
    this->shadow_offset_x = new_x_offset;
    this->shadow_offset_y = -new_y_offset;  // SDL works with inverted y-axis on offset
}

void My_SDL_button::set_shadow_scale_factor(float new_scale_factor)
{ 
    this->shadow_scale_factor = new_scale_factor;
}



void My_SDL_button::set_content(const std::string& new_text) 
{
    this->content = new_text;
}


void My_SDL_button::set_ttf_font_link(TTF_Font* new_ttf_font_link) 
{
    // TODO: Error handling for the invalid links
    if (!new_ttf_font_link)
    {
        std::cerr << "Invalid TTF_Font pointer! Font link not set!" << std::endl;
        return;
    }

    this->ttf_font_link = new_ttf_font_link;
}


void My_SDL_button::set_font_path(const std::string& new_font_path) 
{
    // TODO: Error handling for the invalid links
    if (new_font_path.empty())
    {
        std::cerr << "Invalid font path! Font path not set!" << std::endl;
        return;
    }

    this->font_path = new_font_path;

    this->set_ttf_font_link(TTF_OpenFont(this->font_path.c_str(), this->font_size));

    if (!this->ttf_font_link)
    {
        SDL_Log("TTF_OpenFont failed: %s", SDL_GetError());
    }
}

std::string My_SDL_button::get_font_path() const
{
    return this->font_path;
}


void My_SDL_button::set_font_size(unsigned int new_size) 
{
    if (new_size == 0)
    {
        std::cerr << "Invalid font size! Font size not set!" << std::endl;
        return;
    }

    this->font_size = new_size;
}



void My_SDL_button::set_opacity(Uint8 new_opacity) 
{
    this->opacity = new_opacity;
}


// Color setters

// Pallette 1

void My_SDL_button::set_background_color_1(SDL_Color new_color)
{
    this->background_color_1 = new_color;
}

void My_SDL_button::set_border_color_1(SDL_Color new_color)
{
    this->border_color_1 = new_color;
}

void My_SDL_button::set_content_color_1(SDL_Color new_color)
{
    this->content_color_1 = new_color;
}

void My_SDL_button::set_shadow_color_1(SDL_Color new_color)
{
    this->shadow_color_1 = new_color;
}

void My_SDL_button::set_background_color_hovered_1(SDL_Color new_color)
{
    this->background_color_hovered_1 = new_color;
}

void My_SDL_button::set_border_color_hovered_1(SDL_Color new_color)
{
    this->border_color_hovered_1 = new_color;
}

void My_SDL_button::set_content_color_hovered_1(SDL_Color new_color)
{
    this->content_color_hovered_1 = new_color;
}

void My_SDL_button::set_shadow_color_hovered_1(SDL_Color new_color)
{
    this->shadow_color_hovered_1 = new_color;
}

void My_SDL_button::set_background_color_clicked_1(SDL_Color new_color)
{
    this->background_color_clicked_1 = new_color;
}

void My_SDL_button::set_border_color_clicked_1(SDL_Color new_color)
{
    this->border_color_clicked_1 = new_color;
}

void My_SDL_button::set_content_color_clicked_1(SDL_Color new_color)
{
    this->content_color_clicked_1 = new_color;
}

void My_SDL_button::set_shadow_color_clicked_1(SDL_Color new_color)
{
    this->shadow_color_clicked_1 = new_color;
}


// Pallette 2

void My_SDL_button::set_background_color_2(SDL_Color new_color)
{
    this->background_color_2 = new_color;
}

void My_SDL_button::set_border_color_2(SDL_Color new_color)
{
    this->border_color_2 = new_color;
}

void My_SDL_button::set_content_color_2(SDL_Color new_color)
{
    this->content_color_2 = new_color;
}

void My_SDL_button::set_shadow_color_2(SDL_Color new_color)
{
    this->shadow_color_2 = new_color;
}

void My_SDL_button::set_background_color_hovered_2(SDL_Color new_color)
{
    this->background_color_hovered_2 = new_color;
}

void My_SDL_button::set_border_color_hovered_2(SDL_Color new_color)
{
    this->border_color_hovered_2 = new_color;
}

void My_SDL_button::set_content_color_hovered_2(SDL_Color new_color)
{
    this->content_color_hovered_2 = new_color;
}

void My_SDL_button::set_shadow_color_hovered_2(SDL_Color new_color)
{
    this->shadow_color_hovered_2 = new_color;
}

void My_SDL_button::set_background_color_clicked_2(SDL_Color new_color)
{
    this->background_color_clicked_2 = new_color;
}

void My_SDL_button::set_border_color_clicked_2(SDL_Color new_color)
{
    this->border_color_clicked_2 = new_color;
}

void My_SDL_button::set_content_color_clicked_2(SDL_Color new_color)
{
    this->content_color_clicked_2 = new_color;
}

void My_SDL_button::set_shadow_color_clicked_2(SDL_Color new_color)
{
    this->shadow_color_clicked_2 = new_color;
}


// Textures


void My_SDL_button::set_content_texture(SDL_Texture* new_texture)
{
    this->content_texture = new_texture;
}

// =========================================================================================== GUI