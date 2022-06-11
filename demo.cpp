#include <iostream>
#include "index_bin.hpp"

using namespace g80;
auto main(const int argc, const char *argv[]) -> int {

    // using yyy = unsigned char;
    // index_table<yyy> table(10);

    index_bin<uint32_t> ib(10);
    ib.use(1);
    ib.use(5);
    ib.use(3);


    index_bin<uint32_t> ib2 = ib;

    std::cout << "Used:\n";
    for (auto i = ib.cbegin_used(); i != ib.cend_used(); ++i)
        std::cout << *i << "\n";

    std::cout << "Unsed:\n";
    for (auto i = ib.cbegin_unused(); i != ib.cend_unused(); ++i)
        std::cout << *i << "\n";

} 