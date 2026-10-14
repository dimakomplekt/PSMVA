#include "xlsx_report_writer.h"

#include <cmath>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <system_error>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace
{
    struct zip_entry
    {
        std::string name;
        std::string contents;
        std::uint32_t crc = 0;
        std::uint32_t local_header_offset = 0;
    };

    const std::array<std::string, 12> row_names = {
        "Интенсивность излучения, %",
        "Дельта интенсивности излучения, % / кадр",
        "Ширина струи, мм",
        "Длина струи, мм",
        "Угол основной траектории, °",
        "Угол отклонения, °",
        "Максимальный угол отклонения, °",
        "Дельта угла отклонения, °/ кадр",
        "Скорость частиц без отклонений, м/с",
        "Скорость отклоненных частиц, м/с",
        "Дельта скорости частиц, (м/с) / кадр",
        "Процент отклоненных частиц, %"
    };

    std::uint32_t crc32(const std::string& data)
    {
        std::uint32_t crc = 0xFFFFFFFFu;

        for (unsigned char byte : data)
        {
            crc ^= byte;
            for (int bit = 0; bit < 8; ++bit)
            {
                const std::uint32_t mask = 0u - (crc & 1u);
                crc = (crc >> 1) ^ (0xEDB88320u & mask);
            }
        }

        return ~crc;
    }

    void write_u16(std::ofstream& output, std::uint16_t value)
    {
        const char bytes[] = {
            static_cast<char>(value & 0xFF),
            static_cast<char>((value >> 8) & 0xFF)
        };
        output.write(bytes, sizeof(bytes));
    }

    void write_u32(std::ofstream& output, std::uint32_t value)
    {
        const char bytes[] = {
            static_cast<char>(value & 0xFF),
            static_cast<char>((value >> 8) & 0xFF),
            static_cast<char>((value >> 16) & 0xFF),
            static_cast<char>((value >> 24) & 0xFF)
        };
        output.write(bytes, sizeof(bytes));
    }

    std::string xml_escape(const std::string& text)
    {
        std::string escaped;
        escaped.reserve(text.size());

        for (char character : text)
        {
            switch (character)
            {
                case '&': escaped += "&amp;"; break;
                case '<': escaped += "&lt;"; break;
                case '>': escaped += "&gt;"; break;
                case '"': escaped += "&quot;"; break;
                case '\'': escaped += "&apos;"; break;
                default: escaped += character; break;
            }
        }

        return escaped;
    }

    std::string column_name(unsigned int column)
    {
        std::string name;
        while (column > 0)
        {
            --column;
            name.insert(name.begin(), static_cast<char>('A' + column % 26));
            column /= 26;
        }
        return name;
    }

    std::string inline_string_cell(const std::string& address, const std::string& value, unsigned int style)
    {
        return "<c r=\"" + address + "\" s=\"" + std::to_string(style) +
               "\" t=\"inlineStr\"><is><t>" + xml_escape(value) +
               "</t></is></c>";
    }

    std::string number_cell(const std::string& address, double value)
    {
        std::ostringstream number;
        number << std::setprecision(10) << value;
        return "<c r=\"" + address + "\" s=\"2\"><v>" + number.str() + "</v></c>";
    }

    std::string header_number_cell(const std::string& address, unsigned int value)
    {
        return "<c r=\"" + address + "\" s=\"1\"><v>" + std::to_string(value) + "</v></c>";
    }

    std::string create_worksheet(const std::array<report_video_results, 6>& videos)
    {
        std::ostringstream sheet;
        sheet << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
              << "<worksheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\">"
              << "<dimension ref=\"A1:G13\"/><sheetViews><sheetView workbookViewId=\"0\"/></sheetViews>"
              << "<sheetFormatPr defaultRowHeight=\"20\"/><cols>"
              << "<col min=\"1\" max=\"1\" width=\"48\" customWidth=\"1\"/>"
              << "<col min=\"2\" max=\"7\" width=\"16\" customWidth=\"1\"/>"
              << "</cols><sheetData><row r=\"1\">"
              << inline_string_cell("A1", "Режим", 1);

        for (unsigned int video = 0; video < videos.size(); ++video)
        {
            sheet << header_number_cell(column_name(video + 2) + "1", video + 1);
        }
        sheet << "</row>";

        for (unsigned int row = 0; row < row_names.size(); ++row)
        {
            const unsigned int worksheet_row = row + 2;
            sheet << "<row r=\"" << worksheet_row << "\">"
                  << inline_string_cell("A" + std::to_string(worksheet_row), row_names[row], 3);

            for (unsigned int video = 0; video < videos.size(); ++video)
            {
                const std::string address = column_name(video + 2) + std::to_string(worksheet_row);
                if (!videos[video].available || !std::isfinite(videos[video].values[row]))
                {
                    sheet << inline_string_cell(address, "-", 3);
                }
                else
                {
                    sheet << number_cell(address, videos[video].values[row]);
                }
            }

            sheet << "</row>";
        }

        sheet << "</sheetData><autoFilter ref=\"A1:G13\"/>"
              << "<pageMargins left=\"0.25\" right=\"0.25\" top=\"0.5\" bottom=\"0.5\" header=\"0.2\" footer=\"0.2\"/>"
              << "</worksheet>";
        return sheet.str();
    }

    std::vector<zip_entry> create_workbook_entries(const std::array<report_video_results, 6>& videos)
    {
        return {
            {
                "[Content_Types].xml",
                "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
                "<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">"
                "<Default Extension=\"rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>"
                "<Default Extension=\"xml\" ContentType=\"application/xml\"/>"
                "<Override PartName=\"/xl/workbook.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml\"/>"
                "<Override PartName=\"/xl/worksheets/sheet1.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml\"/>"
                "<Override PartName=\"/xl/styles.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.styles+xml\"/>"
                "</Types>"
            },
            {
                "_rels/.rels",
                "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
                "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">"
                "<Relationship Id=\"rId1\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument\" Target=\"xl/workbook.xml\"/>"
                "</Relationships>"
            },
            {
                "xl/workbook.xml",
                "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
                "<workbook xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\" "
                "xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\">"
                "<sheets><sheet name=\"Отчёт\" sheetId=\"1\" r:id=\"rId1\"/></sheets></workbook>"
            },
            {
                "xl/_rels/workbook.xml.rels",
                "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
                "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">"
                "<Relationship Id=\"rId1\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet\" Target=\"worksheets/sheet1.xml\"/>"
                "<Relationship Id=\"rId2\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles\" Target=\"styles.xml\"/>"
                "</Relationships>"
            },
            {
                "xl/styles.xml",
                "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
                "<styleSheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\">"
                "<fonts count=\"2\"><font><sz val=\"11\"/><name val=\"Calibri\"/></font>"
                "<font><b/><color rgb=\"FFFFFFFF\"/><sz val=\"11\"/><name val=\"Calibri\"/></font></fonts>"
                "<fills count=\"3\"><fill><patternFill patternType=\"none\"/></fill>"
                "<fill><patternFill patternType=\"gray125\"/></fill>"
                "<fill><patternFill patternType=\"solid\"><fgColor rgb=\"FF1F4E78\"/><bgColor indexed=\"64\"/></patternFill></fill></fills>"
                "<borders count=\"2\"><border><left/><right/><top/><bottom/><diagonal/></border>"
                "<border><left style=\"thin\"><color auto=\"1\"/></left><right style=\"thin\"><color auto=\"1\"/></right>"
                "<top style=\"thin\"><color auto=\"1\"/></top><bottom style=\"thin\"><color auto=\"1\"/></bottom><diagonal/></border></borders>"
                "<cellStyleXfs count=\"1\"><xf numFmtId=\"0\" fontId=\"0\" fillId=\"0\" borderId=\"0\"/></cellStyleXfs>"
                "<cellXfs count=\"4\"><xf numFmtId=\"0\" fontId=\"0\" fillId=\"0\" borderId=\"0\" xfId=\"0\"/>"
                "<xf numFmtId=\"0\" fontId=\"1\" fillId=\"2\" borderId=\"1\" xfId=\"0\" applyFont=\"1\" applyFill=\"1\" applyBorder=\"1\" applyAlignment=\"1\"><alignment horizontal=\"center\" vertical=\"center\"/></xf>"
                "<xf numFmtId=\"0\" fontId=\"0\" fillId=\"0\" borderId=\"1\" xfId=\"0\" applyBorder=\"1\" applyAlignment=\"1\"><alignment horizontal=\"center\" vertical=\"center\"/></xf>"
                "<xf numFmtId=\"0\" fontId=\"0\" fillId=\"0\" borderId=\"1\" xfId=\"0\" applyBorder=\"1\" applyAlignment=\"1\"><alignment horizontal=\"left\" vertical=\"center\"/></xf></cellXfs>"
                "<cellStyles count=\"1\"><cellStyle name=\"Normal\" xfId=\"0\" builtinId=\"0\"/></cellStyles></styleSheet>"
            },
            {
                "xl/worksheets/sheet1.xml",
                create_worksheet(videos)
            }
        };
    }

    bool write_zip(const std::filesystem::path& path, std::vector<zip_entry>& entries, std::string& error_message)
    {
        std::ofstream output(path, std::ios::binary | std::ios::trunc);
        if (!output)
        {
            error_message = "Unable to open the report file for writing.";
            return false;
        }

        for (zip_entry& entry : entries)
        {
            if (entry.name.size() > 0xFFFFu || entry.contents.size() > 0xFFFFFFFFu)
            {
                error_message = "The report contains an item that is too large.";
                return false;
            }

            const std::streamoff offset = output.tellp();
            if (offset < 0 || static_cast<std::uint64_t>(offset) > 0xFFFFFFFFu)
            {
                error_message = "The report file is too large.";
                return false;
            }
            entry.local_header_offset = static_cast<std::uint32_t>(offset);
            entry.crc = crc32(entry.contents);

            write_u32(output, 0x04034B50u);
            write_u16(output, 20);
            write_u16(output, 0);
            write_u16(output, 0);
            write_u16(output, 0);
            write_u16(output, 0x0021);
            write_u32(output, entry.crc);
            write_u32(output, static_cast<std::uint32_t>(entry.contents.size()));
            write_u32(output, static_cast<std::uint32_t>(entry.contents.size()));
            write_u16(output, static_cast<std::uint16_t>(entry.name.size()));
            write_u16(output, 0);
            output.write(entry.name.data(), static_cast<std::streamsize>(entry.name.size()));
            output.write(entry.contents.data(), static_cast<std::streamsize>(entry.contents.size()));
        }

        const std::streamoff central_directory_offset_stream = output.tellp();
        if (central_directory_offset_stream < 0 ||
            static_cast<std::uint64_t>(central_directory_offset_stream) > 0xFFFFFFFFu)
        {
            error_message = "The report file is too large.";
            return false;
        }
        const std::uint32_t central_directory_offset =
            static_cast<std::uint32_t>(central_directory_offset_stream);

        for (const zip_entry& entry : entries)
        {
            write_u32(output, 0x02014B50u);
            write_u16(output, 20);
            write_u16(output, 20);
            write_u16(output, 0);
            write_u16(output, 0);
            write_u16(output, 0);
            write_u16(output, 0x0021);
            write_u32(output, entry.crc);
            write_u32(output, static_cast<std::uint32_t>(entry.contents.size()));
            write_u32(output, static_cast<std::uint32_t>(entry.contents.size()));
            write_u16(output, static_cast<std::uint16_t>(entry.name.size()));
            write_u16(output, 0);
            write_u16(output, 0);
            write_u16(output, 0);
            write_u16(output, 0);
            write_u32(output, 0);
            write_u32(output, entry.local_header_offset);
            output.write(entry.name.data(), static_cast<std::streamsize>(entry.name.size()));
        }

        const std::streamoff end_of_directory_stream = output.tellp();
        if (end_of_directory_stream < 0 ||
            static_cast<std::uint64_t>(end_of_directory_stream) > 0xFFFFFFFFu)
        {
            error_message = "The report file is too large.";
            return false;
        }
        const std::uint32_t central_directory_size =
            static_cast<std::uint32_t>(end_of_directory_stream) - central_directory_offset;

        write_u32(output, 0x06054B50u);
        write_u16(output, 0);
        write_u16(output, 0);
        write_u16(output, static_cast<std::uint16_t>(entries.size()));
        write_u16(output, static_cast<std::uint16_t>(entries.size()));
        write_u32(output, central_directory_size);
        write_u32(output, central_directory_offset);
        write_u16(output, 0);

        output.flush();
        if (!output)
        {
            error_message = "An error occurred while writing the report file.";
            return false;
        }

        return true;
    }

    bool replace_report_file(
        const std::filesystem::path& temporary_path,
        const std::filesystem::path& output_path,
        std::string& error_message
    )
    {
#ifdef _WIN32
        if (!MoveFileExW(
                temporary_path.c_str(),
                output_path.c_str(),
                MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
        {
            const DWORD error_code = GetLastError();
            error_message = "Unable to replace the report file: " +
                            std::system_category().message(static_cast<int>(error_code)) +
                            ". Close the workbook if it is open in another application.";
            return false;
        }
#else
        std::error_code error;
        std::filesystem::rename(temporary_path, output_path, error);
        if (error)
        {
            error_message = "Unable to replace the report file: " + error.message();
            return false;
        }
#endif

        return true;
    }
}

bool write_report_xlsx(
    const std::filesystem::path& output_path,
    const std::array<report_video_results, 6>& videos,
    std::string& error_message
)
{
    std::vector<zip_entry> entries = create_workbook_entries(videos);
    static std::atomic<std::uint64_t> temporary_file_counter = 0;
    const auto timestamp = std::chrono::steady_clock::now().time_since_epoch().count();
    std::filesystem::path temporary_path = output_path;
    temporary_path += ".tmp." + std::to_string(timestamp) + "." +
                      std::to_string(temporary_file_counter.fetch_add(1));

    if (!write_zip(temporary_path, entries, error_message))
    {
        std::error_code cleanup_error;
        std::filesystem::remove(temporary_path, cleanup_error);
        if (cleanup_error)
        {
            error_message += " Temporary file cleanup also failed: " + cleanup_error.message();
        }
        return false;
    }

    if (replace_report_file(temporary_path, output_path, error_message))
    {
        return true;
    }

    std::error_code cleanup_error;
    std::filesystem::remove(temporary_path, cleanup_error);
    if (cleanup_error)
    {
        error_message += " Temporary file cleanup also failed: " + cleanup_error.message();
    }
    return false;
}
