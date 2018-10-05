#include <cstdio>
#include <cstdlib>
#include <cstdint>

using namespace std;

struct Address {
    //Initializer
    void init(FILE*);
    //Structure data
    uint32_t ipAddress{};
    //Method print
    void print();
};