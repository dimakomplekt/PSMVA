// my_sdl_fader.cpp


// =========================================================================================== IMPORT

#include "my_sdl_fader.h"

// =========================================================================================== IMPORT


// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR

My_SDL_fader::My_SDL_fader()
{
    // Basic settings setter

    // Data

    this->fader_value = 0.5f;

    // Control flags

    this->slot_hovered = false;
    this->slot_clicked = false;
    this->slot_clicked_tmp = false;
    this->current_slot_state = DEFAULT_ES;

    this->knob_hovered = false;
    this->knob_clicked = false;
    this->knob_clicked_tmp = false;
    this->current_knob_state = DEFAULT_ES;


    this->delta_x_from_click_to_knob = 0;

    this->push_mode_on = true;
    this->press_offset = 0;

    // Sizes

    this->set_slot_size(120, 20);

    this->set_knob_size(20, 40);

    this->slot_border_width_size = 2;
    this->slot_border_radius_size = 5;

    this->knob_border_width_size = 2;
    this->knob_border_radius_size = 5;


    this->set_slot_shadow_offset(3, -2);
    this->slot_shadow_scale_factor = 1.0f;

    this->set_knob_shadow_offset(3, -2);
    this->knob_shadow_scale_factor = 1.0f;


    this->slot_current_form = ROUNDED_RECTANGLE_EF;
    this->knob_current_form = ROUNDED_RECTANGLE_EF;


    // Render points

    this->slot_x_render_point = this->slot_width_size / 2 + 1;
    this->slot_y_render_point = this->slot_height_size / 2 + 1 + 200;   // test value


    this->knob_x_render_point = this->knob_position_by_fader_value();
    this->knob_y_render_point = this->slot_y_render_point;


    // Boarders

    this->reset_knob_boundaries_points();
    this->reset_slot_boundaries_points();


    // Anchor points
    this->anchor_points_reset();


    // Pallette

    this->set_opacity(255);


    // Basic colors

    this->set_slot_shadow_color(hex_to_sdl_color("#d85d44", 150));
    this->set_slot_border_color({23, 23, 23, 255});
    this->set_slot_background_color(hex_to_sdl_color("#05f111", 255));

    this->set_slot_shadow_color_hovered({240, 231, 214, 155});
    this->set_slot_border_color_hovered({23, 23, 23, 255});
    this->set_slot_background_color_hovered({240, 231, 214, 255});


    this->set_knob_shadow_color(hex_to_sdl_color("#fd3108", 150));
    this->set_knob_border_color({23, 23, 23, 255});                       
    this->set_knob_background_color(hex_to_sdl_color("#fd3108", 255));

    this->set_knob_shadow_color_hovered({240, 231, 214, 155});
    this->set_knob_border_color_hovered({23, 23, 23, 255});
    this->set_knob_background_color_hovered({240, 231, 214, 255});
    
    this->set_knob_shadow_color_clicked({140, 122, 180, 150});
    this->set_knob_border_color_clicked({232, 222, 42, 255});
    this->set_knob_background_color_clicked({150, 120, 180, 255});


    // Initial render pallette setup

    this->slot_render_shadow_color = this->slot_shadow_color;
    this->slot_render_border_color = this->slot_border_color;
    this->slot_render_background_color = this->slot_background_color;

    this->knob_render_shadow_color = this->knob_shadow_color;
    this->knob_render_border_color = this->knob_border_color;
    this->knob_render_background_color = this->knob_background_color;
}


My_SDL_fader::~My_SDL_fader() = default;

// =========================================================================================== CONSTRUCTOR AND DESTRUCTOR


// =========================================================================================== MAIN LOGIC

float My_SDL_fader::get_fader_value() const
{
    return this->fader_value;
}


void My_SDL_fader::update()
{
    // Slot hover check
    this->slot_hover_check();

    // Knob hover check
    this->knob_hover_check();


    // Knob hover logic before slot hover logic - if knob is hovered - we set the both knob
    // and slot states as HOVERED and start to check the mouse LB-click

    if (this->knob_hovered)
    {
        // Block the hover-click GUI conflict
        if (!this->knob_clicked_tmp)
        {
            this->current_slot_state = DEFAULT_ES;      // Reset the hover for the slot
            this->slot_clicked = false;                 // Reset the click for the slot     

            this->current_knob_state = HOVERED_ES;
        }

        // New click or release check  
        this->knob_clicked = lb_click_check();
    }

    // Slot hover logic - if slot is hovered and knob not hovered - we set the slot state
    // as HOVERED and start to check mouse LB-click 

    else if (this->slot_hovered && !this->knob_hovered)
    {   
        // Block the hover-click GUI conflict
        if(!this->slot_clicked_tmp) 
        {
            this->current_knob_state = DEFAULT_ES;      // Reset the hover for the knob
            this->knob_clicked = false;                 // Reset the click for the knob   

            this->current_slot_state = HOVERED_ES;  
        }

        // New click or release check  
        this->slot_clicked = lb_click_check();
    }

    else
    {
        // Only without press
        if (!this->slot_clicked_tmp) 
        {
            this->current_slot_state = DEFAULT_ES;
    
            // Clicked flags reset with hover ending (blocks the click logic without hovering)
            this->slot_clicked = false; 
        }


        // Only without press
        if (!this->knob_clicked_tmp)
        {
            this->current_knob_state = DEFAULT_ES;
    
            // Clicked flags reset with hover ending (blocks the click logic without hovering)
            this->knob_clicked = false;
        }
    }


    // If we click inside the slot zone and then release - just set the new pallette, 
    // then new values, then reset everything to default state. If we click inside the slot
    // zone and then hold - we must move to the zone where we click and follow the mouse
    // x-position by the slot center. So the logic of 2 cases could be mixed only 
    // in the logic of second case.

    // Furthermore - if we click inside the knob zone - we must act like in the 2nd case, 
    // but only with exception. that we don't need to instantly change the position of the knob
    // by the small deltas between current knob center x-coordinate and the x-coordinate inside 
    // the knob zone, which was detected with the click - just move the knob with taking
    // of this delta into account!

    // Slot click case
    if (this->slot_clicked && !this->slot_clicked_tmp)
    {   
        this->slot_clicked_tmp = true;
        this->current_slot_state = CLICKED_ES;

        // Set the delta for the follow logic

        this->delta_x_from_click_to_knob = 0;
    }


    // Knob click case

    if (this->knob_clicked && !this->knob_clicked_tmp)
    {
        // We click inside the knob zone - we must move to the zone where we click and follow the mouse
        // x-position by the slot center with taking of the delta between current knob center x-coordinate and the x-coordinate inside 
        // the knob zone, which was detected with the click into account

        this->knob_clicked_tmp = true;
        this->current_knob_state = CLICKED_ES;

        // Set the delta for the follow logic
        this->delta_x_from_click_to_knob = static_cast<int>(std::round(App_mouse.get_x())) - this->knob_x_render_point;
    }

    // Click hold case both for knob and slot, but only with the knob follow logic
    if ((this->knob_clicked && this->knob_clicked_tmp) || (this->slot_clicked && this->slot_clicked_tmp))
    {
        // We must move to the zone where we click and follow the mouse x-position by the slot center
        // with taking of the delta between current knob center x-coordinate and the x-coordinate inside 
        // the knob zone, which was detected with the click into account

        int new_knob_center_x = static_cast<int>(std::round(App_mouse.get_x())) - this->delta_x_from_click_to_knob;


        // We also must check if we are in the slot borders with the new position, if not - just set the position to the nearest border

        int left_border = this->slot_boundaries_points.left_boundary + (this->knob_width_size / 2);
        int right_border = this->slot_boundaries_points.right_boundary - (this->knob_width_size / 2);

        // Overflow check for the new knob position
        if (new_knob_center_x < left_border) new_knob_center_x = left_border;
        else if (new_knob_center_x > right_border) new_knob_center_x = right_border;

        this->set_knob_render_point(new_knob_center_x);

        // Update fader value by the new knob position

        this->fader_value = this->fader_value_by_knob_position();


        // New click / release check, even without hover

        this->knob_clicked = lb_click_check();
    }


    // If we release mouse LB
    if ((!this->slot_clicked && this->slot_clicked_tmp) || (!this->knob_clicked && this->knob_clicked_tmp)) 
    {
        // Block repeats and reset
        this->slot_clicked_tmp = false;
        this->knob_clicked_tmp = false;


        // Check if we still hover after the release for the correct state setting

        // Basically could not be possible, but anyway XD
        if (this->slot_hovered && !this->knob_hovered) 
        {
            this->current_slot_state = HOVERED_ES;
            this->current_knob_state = DEFAULT_ES;
        }

        // Case if we stay on the knob after the release
        else if (this->knob_hovered)
        {
            this->current_slot_state = DEFAULT_ES;
            this->current_knob_state = HOVERED_ES;
        }

        // Case if we stay outside after the release
        else if (!this->slot_hovered && !this->knob_hovered)
        {
            this->current_slot_state = DEFAULT_ES; 
            this->current_knob_state = DEFAULT_ES; 
        }
    }


    // Prepare the pallette for rendering by the current slot and knob states
    this->fader_pallette_prepare();
}


void My_SDL_fader::push_mode_switch()
{
    this->push_mode_on = !this->push_mode_on;
}


float My_SDL_fader::fader_value_by_knob_position()
{
    // Fader value calculation by the knob position like ((s.x.rp + (s.w - k.w) / 2) - (s.x.rp + (s.w - k.w) / 2) - curr.x)) / (s.w - k.w) jr
    float new_fader_value = static_cast<float>(this->knob_x_render_point - (this->slot_x_render_point - (this->slot_width_size - this->knob_width_size) / 2)) / static_cast<float>(this->slot_width_size - this->knob_width_size);

    // Overflow check for the fader value
    if (new_fader_value < 0.0f) new_fader_value = 0.0f;
    else if (new_fader_value > 1.0f) new_fader_value = 1.0f;

    return new_fader_value;
}


int My_SDL_fader::knob_position_by_fader_value()
{
    // Fader position calculation by the fader value like (s.x.rp + (s.w - k.w) / 2) + fader_value * (s.w - k.w)
    int new_knob_position = static_cast<int>(std::round((this->slot_x_render_point - (this->slot_width_size - this->knob_width_size) / 2) + this->fader_value * (this->slot_width_size - this->knob_width_size)));

    return new_knob_position;
}


void My_SDL_fader::slot_hover_check()
{
    this->slot_hovered = hover_check_by_boundaries(this->slot_boundaries_points);
}


void My_SDL_fader::knob_hover_check()
{
    this->knob_hovered = hover_check_by_boundaries(this->knob_boundaries_points);
}


// =========================================================================================== MAIN LOGIC


// =========================================================================================== GUI

void My_SDL_fader::render(SDL_Renderer *renderer)
{
    // Press offset for push simulation

    if (this->current_slot_state != CLICKED_ES && this->current_knob_state != CLICKED_ES) this->press_offset = 0;


    // Render points

    int slot_sw_cx = this->slot_x_render_point + this->slot_shadow_offset_x;
    int slot_sw_cy = this->slot_y_render_point + this->slot_shadow_offset_y;

    int slot_br_cx = this->slot_x_render_point;
    int slot_br_cy = this->slot_y_render_point;

    int slot_bd_cx = this->slot_x_render_point;
    int slot_bd_cy = this->slot_y_render_point;


    int knob_sw_cx = this->knob_x_render_point + this->knob_shadow_offset_x;
    int knob_sw_cy = this->knob_y_render_point + this->knob_shadow_offset_y;

    int knob_br_cx = this->knob_x_render_point;
    int knob_br_cy = this->knob_y_render_point;

    int knob_bd_cx = this->knob_x_render_point;
    int knob_bd_cy = this->knob_y_render_point;


    // Sizes

    unsigned int slot_sw_w = static_cast<unsigned int>(std::round((this->slot_width_size - this->press_offset) * this->slot_shadow_scale_factor));
    unsigned int slot_sw_h = static_cast<unsigned int>(std::round((this->slot_height_size - this->press_offset) * this->slot_shadow_scale_factor));

    unsigned int slot_br_w = this->slot_width_size - this->press_offset; 
    unsigned int slot_br_h = this->slot_height_size - this->press_offset;

    int slot_bg_w_signed = (int)this->slot_width_size - 2 * (int)this->slot_border_width_size - static_cast<int>(std::round(static_cast<float>(this->press_offset) / 2));
    int slot_bg_h_signed = (int)this->slot_height_size - 2 * (int)this->slot_border_width_size - static_cast<int>(std::round(static_cast<float>(this->press_offset) / 2));
    
    unsigned int slot_bg_w = std::max(0, slot_bg_w_signed);
    unsigned int slot_bg_h = std::max(0, slot_bg_h_signed);

    unsigned int slot_sw_r = static_cast<unsigned int>(std::round(this->slot_border_radius_size * this->slot_shadow_scale_factor));
    unsigned int slot_br_r = this->slot_border_radius_size - static_cast<int>(std::round(static_cast<float>(this->press_offset) / 2));

    int slot_bg_r_signed = (int)this->slot_border_radius_size - (int)this->slot_border_width_size - static_cast<int>(std::round(static_cast<float>(this->press_offset) / 2));
    unsigned int slot_bg_r = std::max(0, slot_bg_r_signed);



    unsigned int knob_sw_w = static_cast<unsigned int>(std::round((this->knob_width_size - this->press_offset) * this->knob_shadow_scale_factor));
    unsigned int knob_sw_h = static_cast<unsigned int>(std::round((this->knob_height_size - this->press_offset) * this->knob_shadow_scale_factor));

    unsigned int knob_br_w = this->knob_width_size - this->press_offset; 
    unsigned int knob_br_h = this->knob_height_size - this->press_offset;

    int knob_bg_w_signed = (int)this->knob_width_size - 2 * (int)this->knob_border_width_size - static_cast<int>(std::round(static_cast<float>(this->press_offset) / 2));
    int knob_bg_h_signed = (int)this->knob_height_size - 2 * (int)this->knob_border_width_size - static_cast<int>(std::round(static_cast<float>(this->press_offset) / 2));

    unsigned int knob_bg_w = std::max(0, knob_bg_w_signed);
    unsigned int knob_bg_h = std::max(0, knob_bg_h_signed);

    unsigned int knob_sw_r = static_cast<unsigned int>(std::round(this->knob_border_radius_size * this->knob_shadow_scale_factor));
    unsigned int knob_br_r = this->knob_border_radius_size - static_cast<int>(std::round(static_cast<float>(this->press_offset) / 2));

    int knob_bg_r_signed = (int)this->knob_border_radius_size - (int)this->knob_border_width_size - static_cast<int>(std::round(static_cast<float>(this->press_offset) / 2));
    unsigned int knob_bg_r = std::max(0, knob_bg_r_signed);


    // Increment the press offset at every render repeat
    
    if (this->current_knob_state == CLICKED_ES)
    {
        if (this->push_mode_on && this->press_offset <= 5)
        {
            this->press_offset += 1;
        }
    }
    else
    {
        if (this->push_mode_on && this->press_offset > 0)
        {
            this->press_offset = 0;
        }
    }

    // Render the slot and knob with the appropriate colors, sizes and positions, based on the current states

    // Slot render

    if (this->slot_current_form == RECTANGLE_EF)
    {
        // SHADOW
        rectangle_draw_by_color(slot_sw_cx, slot_sw_cy, slot_sw_w, slot_sw_h, this->slot_render_shadow_color, renderer);

        // BORDER
        rectangle_draw_by_color(slot_br_cx, slot_br_cy, slot_br_w, slot_br_h, this->slot_render_border_color, renderer);

        // BACKGROUND
        rectangle_draw_by_color(slot_bd_cx, slot_bd_cy, slot_bg_w, slot_bg_h, this->slot_render_background_color, renderer);
    }

    else if (this->slot_current_form == ROUNDED_RECTANGLE_EF)
    {
        // SHADOW
        rounded_rectangle_draw_by_color(slot_sw_cx, slot_sw_cy, slot_sw_w, slot_sw_h, slot_sw_r, this->slot_render_shadow_color, renderer);

        // BORDER
        rounded_rectangle_draw_by_color(slot_br_cx, slot_br_cy, slot_br_w, slot_br_h, slot_br_r, this->slot_render_border_color, renderer);

        // BACKGROUND
        rounded_rectangle_draw_by_color(slot_bd_cx, slot_bd_cy, slot_bg_w, slot_bg_h, slot_bg_r, this->slot_render_background_color, renderer);
    }

    // Knob render

    if (this->knob_current_form == RECTANGLE_EF)
    {
        // SHADOW
        rectangle_draw_by_color(knob_sw_cx, knob_sw_cy, knob_sw_w, knob_sw_h, this->knob_render_shadow_color, renderer);

        // BORDER
        rectangle_draw_by_color(knob_br_cx, knob_br_cy, knob_br_w, knob_br_h, this->knob_render_border_color, renderer);

        // BACKGROUND
        rectangle_draw_by_color(knob_bd_cx, knob_bd_cy, knob_bg_w, knob_bg_h, this->knob_render_background_color, renderer);
    }

    else if (this->knob_current_form == ROUNDED_RECTANGLE_EF)
    {
        // SHADOW
        rounded_rectangle_draw_by_color(knob_sw_cx, knob_sw_cy, knob_sw_w, knob_sw_h, knob_sw_r, this->knob_render_shadow_color, renderer);

        // BORDER
        rounded_rectangle_draw_by_color(knob_br_cx, knob_br_cy, knob_br_w, knob_br_h, knob_br_r, this->knob_render_border_color, renderer);

        // BACKGROUND
        rounded_rectangle_draw_by_color(knob_bd_cx, knob_bd_cy, knob_bg_w, knob_bg_h, knob_bg_r, this->knob_render_background_color, renderer);
    }

    else if (this->knob_current_form == CIRCLE_EF)
    {
        // SHADOW
        circle_draw_by_color(knob_sw_cx, knob_sw_cy, knob_sw_w / 2, this->knob_render_shadow_color, renderer);

        // BORDER
        circle_draw_by_color(knob_br_cx, knob_br_cy, knob_br_w / 2, this->knob_render_border_color, renderer);

        // BACKGROUND
        circle_draw_by_color(knob_bd_cx, knob_bd_cy, knob_bg_w / 2, this->knob_render_background_color, renderer);
    }
}


void My_SDL_fader::set_render_point(int x_cc_rp, int y_cc_rp)
{
    this->x_render_point = x_cc_rp;
    this->y_render_point = y_cc_rp;

    this->slot_x_render_point = x_cc_rp;
    this->slot_y_render_point = y_cc_rp;

    this->knob_y_render_point = y_cc_rp;

    this->reset_slot_boundaries_points();
    this->reset_knob_boundaries_points();
}


void My_SDL_fader::set_slot_size(unsigned int new_width, unsigned int new_height)
{
    // Slot can't be circle
    if ((new_width < 120 || new_height < 20) || 
        (this->slot_border_width_size > new_width / 2) || 
        (this->slot_border_width_size > new_height / 2) || 
        (this->slot_border_radius_size != 0 && this->slot_border_width_size > (this->slot_border_radius_size - 1)))
    {
        std::cerr << "Wrong size value pass! Slot size ain't changed" << std::endl;
        return;
    }

    this->slot_width_size = new_width;
    this->slot_height_size = new_height;

    this->reset_slot_boundaries_points();
    this->reset_slot_current_form();
}


unsigned int My_SDL_fader::get_slot_width_size() const
{
    return this->slot_width_size;
}


unsigned int My_SDL_fader::get_slot_height_size() const
{
    return this->slot_height_size;
}


void My_SDL_fader::set_knob_size(unsigned int new_width, unsigned int new_height)
{
    // (s.w - k.w  > 20px)
    // k.r < k.w / 2 or k.h / 2
    if ((this->slot_width_size - new_width <= 20) ||
        (this->knob_border_radius_size > new_width || this->knob_border_radius_size > new_height)
    )
    {
        std::cerr << "Wrong size value pass! Knob size ain't changed" << std::endl;
        return;
    }

    this->knob_width_size = new_width;
    this->knob_height_size = new_height;

    this->reset_knob_boundaries_points();
    this->reset_knob_current_form();
}


unsigned int My_SDL_fader::get_knob_width_size() const
{
    return this->knob_width_size;
}


unsigned int My_SDL_fader::get_knob_height_size() const
{
    return this->knob_height_size;
}


void My_SDL_fader::set_slot_border_width_size(unsigned int new_size)
{
    if ((this->slot_border_width_size > this->slot_width_size / 2) || 
        (this->slot_border_width_size > this->slot_height_size / 2) ||
        (this->slot_border_radius_size != 0 && this->slot_border_width_size > (this->slot_border_radius_size - 1)))
    {
        std::cerr << "Wrong border size value pass! Slot border width size ain't changed" << std::endl;
        return;
    }

    this->slot_border_width_size = new_size;
}


void My_SDL_fader::set_slot_border_radius(unsigned int new_size)
{
    if ((this->slot_border_radius_size > this->slot_width_size / 2) || (this->slot_border_radius_size > this->slot_height_size / 2))
    {
        std::cerr << "Wrong radius size value pass! Slot border radius size ain't changed" << std::endl;
        return;
    }

    this->slot_border_radius_size = new_size;

    this->reset_slot_current_form();
}


void My_SDL_fader::set_slot_shadow_offset(int new_x_offset, int new_y_offset)
{
    this->slot_shadow_offset_x = new_x_offset;
    this->slot_shadow_offset_y = -new_y_offset;
}


void My_SDL_fader::set_slot_shadow_scale_factor(float new_scale_factor)
{
    this->slot_shadow_scale_factor = new_scale_factor;
}


void My_SDL_fader::set_knob_border_width_size(unsigned int new_size)
{
    if ((this->knob_border_width_size > this->knob_width_size / 2) || 
        (this->knob_border_width_size > this->knob_height_size / 2) ||
        (this->knob_border_radius_size != 0 && this->knob_border_width_size > (this->knob_border_radius_size - 1)))
    {
        std::cerr << "Wrong border size value pass! knob border width size ain't changed" << std::endl;
        return;
    }

    this->knob_border_width_size = new_size;
}


void My_SDL_fader::set_knob_border_radius(unsigned int new_size)
{
    if ((this->knob_border_radius_size > this->knob_width_size / 2) || (this->knob_border_radius_size > this->knob_height_size / 2))
    {
        std::cerr << "Wrong radius size value pass! knob border radius size ain't changed" << std::endl;
        return;
    }

    this->knob_border_radius_size = new_size;

    this->reset_knob_current_form();
}


void My_SDL_fader::set_knob_shadow_offset(int new_x_offset, int new_y_offset)
{
    this->knob_shadow_offset_x = new_x_offset;
    this->knob_shadow_offset_y = -new_y_offset;
}


void My_SDL_fader::set_knob_shadow_scale_factor(float new_scale_factor)
{
    this->knob_shadow_scale_factor = new_scale_factor;
}


void My_SDL_fader::anchor_points_reset()
{
    // Uses current crop to set the current anchor points

    // Always the same rounding accuracy, because we work with crop map in initial scale and new scalers
    unsigned int half_w = static_cast<unsigned_int>(std::round(static_cast<float>(this->slot_width_size) * 0.5))
    unsigned int half_h = static_cast<unsigned_int>(std::round(static_cast<float>(this->slot_height_size) * 0.5))


    // Anchors reset
    
    /**
     * 
     * P P P P P
     * 1 2 3 4 5
     * 
     * center is 3 -> (n + 1) / 2
     *
     */

    unsigned int c_w = this->slot_x_render_point;         // Horizontal center
    unsigned int c_h = this->slot_y_render_point;         // Vertical center


    // SDL windows points goes from TL(0; 0) to BR(Max_W, Max_H)
    
    this->anchors.top_left     = { c_w - half_w, c_h - half_h };
    this->anchors.top_center   = { c_w , c_h - half_h };
    this->anchors.top_right    = { c_w + half_w, c_h - half_h };

    this->anchors.center_left  = { c_w - half_w, c_h };
    this->anchors.center_center= { c_w, c_h };
    this->anchors.center_right = { c_w + half_w, c_h };

    this->anchors.bottom_left  = { c_w - half_w, c_h + half_h  };
    this->anchors.bottom_center= { c_w, c_h + half_h };
    this->anchors.bottom_right = { c_w + half_w, c_h + half_h };
}


// Color setters

void My_SDL_fader::set_slot_background_color(SDL_Color new_color)               { this->slot_background_color = new_color; }

void My_SDL_fader::set_slot_border_color(SDL_Color new_color)                   { this->slot_border_color = new_color; }

void My_SDL_fader::set_slot_shadow_color(SDL_Color new_color)                   { this->slot_shadow_color = new_color; }

void My_SDL_fader::set_slot_background_color_hovered(SDL_Color new_color)       { this->slot_background_color_hovered = new_color; }

void My_SDL_fader::set_slot_border_color_hovered(SDL_Color new_color)           { this->slot_border_color_hovered = new_color; }

void My_SDL_fader::set_slot_shadow_color_hovered(SDL_Color new_color)           { this->slot_shadow_color_hovered = new_color; }

void My_SDL_fader::set_knob_background_color(SDL_Color new_color)               { this->knob_background_color = new_color; }

void My_SDL_fader::set_knob_border_color(SDL_Color new_color)                   { this->knob_border_color = new_color; }

void My_SDL_fader::set_knob_shadow_color(SDL_Color new_color)                   { this->knob_shadow_color = new_color; }

void My_SDL_fader::set_knob_background_color_hovered(SDL_Color new_color)       { this->knob_background_color_hovered = new_color; }

void My_SDL_fader::set_knob_border_color_hovered(SDL_Color new_color)           { this->knob_border_color_hovered = new_color; }

void My_SDL_fader::set_knob_shadow_color_hovered(SDL_Color new_color)           { this->knob_shadow_color_hovered = new_color; }

void My_SDL_fader::set_knob_background_color_clicked(SDL_Color new_color)       { this->knob_background_color_clicked = new_color; }

void My_SDL_fader::set_knob_border_color_clicked(SDL_Color new_color)           { this->knob_border_color_clicked = new_color; }

void My_SDL_fader::set_knob_shadow_color_clicked(SDL_Color new_color)           { this->knob_shadow_color_clicked = new_color; }


// Knob render point inner setter 

void My_SDL_fader::set_knob_render_point(int x_cc_rp)
{
    this->knob_x_render_point = x_cc_rp;

    this->reset_knob_boundaries_points();
}


// Form checkers

void My_SDL_fader::reset_slot_current_form()
{
    float half_w = this->slot_width_size / 2.0f;
    float half_h = this->slot_height_size / 2.0f;

    if (this->slot_border_radius_size >= half_w && this->slot_border_radius_size >= half_h)
        this->slot_current_form = CIRCLE_EF;         

    else if (this->slot_border_radius_size > 0)
        this->slot_current_form = ROUNDED_RECTANGLE_EF; 
         
    else
        this->slot_current_form = RECTANGLE_EF;       
}


void My_SDL_fader::reset_knob_current_form()
{
    float half_w = this->knob_width_size / 2.0f;
    float half_h = this->knob_height_size / 2.0f;

    if (this->knob_border_radius_size >= half_w && this->knob_border_radius_size >= half_h)
        this->knob_current_form = CIRCLE_EF;         

    else if (this->knob_border_radius_size > 0)
        this->knob_current_form = ROUNDED_RECTANGLE_EF; 
         
    else
        this->knob_current_form = RECTANGLE_EF;       
}


// Boundaries points resetters

void My_SDL_fader::reset_slot_boundaries_points()
{
    this->slot_boundaries_points.left_boundary = this->slot_x_render_point - this->slot_width_size / 2;
    this->slot_boundaries_points.right_boundary = this->slot_x_render_point + this->slot_width_size / 2;
    this->slot_boundaries_points.top_boundary = this->slot_y_render_point - this->slot_height_size / 2;
    this->slot_boundaries_points.bottom_boundary = this->slot_y_render_point + this->slot_height_size / 2;
}


void My_SDL_fader::reset_knob_boundaries_points()
{
    this->knob_boundaries_points.left_boundary = this->knob_x_render_point - this->knob_width_size / 2;
    this->knob_boundaries_points.right_boundary = this->knob_x_render_point + this->knob_width_size / 2;
    this->knob_boundaries_points.top_boundary = this->knob_y_render_point - this->knob_height_size / 2;
    this->knob_boundaries_points.bottom_boundary = this->knob_y_render_point + this->knob_height_size / 2;
}


// Pallette preparation for render step (last update() action)

void My_SDL_fader::fader_pallette_prepare()
{
    // Slot pallette preparation

    if (this->current_slot_state == DEFAULT_ES)
    {
        this->slot_render_shadow_color = this->slot_shadow_color;
        this->slot_render_border_color = this->slot_border_color;
        this->slot_render_background_color = this->slot_background_color;
    }

    // Hovered
    else if (this->current_slot_state == HOVERED_ES)
    {
        this->slot_render_shadow_color = this->slot_shadow_color_hovered;
        this->slot_render_border_color = this->slot_border_color_hovered;
        this->slot_render_background_color = this->slot_background_color_hovered;
    }

    // Fader clicked, so we colorize the knob and reset the slot color to default / hovered
    else if (this->current_slot_state == CLICKED_ES)
    {
        this->slot_render_shadow_color = this->slot_shadow_color;
        this->slot_render_border_color = this->slot_border_color;
        this->slot_render_background_color = this->slot_background_color;
    }    


    // Knob pallette preparation

    if (this->current_knob_state == DEFAULT_ES)
    {
        this->knob_render_shadow_color = this->knob_shadow_color;
        this->knob_render_border_color = this->knob_border_color;
        this->knob_render_background_color = this->knob_background_color;
    }

    // Hovered
    else if (this->current_knob_state == HOVERED_ES)
    {
        this->knob_render_shadow_color = this->knob_shadow_color_hovered;
        this->knob_render_border_color = this->knob_border_color_hovered;
        this->knob_render_background_color = this->knob_background_color_hovered;
    }

    // Fader clicked, so we colorize the knob and reset the slot color to default / hovered
    else if (this->current_knob_state == CLICKED_ES)
    {
        this->knob_render_shadow_color = this->knob_shadow_color_clicked;
        this->knob_render_border_color = this->knob_border_color_clicked;
        this->knob_render_background_color = this->knob_background_color_clicked;
    }    


    // Global opacity scaler for the render pallette

    float opacity_scaler = static_cast<float>(this->opacity) / 255.0f;

    this->slot_render_shadow_color.a = static_cast<uint8_t>(std::round(static_cast<float>(this->slot_render_shadow_color.a) * opacity_scaler));
    this->slot_render_border_color.a = static_cast<uint8_t>(std::round(static_cast<float>(this->slot_render_border_color.a) * opacity_scaler));
    this->slot_render_background_color.a = static_cast<uint8_t>(std::round(static_cast<float>(this->slot_render_background_color.a) * opacity_scaler));


    this->knob_render_shadow_color.a = static_cast<uint8_t>(std::round(static_cast<float>(this->knob_render_shadow_color.a) * opacity_scaler));
    this->knob_render_border_color.a = static_cast<uint8_t>(std::round(static_cast<float>(this->knob_render_border_color.a) * opacity_scaler));
    this->knob_render_background_color.a = static_cast<uint8_t>(std::round(static_cast<float>(this->knob_render_background_color.a) * opacity_scaler));
}

// =========================================================================================== GUI
