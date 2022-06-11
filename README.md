# Index Table

A C++ template for a fast but expensive index table. 

The maximum values that can be stored in an index_table class is:
    2 ^ no_of_bits(uint_type) - 1

Because index_table uses ~static_cast<uint_type>(0) as its invalid index
