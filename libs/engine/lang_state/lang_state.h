// lang_state.h

#pragma once

// =========================================================================================== IMPORT

#include "lang_types.h"

// =========================================================================================== IMPORT

// =========================================================================================== LANG_STATE SINGLETON

/**
 * @brief Singleton class that holds the current language state.
 *
 * Ensures there is only one global instance of language state.
 * Provides methods to get and set the current language.
 *
 * Usage:
 * @code
 * Lang_state::Instance().Set_lang(Lang_list::RU);
 * auto current = Lang_state::Instance().Get_lang();
 * @endcode
 */
class Lang_state
{

public:

    /**
     * @brief Returns the singleton instance.
     *
     * Guarantees a single global instance of Lang_state.
     */
    static Lang_state& Instance();


    /**
     * @brief Returns the current language.
     *
     * @return Currently set language as Lang_list.
     */
    Lang_list Get_lang() const;


    /**
     * @brief Sets the current language.
     *
     * @param lang New language to set.
     * @return true if the language was changed successfully, false if invalid.
     */
    bool Set_lang(Lang_list lang);


private:

    // Private constructor ensures no external instances can be created.
    Lang_state();

    // Default destructor is fine; no dynamic allocation to clean up.
    ~Lang_state() = default;

    // Copy constructor is deleted to prevent copying the singleton.
    Lang_state(const Lang_state&) = delete;


    // Assignment operator is deleted to prevent copying the singleton.
    Lang_state& operator=(const Lang_state&) = delete;

    // Currently active language
    Lang_list current_lang;
};

// =========================================================================================== LANG_STATE SINGLETON


// =========================================================================================== SINGLETONES FOR USE

// Global singleton instance of GI_mouse for easy access throughout the program
inline Lang_state& App_lang = Lang_state::Instance();


// =========================================================================================== SINGLETONES FOR USE
