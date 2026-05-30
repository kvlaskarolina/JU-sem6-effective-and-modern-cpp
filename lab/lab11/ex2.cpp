#include <iostream>
#include <filesystem>
#include <regex>
#include <string>
#include <string_view>
#include <fstream>

namespace fs = std::filesystem;

void printDirectory(std::string_view path) {
    const fs::path dir{path};

    if (!fs::exists(dir) || !fs::is_directory(dir)) {
        std::cerr << "Error: '" << path << "' is not a valid directory.\n";
        return;
    }

    for (const fs::directory_entry& entry : fs::directory_iterator{dir}) {
        char tag = ' ';
        if (fs::is_symlink(entry.symlink_status()))
            tag = 'L';
        else if (fs::is_directory(entry.status()))
            tag = 'D';
        else if (fs::is_regular_file(entry.status()))
            tag = 'F';

        std::uintmax_t size = 0;
        if (fs::is_regular_file(entry.status()))   
            size = fs::file_size(entry.path());

        std::cout << '[' << tag << "] "
                  << entry.path().filename().string()
                  << ' ' << size << '\n';
    }
}


void changeExtension(fs::path path, std::string fileNames, std::string_view newExtension) {
    if (!fs::exists(path) || !fs::is_directory(path)) {
        std::cerr << "Error: '" << path << "' is not a valid directory.\n";
        return;
    }

    const std::regex pattern{fileNames};

    for (const fs::directory_entry& entry : fs::directory_iterator{path}) {
        if (!fs::is_regular_file(entry.status()))
            continue;

        const std::string filename = entry.path().filename().string();

        if (!std::regex_match(filename, pattern))
            continue;

        fs::path dest = entry.path();
        dest.replace_extension(newExtension);

        if (dest == entry.path()) {
            std::cerr << "Skipping '" << filename
                      << "': source and destination are identical.\n";
            continue;
        }

        std::error_code ec;
        fs::copy_file(entry.path(), dest, fs::copy_options::overwrite_existing, ec);
        if (ec)
            std::cerr << "Failed to copy '" << filename << "': " << ec.message() << '\n';
        else
            std::cout << "Copied: " << filename
                      << " -> " << dest.filename().string() << '\n';
    }
}

int main() {
    printDirectory(".");

    return 0;
}

