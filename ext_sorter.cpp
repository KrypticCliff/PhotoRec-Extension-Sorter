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
    fs::directory_iterator begin(p), end;

//  Checks if directory path is a directory
    if (!is_directory(p)) {
        std::cerr << "Could not find location.\n";
        return -1;
    }

    for (; begin != end; begin++) {
        std::cout << begin->path().extension() << "\n";
    }
}
