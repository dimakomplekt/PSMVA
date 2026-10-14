// 1.2_MS_HELPER.h

#pragma once


// =========================================================================================== IMPORT

#include <string>
#include <vector>

// =========================================================================================== IMPORT


// =========================================================================================== HELPERS



// ===== Save and load presets =====


// Txt-file preset rows
const std::vector<std::string> masks_preset_rows =
{

    "NOZZLE_MASK",
    "",                         // String pass
    "X1:",                      // Should be int in ranges of [0, files_metadata.video_X_data.width]
    "Y1:",                      // Should be int in ranges of [0, files_metadata.video_X_data.height]
    "X2:",                      // Should be int in ranges of [0, files_metadata.video_X_data.width]
    "Y2:",                      // Should be int in ranges of [0, files_metadata.video_X_data.height]
    "Dn:",                      // Should be int in ranges of [nozzle_diameters[0], nozzle_diameters[nozzle_diameters.size() - 1]]
    "",                         // String pass
    "JET_MASK",  
    "",                         // String pass
    "H_MIN: ",                  // HUE minimal in ranges of [0, H_MAX]
    "H_MAX: ",                  // HUE maximal in ranges of [H_MIN, 179]
    "S_MIN: ",                  // Saturation minimal in ranges of [0, S_MAX]
    "S_MAX: ",                  // Saturation maximal in ranges of [S_MIN, 255]
    "V_MIN: ",                  // Value minimal in ranges of [0, V_MAX]
    "V_MAX: ",                  // Value maximal in ranges of [V_MIN, 255]
    "",                         // String pass
    "PARTICLE_MASK",
    "",                         // String pass
    "B_H: ",                    // Blur horizontal in ranges of [0, 3]
    "B_V: ",                    // Blur vertical in ranges of [0, 3]
    "H_MIN: ",                  // Hue minimal in ranges of [0, H_MAX]
    "H_MAX: ",                  // Hue maximal in ranges of [H_MIN, 179]
    "S_MIN: ",                  // Saturation minimal in ranges of [0, S_MAX]
    "S_MAX: ",                  // Saturation maximal in ranges of [S_MIN, 255]
    "V_MIN: ",                  // Value minimal in ranges of [0, V_MAX]
    "V_MAX: ",                  // Value maximal in ranges of [V_MIN, 255]
    "CANNY_LOW: ",              // Canny low in ranges of [0, CANNY_HIGH]
    "CANNY_HIGH: ",             // Canny high in ranges of [CANNY_LOW, 255]
    "DILATE_SIZE: ",            // Dilate size in ranges of [1, 9]
    "DILATE_ITERATIONS: ",      // Dilate iterations in ranges of [1, 3]
    "LENGTH_MIN: ",             // Length minimal in ranges of [0, LENGTH_MAX]
    "LENGTH_MAX: ",             // Length maximal in ranges of [LENGTH_MIN, 100]
    "AREA_MIN: ",               // Area minimal in ranges of [0, AREA_MAX]
    "AREA_MAX: ",               // Area maximal in ranges of [AREA_MIN, 200]
    ""                          // String pass
};


void save_mask_preset(int file_number);


void load_mask_preset(int file_number);


// ===== Save and load presets =====



// =========================================================================================== HELPERS