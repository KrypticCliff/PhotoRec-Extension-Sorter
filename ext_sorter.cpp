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

            // Remove "." from file extension
            file_ext.erase(0,1);

            // Test statement
            std::cout << sub_begin->path() << "\n";

            // If folder !exists, create folder extension folder
            if (!fs::exists(p/file_ext)) {
                fs::create_directory(p/file_ext);
            }

            // file_d "backup_path/name_of_ext/filename"
            // file_s iterated file 
            fs::path file_dest(p/file_ext/file_name);
            fs::path file_src(sub_begin->path());

            fs::copy(file_src, file_dest);

/*            fs::directory_iterator inner_sub_p("./");
            for (; inner_sub_p != end; inner_sub_p++) {
                std::string sub_file_name = inner_sub_p->path().extension().string();
                if (file_ext == sub_file_name) {

                }
            }
*/

            //fs::rename(sub_begin->path(),)
        } // For Loop 1
    } // For Loop 2
} // Main
