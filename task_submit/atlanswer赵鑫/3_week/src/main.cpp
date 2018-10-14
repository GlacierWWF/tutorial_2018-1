#include "SSD.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "usage: ./test <image_path>" << std::endl;
        std::cout << "Argument number: " << argc << std::endl;
        return -1;
    }

    SSD image(argv[1]);

    image.playground();

    return 0;
}