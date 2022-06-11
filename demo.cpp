#include <iostream>
#include "index_bin.hpp"

using namespace g80;
auto main(const int argc, const char *argv[]) -> int {

    // using yyy = unsigned char;
    // index_table<yyy> table(10);

    index_bin<uint32_t> ib(100);
    index_bin<uint32_t> ib2 = ib;


} 