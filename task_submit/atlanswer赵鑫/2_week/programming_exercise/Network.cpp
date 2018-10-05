#include "Network.hpp"

Network::Network(FILE* input) {
    fscanf(input, "%d", &ipNumber);
    ipAddressList = new Address[ipNumber];
    for (int i{0}; i < ipNumber; ++i)
        ipAddressList[i].init(input);
    calculate();
}

Network::~Network() {
    delete[] ipAddressList;
    ipAddressList = NULL;
}

void Network::calculate() {
    Address *min{&ipAddressList[0]},
            *max{&ipAddressList[0]};
    for (int i{1}; i < ipNumber; ++i) {
        if (ipAddressList[i].ipAddress > max->ipAddress)
            max = &ipAddressList[i];
        if (ipAddressList[i].ipAddress < min->ipAddress)
            min = &ipAddressList[i];
    }

    uint32_t diff{max->ipAddress ^ min->ipAddress};
    short CIDRsufx{};
    while (diff != 0) {
        ++CIDRsufx;
        diff >>= 1;
    }

    networkAddress.ipAddress = min->ipAddress;
    networkAddress.ipAddress >>= CIDRsufx;
    networkAddress.ipAddress <<= CIDRsufx;

    networkMask.ipAddress = ~networkMask.ipAddress;
    networkMask.ipAddress >>= CIDRsufx;
    networkMask.ipAddress <<= CIDRsufx;
}

void Network::printIP(FILE* output, Address& ip) {
    uint32_t mask{0x000000ff};
    for (int shift{24}; shift > 0; shift -= 8)
        fprintf(output, "%u.", (ip.ipAddress & (mask << shift)) >> shift);
    fprintf(output, "%u", ip.ipAddress & mask);
}

void Network::show(FILE* output) {
    printIP(output, networkAddress);
    fprintf(output, "\n");
    printIP(output, networkMask);
}

void Network::display() {
    for (int i{0}; i < ipNumber; ++i) {
        ipAddressList[i].print();
        printf("\n");
    }
}

Address Network::provide(int n) {
    return ipAddressList[--n];
}