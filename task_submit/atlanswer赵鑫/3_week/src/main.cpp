#include "SSD2.hpp"

int main(int argc, char** argv) {
    if (argc == 1 or argc > 3) {
        std::cout << "usage: ./test <image_path>" << std::endl;
        std::cout << "Argument number: " << argc - 1 << std::endl;
        return -1;
    }

    if (argc == 2) {
        SSD2 ONE_FUCKING_UNREADABLE_IMAGE(argv[1]);
        // SSD A_FUCKING_UNREADABLE_IMAGE(argv[1]);
        // A_FUCKING_UNREADABLE_IMAGE.readDigit();
    } else {
        SSD2 THE_MOTHER_OF_TWO_FUCKING_BLURRY_IMAGES(argv[1], argv[2]);
        THE_MOTHER_OF_TWO_FUCKING_BLURRY_IMAGES.readDigit();
    }

    return 0;
}