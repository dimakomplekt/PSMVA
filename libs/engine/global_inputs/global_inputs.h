// global_inputs.h

#pragma once


// =========================================================================================== IMPORT

#include <SDL3/SDL.h>

// =========================================================================================== IMPORT


// =========================================================================================== GLOBAL INPUTS


// =========================================================================================== MOUSE

// Sinletone class for mouse input state tracking - API wrapper for SDL mouse state functions and event 
// handling for mouse data and logic centralization
class GI_mouse
{

public:

    /**
     * @brief Returns the singleton instance.
     *
     * Guarantees a single global instance of GI_mouse.
     */
    static GI_mouse& Instance();

    // ===== Basic getters =====
    
    // Main mouse data update method - should be called once per frame to refresh 
    // mouse state information
    void update();


    float get_x() const;
    float get_y() const;

    bool lb_clicked() const;
    bool rb_clicked() const;

    // ===== Basic getters =====

private:

    // ===== Singleton pattern implementation =====

    // Private constructor ensures no external instances can be created.
    GI_mouse() = default;

    // Default destructor is fine; no dynamic allocation to clean up.
    ~GI_mouse() = default;

    // Copy constructor is deleted to prevent copying the singleton.
    GI_mouse(const GI_mouse&) = delete;


    // Assignment operator is deleted to prevent copying the singleton.
    GI_mouse& operator=(const GI_mouse&) = delete;

    // ===== Singleton pattern implementation =====


    // ===== Cached state =====

    float x_pos = 0.0f;
    float y_pos = 0.0f;

    bool lb_state = false;
    bool rb_state = false;

    // ===== Cached state =====

};


// =========================================================================================== MOUSE


// =========================================================================================== KEYBOARD




// =========================================================================================== KEYBOARD


// =========================================================================================== GLOBAL INPUTS