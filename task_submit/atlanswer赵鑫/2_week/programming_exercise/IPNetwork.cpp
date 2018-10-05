/**
 * @file IPNetwork.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2018-10-04
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "Network.hpp"

using namespace std;

int main() {
    FILE* input = fopen("../input.dat", "r");
    FILE* output = fopen("../output.dat", "w");
    if (!input || !output) {
        perror("File opening failed.");
        return EXIT_FAILURE;
    }

    Network network(input);
    fclose(input);
    network.show(output);
    fclose(output);

    return 0;
}