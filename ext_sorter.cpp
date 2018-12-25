/*
    Current issues: Duplicate Files may add additional "_#" tags on name.
    Folders within sub_begin will not be accounted for and
    may cause issues.
*/

#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

// Function checks if file exists, if so iterate name i.e. file_1, file_2.
fs::path file_exists(fs::path p, std::string ext, std::string file_name) {
    fs::path file_dest(p/ext/file_name);

    if (fs::exists(file_dest)) {
        int counter = 1;

        while (fs::exists(file_dest)) {
            std::string file_name = file_dest.stem().string();
            std::string count_ext = "_" + std::to_string(counter) + "." + ext;

            if (counter < 2) {
                file_name = file_name + count_ext;

            } else {
                file_name.erase(count_ext.length(), count_ext.length());
                file_name = file_name + count_ext;
            }

            counter++;
            file_dest = (p/ext/file_name);
        } // While Statement

        return file_dest;
    }

    return file_dest;
} // If Statement


int main(int argc, char** argv) {
// Checks if 1 path to location is found.
    if (argc < 2 || argc >= 3) {
        std::cout << "Input Location of Path to Sort.\n";
        return -1;
    }

    std::cout << "Location: " << argv[1] << "\n";
    fs::path p(argv[1]);
    fs::path cur_p("./");
    fs::directory_iterator root_begin(p), end;

// Checks if directory path is a directory
    if (!fs::is_directory(p)) {
        std::cerr << "Could not find location.\n";
        return -1;
    }

// Iterates through ROOT directory
    for (; root_begin != end; root_begin++) {
        //std::cout << root_begin->path().string() << "\n";
        fs::directory_iterator sub_begin(root_begin->path());

// Iterates through SUB directory (Assuming filename recup_dir.#)
        for (; sub_begin != end; sub_begin++) {
            std::string file_name = sub_begin->path().filename().string();
            std::string file_ext  = sub_begin->path().extension().string();

// Remove "." from file extension named
            std::string _file_ext = file_ext.erase(0,1);

// Test statement
            std::cout << sub_begin->path() << "\n";

// If folder !exists, create folder extension folder
            if (!fs::exists(p/_file_ext))
                fs::create_directory(p/_file_ext);

// file_dest = "backup_path/name_of_ext/filename"
            fs::path file_dest(file_exists(p, file_ext, file_name));
            fs::path file_src(sub_begin->path());

            fs::copy(file_src, file_dest);

        } // For Loop 1
    } // For Loop 2
} // Main
