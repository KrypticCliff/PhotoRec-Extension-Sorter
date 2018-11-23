#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

int main(int argc, char** argv) {
//  Checks if 1 path to location is found.
    if (argc < 2 || argc >= 3) {
        std::cout << "Input Location of Path to Sort.\n";
        return -1;
    }

    std::cout << "Location: " << argv[1] << "\n";
    fs::path p(argv[1]);
    fs::directory_iterator root_begin(p), end;

//  Checks if directory path is a directory
    if (!fs::is_directory(p)) {
        std::cerr << "Could not find location.\n";
        return -1;
    }

    try {
        // Iterates through ROOT directory
        for (; root_begin != end; root_begin++) {
            std::cout << root_begin->path().string() << "\n";
            fs::directory_iterator sub_begin(root_begin->path());

            // Iterates through SUB directory (Assuming filename recup_dir.#)
            for (; sub_begin != end; sub_begin++) {
                // Remove "." from file extension
                // If folder !exists, create folder called file_ext

                std::string file_ext = sub_begin->path().extension().string();
                file_ext.erase(0,1);
                fs::path ext_p(file_ext);
                //std::cout << sub_begin->path().extension().string() << "\n";

                // Check if extension directory exists
                if (!fs::exists(ext_p)) {
                    fs::create_directory(ext_p);
                }
                else {
                    continue;
                }


            } // For Loop 1

        } // For Loop 2

    } // Try
    catch (int e) {
        std::cout << "An exception has occurred: " << e << "\n";
    }
} // Main
