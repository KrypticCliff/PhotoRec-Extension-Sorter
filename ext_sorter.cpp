#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

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
                std::cout << "Before: " << file_name.length() << "\n";
                file_name.erase(count_ext.length(), count_ext.length());
                std::cout << "After: " << file_name.length() << "\n";
                file_name = file_name + count_ext;
                // std::cout << file_name.size() - count_ext.size() << "\n";
            }

            counter++;
            file_dest = (p/ext/file_name);
        }
        return file_dest;
    } else
        return file_dest;

} // If Statement

int main(int argc, char** argv) {
//  Checks if 1 path to location is found.
    if (argc < 2 || argc >= 3) {
        std::cout << "Input Location of Path to Sort.\n";
        return -1;
    }

    std::cout << "Location: " << argv[1] << "\n";
    fs::path p(argv[1]);
    fs::path cur_p("./");
    fs::directory_iterator root_begin(p), end;

//  Checks if directory path is a directory
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
            //std::cout << sub_begin->path() << "\n";

            // If folder !exists, create folder extension folder
            if (!fs::exists(p/_file_ext)) {
                fs::create_directory(p/_file_ext);
            }

            // file_d "backup_path/name_of_ext/filename"
            // fs::path file_dest(p/file_ext/file_name);
            fs::path file_dest(file_exists(p, file_ext, file_name));
            fs::path file_src(sub_begin->path());

            fs::copy(file_src, file_dest);

// Current issue: Same name files cause issues.
        } // For Loop 1
    } // For Loop 2
} // Main
