#include <iostream>
#include "index_table.hpp"

using namespace g80;
auto main(const int argc, const char *argv[]) -> int {

    index_table<uint> table(10);
    table.add_to_bin(2);
    table.add_to_bin(1); 
    table.add_to_bin(0);
    table.add_to_bin(3);
    

    std::cout << "bin_ptr: " << table.get_bin_ptr() << "\n";
    // for (auto &ix : table) {
    //     std::cout << ix << "\n";
    // }


} 