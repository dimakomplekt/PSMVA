#pragma once

#include <array>
#include <filesystem>
#include <string>

struct report_video_results
{
    bool available = false;
    std::array<double, 12> values = {};
};

bool write_report_xlsx(
    const std::filesystem::path& output_path,
    const std::array<report_video_results, 6>& videos,
    std::string& error_message
);
