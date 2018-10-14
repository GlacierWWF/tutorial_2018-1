#include "SSD.hpp"

int main(int argc, char** argv) {
    if (argc == 1 or argc > 3) {
        std::cout << "usage: ./test <image_path>" << std::endl;
        std::cout << "Argument number: " << argc - 1 << std::endl;
        return -1;
    }

    if (argc == 2) {
        std::cout << "Here" << std::endl;
        SSD image(argv[1]);
        image.readDigit();
    } else {
        SSD2 combine(argv[1], argv[2]);
        combine.combine();
    }

    return 0;
}