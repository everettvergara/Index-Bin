#include <iostream>
#include "index_bin.hpp"

using namespace g80;
auto main(const int argc, const char *argv[]) -> int {

    // using yyy = unsigned char;
    // index_table<yyy> table(10);

    index_bin<uint32_t> ib(10);
    ib.use(1);
    ib.use(7);
    ib.use(5);
    ib.use(2);

    ib.unuse(7);
    ib.unuse(1);
    ib.unuse(2);
    ib.unuse(5);   


    ib.use(3);
    ib.use(2);
    ib.use(9);

    index_bin<uint32_t> ib2 = ib;

    std::cout << "Used:\n";
    for (auto i = ib2.cbegin_used(); i != ib2.cend_used(); ++i)
        std::cout << *i << "\n";

    std::cout << "Unused:\n";
    for (auto i = ib2.cbegin_unused(); i != ib2.cend_unused(); ++i)
        std::cout << *i << "\n";

    std::cout << "Mapper:\n";
    for (auto i = 0; i < 10; ++i) {
        std::cout << i << " - " << ib2.get_mapper()[i] << "\n";
    }


    std::cout << "Start of ununsed ix: " << ib2.start_of_unused_ix();
} 