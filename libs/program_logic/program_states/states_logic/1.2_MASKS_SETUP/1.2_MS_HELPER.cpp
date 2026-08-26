// 1.2_MS_HELPER.cpp

// =========================================================================================== IMPORT

#include "1.2_MS_HELPER.h"

// For parsing

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>



// Files metadata
#include "../1.1_FILE_CHOOSE/1.1_FILE_CHOOSE.h"

// Controlled masks ctx and nozzle diameters
#include "1.2_MASKS_SETUP.h"

// =========================================================================================== IMPORT


// =========================================================================================== HELPERS


// =========================================================================================== FILE SELECTOR

file_masks_data* get_file_masks(int file_number)
{

    switch (file_number)
    {

        case 1:
            return &masks_data.file_1_masks;

        case 2:
            return &masks_data.file_2_masks;

        case 3:
            return &masks_data.file_3_masks;

        case 4:
            return &masks_data.file_4_masks;

        case 5:
            return &masks_data.file_5_masks;

        case 6:
            return &masks_data.file_6_masks;

        default:
            return nullptr;

    }

}


parsed_video_data* get_file_metadata(int file_number)
{

    switch (file_number)
    {

        case 1:
            return &files_metadata.video_1_data;

        case 2:
            return &files_metadata.video_2_data;

        case 3:
            return &files_metadata.video_3_data;

        case 4:
            return &files_metadata.video_4_data;

        case 5:
            return &files_metadata.video_5_data;

        case 6:
            return &files_metadata.video_6_data;

        default:
            return nullptr;

    }

}


// =========================================================================================== FILE SELECTOR


// =========================================================================================== FILESYSTEM

std::string save_file_dialog()
{
    char file_path[MAX_PATH] = { 0 };

    OPENFILENAMEA dialog = {};

    dialog.lStructSize = sizeof(OPENFILENAMEA);
    dialog.lpstrFile = file_path;
    dialog.nMaxFile = MAX_PATH;

    dialog.lpstrFilter =
        "Mask preset (*.txt)\0*.txt\0"
        "All files (*.*)\0*.*\0";

    dialog.nFilterIndex = 1;

    dialog.lpstrDefExt = "txt";

    dialog.Flags =
        OFN_PATHMUSTEXIST |
        OFN_OVERWRITEPROMPT;

    if (GetSaveFileNameA(&dialog))
    {
        return std::string(file_path);
    }

    return "";
}


std::string load_file_dialog()
{
    char file_path[MAX_PATH] = { 0 };

    OPENFILENAMEA dialog = {};

    dialog.lStructSize = sizeof(OPENFILENAMEA);
    dialog.lpstrFile = file_path;
    dialog.nMaxFile = MAX_PATH;

    dialog.lpstrFilter =
        "Mask preset (*.txt)\0*.txt\0"
        "All files (*.*)\0*.*\0";

    dialog.nFilterIndex = 1;

    dialog.Flags =
        OFN_PATHMUSTEXIST |
        OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&dialog))
    {
        return std::string(file_path);
    }

    return "";
}

// =========================================================================================== FILESYSTEM



// =========================================================================================== SAVE


void save_mask_preset(int file_number)
{

    // TEST
    std::cout << "CALL SAVE FUNCTION TO FILE " << file_number << ".\n\n";


    // ===== Get selected file =====

    file_masks_data* used_file = get_file_masks(file_number);

    if (used_file == nullptr)
    {
        std::cout << "Wrong file number!\n" << std::endl;
        return;
    }


    // ===== Get save path =====

    std::string file_path = save_file_dialog();

    if (file_path.empty())
    {
        std::cout << "Save cancelled!\n" << std::endl;
        return;
    }


    // ===== Open =====

    std::ofstream file(file_path);

    if (!file.is_open())
    {
        std::cout << "Can't open preset file for writing!\n"
                  << std::endl;
        return;
    }



    // ===== Write NOZZLE MASK =====

    file << "NOZZLE_MASK\n";
    file << "\n";

    file << "X1: " << used_file->nozzle_mask.x_1 << "\n";
    file << "Y1: " << used_file->nozzle_mask.y_1 << "\n";
    file << "X2: " << used_file->nozzle_mask.x_2 << "\n";
    file << "Y2: " << used_file->nozzle_mask.y_2 << "\n";
    file << "Dn: " << used_file->nozzle_mask.d_n << "\n";

    file << "\n";

    // ===== Write NOZZLE MASK =====

    // ===== Write JET MASK =====

    file << "JET_MASK\n";
    file << "\n";

    file << "H_MIN: " << used_file->jet_mask.h_min << "\n";
    file << "H_MAX: " << used_file->jet_mask.h_max << "\n";
    file << "S_MIN: " << used_file->jet_mask.s_min << "\n";
    file << "S_MAX: " << used_file->jet_mask.s_max << "\n";
    file << "V_MIN: " << used_file->jet_mask.v_min << "\n";
    file << "V_MAX: " << used_file->jet_mask.v_max << "\n";

    file << "\n";

    // ===== Write JET MASK =====

    
    // ===== Write =====

    file.close();

}


// =========================================================================================== SAVE


// =========================================================================================== LOAD

// =========================================================================================== LOAD


bool load_mask_1_preset(

    int file_number,
    const std::vector<std::string>& txt_lines,
    decltype(file_masks_data::nozzle_mask)& output
    
)
{
    // ===== GET FILE =====

    parsed_video_data* used_video = get_file_metadata(file_number);

    if (used_video == nullptr)
    {
        std::cout << "Wrong file number!\n" << std::endl;
        return false;
    }

    // ===== GET FILE =====


    // =======================================================================================
    // FORMAT CHECK

    bool nozzle_mask_found = false;

    bool x_1_found = false;
    bool y_1_found = false;
    bool x_2_found = false;
    bool y_2_found = false;
    bool d_n_found = false;


    std::string tmp_x_1;
    std::string tmp_y_1;
    std::string tmp_x_2;
    std::string tmp_y_2;
    std::string tmp_d_n;


    for (const std::string& current_line : txt_lines)
    {
        // ===== NOZZLE MASK =====

        if (current_line == "NOZZLE_MASK")
        {
            if (nozzle_mask_found)
            {
                std::cout << "Duplicate NOZZLE_MASK section!\n"
                          << std::endl;

                return false;
            }

            nozzle_mask_found = true;
        }


        // ===== X1 =====

        else if (current_line.rfind("X1:", 0) == 0)
        {
            if (x_1_found)
            {
                std::cout << "Duplicate X1 field!\n"
                          << std::endl;

                return false;
            }

            tmp_x_1 = current_line.substr(3);

            size_t first_not_space = tmp_x_1.find_first_not_of(' ');

            if (first_not_space != std::string::npos)
            {
                tmp_x_1 = tmp_x_1.substr(first_not_space);
            }
            else
            {
                tmp_x_1.clear();
            }

            x_1_found = true;
        }


        // ===== Y1 =====

        else if (current_line.rfind("Y1:", 0) == 0)
        {
            if (y_1_found)
            {
                std::cout << "Duplicate Y1 field!\n"
                          << std::endl;

                return false;
            }

            tmp_y_1 = current_line.substr(3);

            size_t first_not_space = tmp_y_1.find_first_not_of(' ');

            if (first_not_space != std::string::npos)
            {
                tmp_y_1 = tmp_y_1.substr(first_not_space);
            }
            else
            {
                tmp_y_1.clear();
            }

            y_1_found = true;
        }


        // ===== X2 =====

        else if (current_line.rfind("X2:", 0) == 0)
        {
            if (x_2_found)
            {
                std::cout << "Duplicate X2 field!\n"
                          << std::endl;

                return false;
            }

            tmp_x_2 = current_line.substr(3);

            size_t first_not_space = tmp_x_2.find_first_not_of(' ');

            if (first_not_space != std::string::npos)
            {
                tmp_x_2 = tmp_x_2.substr(first_not_space);
            }
            else
            {
                tmp_x_2.clear();
            }

            x_2_found = true;
        }


        // ===== Y2 =====

        else if (current_line.rfind("Y2:", 0) == 0)
        {
            if (y_2_found)
            {
                std::cout << "Duplicate Y2 field!\n"
                          << std::endl;

                return false;
            }

            tmp_y_2 = current_line.substr(3);

            size_t first_not_space = tmp_y_2.find_first_not_of(' ');

            if (first_not_space != std::string::npos)
            {
                tmp_y_2 = tmp_y_2.substr(first_not_space);
            }
            else
            {
                tmp_y_2.clear();
            }

            y_2_found = true;
        }


        // ===== Dn =====

        else if (current_line.rfind("Dn:", 0) == 0)
        {
            if (d_n_found)
            {
                std::cout << "Duplicate Dn field!\n"
                          << std::endl;

                return false;
            }

            tmp_d_n = current_line.substr(3);

            size_t first_not_space = tmp_d_n.find_first_not_of(' ');

            if (first_not_space != std::string::npos)
            {
                tmp_d_n = tmp_d_n.substr(first_not_space);
            }
            else
            {
                tmp_d_n.clear();
            }

            d_n_found = true;
        }
    }


    // ===== CHECK REQUIRED FIELDS =====

    if (!nozzle_mask_found ||
        !x_1_found ||
        !y_1_found ||
        !x_2_found ||
        !y_2_found ||
        !d_n_found)
    {
        std::cout << "Wrong NOZZLE_MASK preset format!\n"
                  << std::endl;

        return false;
    }

    // =======================================================================================
    // FORMAT CHECK


    // =======================================================================================
    // DATA CHECK

    int x_1_for_pass;
    int y_1_for_pass;

    int x_2_for_pass;
    int y_2_for_pass;

    int d_n_for_pass;


    // =======================================================================================
    // CHECK X1

    if (tmp_x_1.empty() ||
        tmp_x_1.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Wrong X1 value!\n"
                  << std::endl;

        return false;
    }

    int x_1_value = std::stoi(tmp_x_1);

    if (x_1_value < 0 ||
        x_1_value > static_cast<int>(used_video->width))
    {
        std::cout << "Wrong X1 value!\n"
                  << std::endl;

        return false;
    }

    x_1_for_pass = x_1_value;

    // =======================================================================================
    // CHECK X1


    // =======================================================================================
    // CHECK Y1

    if (tmp_y_1.empty() ||
        tmp_y_1.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Wrong Y1 value!\n"
                  << std::endl;

        return false;
    }

    int y_1_value = std::stoi(tmp_y_1);

    if (y_1_value < 0 ||
        y_1_value > static_cast<int>(used_video->height))
    {
        std::cout << "Wrong Y1 value!\n"
                  << std::endl;

        return false;
    }

    y_1_for_pass = y_1_value;

    // =======================================================================================
    // CHECK Y1


    // =======================================================================================
    // CHECK X2

    if (tmp_x_2.empty() ||
        tmp_x_2.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Wrong X2 value!\n"
                  << std::endl;

        return false;
    }

    int x_2_value = std::stoi(tmp_x_2);

    if (x_2_value < 0 ||
        x_2_value > static_cast<int>(used_video->width))
    {
        std::cout << "Wrong X2 value!\n"
                  << std::endl;

        return false;
    }

    x_2_for_pass = x_2_value;

    // =======================================================================================
    // CHECK X2


    // =======================================================================================
    // CHECK Y2

    if (tmp_y_2.empty() ||
        tmp_y_2.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Wrong Y2 value!\n"
                  << std::endl;

        return false;
    }

    int y_2_value = std::stoi(tmp_y_2);

    if (y_2_value < 0 ||
        y_2_value > static_cast<int>(used_video->height))
    {
        std::cout << "Wrong Y2 value!\n"
                  << std::endl;

        return false;
    }

    y_2_for_pass = y_2_value;

    // =======================================================================================
    // CHECK Y2


    // =======================================================================================
    // CHECK DN

    if (tmp_d_n.empty() ||
        tmp_d_n.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Wrong nozzle diameter!\n"
                  << std::endl;

        return false;
    }

    int d_n_value = std::stoi(tmp_d_n);

    bool diameter_found = false;

    for (size_t i = 0; i < nozzle_diameters.size(); ++i)
    {
        if (d_n_value == nozzle_diameters[i])
        {
            diameter_found = true;
            break;
        }
    }

    if (!diameter_found)
    {
        std::cout << "Wrong nozzle diameter!\n"
                  << std::endl;

        return false;
    }

    d_n_for_pass = d_n_value;

    // =======================================================================================
    // CHECK DN


    // =======================================================================================
    // OUTPUT

    output.x_1 = x_1_for_pass;
    output.y_1 = y_1_for_pass;

    output.x_2 = x_2_for_pass;
    output.y_2 = y_2_for_pass;

    output.d_n = d_n_for_pass;

    output.initialized = true;

    // =======================================================================================
    // OUTPUT


    return true;
}


// ===========================================================================================


bool load_mask_2_preset(

    int file_number,
    const std::vector<std::string>& txt_lines,
    decltype(file_masks_data::jet_mask)& output

)
{
    // file_number здесь сохраняем в интерфейсе
    // для симметрии с load_mask_1_preset().
    // Для JET_MASK metadata не требуется.

    (void)file_number;


    // =======================================================================================
    // FORMAT CHECK

    bool jet_mask_found = false;

    bool h_min_found = false;
    bool h_max_found = false;

    bool s_min_found = false;
    bool s_max_found = false;

    bool v_min_found = false;
    bool v_max_found = false;


    std::string tmp_h_min;
    std::string tmp_h_max;

    std::string tmp_s_min;
    std::string tmp_s_max;

    std::string tmp_v_min;
    std::string tmp_v_max;


    for (const std::string& current_line : txt_lines)
    {
        // ===== JET MASK =====

        if (current_line == "JET_MASK")
        {
            if (jet_mask_found)
            {
                std::cout << "Duplicate JET_MASK section!\n"
                          << std::endl;

                return false;
            }

            jet_mask_found = true;
        }


        // ===== H MIN =====

        else if (current_line.rfind("H_MIN:", 0) == 0)
        {
            if (h_min_found)
            {
                std::cout << "Duplicate H_MIN field!\n"
                          << std::endl;

                return false;
            }

            tmp_h_min = current_line.substr(6);

            size_t first_not_space = tmp_h_min.find_first_not_of(' ');

            if (first_not_space != std::string::npos)
            {
                tmp_h_min = tmp_h_min.substr(first_not_space);
            }
            else
            {
                tmp_h_min.clear();
            }

            h_min_found = true;
        }


        // ===== H MAX =====

        else if (current_line.rfind("H_MAX:", 0) == 0)
        {
            if (h_max_found)
            {
                std::cout << "Duplicate H_MAX field!\n"
                          << std::endl;

                return false;
            }

            tmp_h_max = current_line.substr(6);

            size_t first_not_space = tmp_h_max.find_first_not_of(' ');

            if (first_not_space != std::string::npos)
            {
                tmp_h_max = tmp_h_max.substr(first_not_space);
            }
            else
            {
                tmp_h_max.clear();
            }

            h_max_found = true;
        }


        // ===== S MIN =====

        else if (current_line.rfind("S_MIN:", 0) == 0)
        {
            if (s_min_found)
            {
                std::cout << "Duplicate S_MIN field!\n"
                          << std::endl;

                return false;
            }

            tmp_s_min = current_line.substr(6);

            size_t first_not_space = tmp_s_min.find_first_not_of(' ');

            if (first_not_space != std::string::npos)
            {
                tmp_s_min = tmp_s_min.substr(first_not_space);
            }
            else
            {
                tmp_s_min.clear();
            }

            s_min_found = true;
        }


        // ===== S MAX =====

        else if (current_line.rfind("S_MAX:", 0) == 0)
        {
            if (s_max_found)
            {
                std::cout << "Duplicate S_MAX field!\n"
                          << std::endl;

                return false;
            }

            tmp_s_max = current_line.substr(6);

            size_t first_not_space = tmp_s_max.find_first_not_of(' ');

            if (first_not_space != std::string::npos)
            {
                tmp_s_max = tmp_s_max.substr(first_not_space);
            }
            else
            {
                tmp_s_max.clear();
            }

            s_max_found = true;
        }


        // ===== V MIN =====

        else if (current_line.rfind("V_MIN:", 0) == 0)
        {
            if (v_min_found)
            {
                std::cout << "Duplicate V_MIN field!\n"
                          << std::endl;

                return false;
            }

            tmp_v_min = current_line.substr(6);

            size_t first_not_space = tmp_v_min.find_first_not_of(' ');

            if (first_not_space != std::string::npos)
            {
                tmp_v_min = tmp_v_min.substr(first_not_space);
            }
            else
            {
                tmp_v_min.clear();
            }

            v_min_found = true;
        }


        // ===== V MAX =====

        else if (current_line.rfind("V_MAX:", 0) == 0)
        {
            if (v_max_found)
            {
                std::cout << "Duplicate V_MAX field!\n"
                          << std::endl;

                return false;
            }

            tmp_v_max = current_line.substr(6);

            size_t first_not_space = tmp_v_max.find_first_not_of(' ');

            if (first_not_space != std::string::npos)
            {
                tmp_v_max = tmp_v_max.substr(first_not_space);
            }
            else
            {
                tmp_v_max.clear();
            }

            v_max_found = true;
        }
    }


    // ===== CHECK REQUIRED FIELDS =====

    if (!jet_mask_found ||
        !h_min_found ||
        !h_max_found ||
        !s_min_found ||
        !s_max_found ||
        !v_min_found ||
        !v_max_found)
    {
        std::cout << "Wrong JET_MASK preset format!\n"
                  << std::endl;

        return false;
    }

    // =======================================================================================
    // FORMAT CHECK


    // =======================================================================================
    // DATA CHECK

    int h_min_for_pass;
    int h_max_for_pass;

    int s_min_for_pass;
    int s_max_for_pass;

    int v_min_for_pass;
    int v_max_for_pass;


    std::cout << "H_MIN: " << tmp_h_min << "\n\n";

    std::cout << "H_MAX: " << tmp_h_max << "\n\n";
    
    std::cout << "S_MIN: " << tmp_s_min << "\n\n";
    
    std::cout << "S_MAX: " << tmp_s_max << "\n\n";
    
    std::cout << "V_MIN: " << tmp_v_min << "\n\n";
    
    std::cout << "V_MAX: " << tmp_v_max << "\n\n";


    // =======================================================================================
    // CHECK H MIN

    if (tmp_h_min.empty() ||
        tmp_h_min.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Wrong H_MIN value!\n"
                  << std::endl;

        return false;
    }

    h_min_for_pass = std::stoi(tmp_h_min);

    if (h_min_for_pass < 0 ||
        h_min_for_pass > 179)
    {
        std::cout << "Wrong H_MIN value!\n"
                  << std::endl;

        return false;
    }

    // =======================================================================================
    // CHECK H MIN


    // =======================================================================================
    // CHECK H MAX

    if (tmp_h_max.empty() ||
        tmp_h_max.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Wrong H_MAX value SYMBOLS!\n"
                  << std::endl;

        return false;
    }

    h_max_for_pass = std::stoi(tmp_h_max);

    if (h_max_for_pass < 0 ||
        h_max_for_pass > 179 || h_min_for_pass >= h_max_for_pass)
    {
        std::cout << "Wrong H_MAX value VALUE!\n"
                  << std::endl;

        return false;
    }

    // =======================================================================================
    // CHECK H MAX


    // =======================================================================================
    // CHECK S MIN

    if (tmp_s_min.empty() ||
        tmp_s_min.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Wrong S_MIN value!\n"
                  << std::endl;

        return false;
    }

    s_min_for_pass = std::stoi(tmp_s_min);

    if (s_min_for_pass < 0 ||
        s_min_for_pass > 255)
    {
        std::cout << "Wrong S_MIN value!\n"
                  << std::endl;

        return false;
    }

    // =======================================================================================
    // CHECK S MIN


    // =======================================================================================
    // CHECK S MAX

    if (tmp_s_max.empty() ||
        tmp_s_max.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Wrong S_MAX value!\n"
                  << std::endl;

        return false;
    }

    s_max_for_pass = std::stoi(tmp_s_max);

    if (s_max_for_pass < 0 ||
        s_max_for_pass > 255 || s_min_for_pass >= s_max_for_pass)
    {
        std::cout << "Wrong S_MAX value!\n"
                  << std::endl;

        return false;
    }

    // =======================================================================================
    // CHECK S MAX


    // =======================================================================================
    // CHECK V MIN

    if (tmp_v_min.empty() ||
        tmp_v_min.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Wrong V_MIN value!\n"
                  << std::endl;

        return false;
    }

    v_min_for_pass = std::stoi(tmp_v_min);

    if (v_min_for_pass < 0 ||
        v_min_for_pass > 255)
    {
        std::cout << "Wrong V_MIN value!\n"
                  << std::endl;

        return false;
    }

    // =======================================================================================
    // CHECK V MIN


    // =======================================================================================
    // CHECK V MAX

    if (tmp_v_max.empty() ||
        tmp_v_max.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "Wrong V_MAX value!\n"
                  << std::endl;

        return false;
    }

    v_max_for_pass = std::stoi(tmp_v_max);

    if (v_max_for_pass < 0 ||
        v_max_for_pass > 255 || v_min_for_pass >= v_max_for_pass)
    {
        std::cout << "Wrong V_MAX value!\n"
                  << std::endl;

        return false;
    }

    // =======================================================================================
    // CHECK V MAX


    // =======================================================================================
    // CHECK RANGES

    if (h_min_for_pass > h_max_for_pass)
    {
        std::cout << "H_MIN can't be greater than H_MAX!\n"
                  << std::endl;

        return false;
    }

    if (s_min_for_pass > s_max_for_pass)
    {
        std::cout << "S_MIN can't be greater than S_MAX!\n"
                  << std::endl;

        return false;
    }

    if (v_min_for_pass > v_max_for_pass)
    {
        std::cout << "V_MIN can't be greater than V_MAX!\n"
                  << std::endl;

        return false;
    }

    // =======================================================================================
    // CHECK RANGES


    // =======================================================================================
    // OUTPUT

    output.h_min = h_min_for_pass;
    output.h_max = h_max_for_pass;

    output.s_min = s_min_for_pass;
    output.s_max = s_max_for_pass;

    output.v_min = v_min_for_pass;
    output.v_max = v_max_for_pass;

    output.initialized = true;

    // =======================================================================================
    // OUTPUT


    return true;
}


// ===========================================================================================



void load_mask_preset(int file_number)
{
    // ===== GET FILE =====

    file_masks_data* used_file = get_file_masks(file_number);

    if (used_file == nullptr)
    {
        std::cout << "Wrong file number!\n" << std::endl;
        return;
    }

    // ===== GET FILE =====


    // ===== SELECT FILE =====

    std::string file_path = load_file_dialog();

    if (file_path.empty())
    {
        std::cout << "Load cancelled!\n" << std::endl;
        return;
    }

    // ===== SELECT FILE =====


    // ===== OPEN FILE =====

    std::ifstream file(file_path);

    if (!file.is_open())
    {
        std::cout << "Can't open preset file!\n"
                  << std::endl;

        return;
    }

    // ===== OPEN FILE =====


    // ===== COPY ROWS =====

    std::vector<std::string> txt_lines;

    std::string line;

    while (std::getline(file, line))
    {
        txt_lines.push_back(line);
    }

    file.close();

    // ===== COPY ROWS =====


    // =======================================================================================
    // TEMPORARY DATA

    decltype(file_masks_data::nozzle_mask) nozzle_mask_for_pass;
    decltype(file_masks_data::jet_mask) jet_mask_for_pass;

    // =======================================================================================
    // TEMPORARY DATA


    // =======================================================================================
    // LOAD MASKS

    bool nozzle_mask_loaded =
        load_mask_1_preset(
            file_number,
            txt_lines,
            nozzle_mask_for_pass);


    bool jet_mask_loaded =
        load_mask_2_preset(
            file_number,
            txt_lines,
            jet_mask_for_pass);

    // =======================================================================================
    // LOAD MASKS


    // =======================================================================================
    // FINAL CHECK

    if (!nozzle_mask_loaded ||
        !jet_mask_loaded)
    {
        std::cout << "Preset loading failed!\n"
                  << "No mask data was changed.\n"
                  << std::endl;

        return;
    }

    // =======================================================================================
    // FINAL CHECK


    // =======================================================================================
    // FINAL FILL

    // Everything is correct.
    // Both masks are valid.
    // Now and only now modify global data.

    used_file->nozzle_mask = nozzle_mask_for_pass;
    used_file->jet_mask = jet_mask_for_pass;

    // =======================================================================================
    // FINAL FILL
}

// =========================================================================================== LOAD


// =========================================================================================== HELPERS