#include <iostream>
#include <string>
#include <regex>
#include <filesystem>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

std::string pattern_to_regex(const std::string& pattern) {
    std::string result;
    for (char c : pattern) {
        if (c == '*') {
            result += ".*";
        } else if (c == '.') {
            result += ".";
        } else {
            result += std::regex_replace(std::string(1, c), std::regex(R"([\^\$\.\|\?\*\+\(\)\[\]\{\}\\])"), R"(\\$&)");
        }
    }
    return result;
}

void rename_files(const fs::path& dir, const std::string& from, const std::string& to, bool use_regex) {
    std::string pattern = use_regex ? pattern_to_regex(from) : std::regex_replace(from, std::regex(R"([\^\$\.\|\?\*\+\(\)\[\]\{\}\\])"), R"(\\$&)");

    std::regex re(pattern);

    for (const auto& entry : fs::recursive_directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            std::string new_filename = std::regex_replace(filename, re, to);
            if (new_filename != filename) {
                fs::path new_path = entry.path().parent_path() / new_filename;
                if (!fs::exists(new_path)) {
                    fs::rename(entry.path(), new_path);
                    std::cout << "Renamed: " << filename << " -> " << new_filename << std::endl;
                } else {
                    std::cerr << "Error: " << new_filename << " already exists." << std::endl;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <directory> [-r] <from> <to>\n";
        return 1;
    }

    bool use_regex = false;
    int i = 1;

    std::string dir_str = argv[i++];

    if (std::string(argv[i]) == "-r") {
        use_regex = true;
        ++i;
    }

    if (argc - i < 2) {
        std::cerr << "Usage: " << argv[0] << " <directory> [-r] <from> <to>\n";
        return 1;
    }

    std::string from = argv[i++];
    std::string to = argv[i++];

    fs::path dir(dir_str);
    if (!fs::exists(dir) or !fs::is_directory(dir)) {
        std::cerr << "Directory does not exist or is not a directory: " << dir_str << "\n";
        return 1;
    }

    try {
        rename_files(dir, from, to, use_regex);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}