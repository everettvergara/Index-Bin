/**
 * @file index_bin.hpp
 * @author Everett Gaius S. Vergara (me@everettgaius.com)
 * @brief A fast but expensive datastruct for hashtables 
 * @version 0.1
 * @date 2022-06-10
 * 
 * @copyright Copyright (c) 2022
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * 
 * @note: 
 * 
 * Index Bin is a datastructure concept wherein you have an N-sized vector
 * paritioned into used and unused indexes. 
 * 
 * Indices under each partition are not in any particular order. But even 
 * though this is the case, searching for an index will take O(1) because
 * of the index mapper, which monitors the position of the index under the
 * bin.
 * 
 * Below is a sample data structure of a 10-sized element Index Bin.
 * 
 * 
 * Bin:
 * Used     | Unused
 * 0 1 2 3    4 5 6 7 8 9 10
 * 4 5 2 10 | 9 0 1 3 6 7 8 
 * 
 * Index Mapper
 * 0 1 2 3 4 5 6 7 8  9 10
 * 5 6 2 7 0 1 8 9 10 4 3  
 * 
 */

#ifndef INDEX_TABLE_HPP
#define INDEX_TABLE_HPP

#include <type_traits>

namespace g80 {

    /**
     * Uncomment #define UNSAFE_OPTIM if you are sure that your 
     * program won't go beyond the boundaries of uint_type
     * 
     * #define UNSAFE_OPTIM 
     * 
     */
    
    #define UNSAFE_OPTIM

    /**
     * Template class proper for 
     * index_table
     * 
     */

    template<typename uint_type>
    class index_table {
    
    /**
     * Template validation
     * 
     */

    static_assert(
        std::is_same<uint_type, unsigned char>::value || std::is_same<uint_type, unsigned int>::value || 
        std::is_same<uint_type, unsigned short>::value || std::is_same<uint_type, unsigned long>::value || 
        std::is_same<uint_type, unsigned long long>::value || 

        std::is_same<uint_type, uint8_t>::value || std::is_same<uint_type, uint16_t>::value || 
        std::is_same<uint_type, uint32_t>::value || std::is_same<uint_type, uint64_t>::value,

        "Must be of unsigned integral type");

    /**
     * Constructor, Destructor and 
     * Assignment Helpers
     * 
     */

    private:

        auto del_ix_bin_loc() -> void {
            delete []ix_bin_;
            delete []bin_loc_;
            ix_bin_ = {nullptr};
            bin_loc_ = {nullptr};
        }

        auto new_ix_bin_loc() -> void {
            ix_bin_ = new uint_type[size_];
            bin_loc_ = new uint_type[size_];
        }

        auto reset_bin_loc_() -> void {
            std::fill_n(bin_loc_, size_, INVALID_IX);
        }
    
        auto copy_index_table(const index_table &rhs) -> void {
            std::copy(rhs.ix_bin_, rhs.ix_bin_ + size_, ix_bin_);
            std::copy(rhs.bin_loc_, rhs.bin_loc_ + size_, bin_loc_);
        }

    public:

        auto reset(const uint_type size) {
            size_(size);
            last_ix_ = {INVALID_IX};
            reset();
        }

        
    /**
     * Constructor, Destructor and 
     * Assignment Functions
     * 
     */

    public:
        
        index_table(uint_type size) : size_(size) {
            new_ix_bin_loc();
            reset_bin_loc_();
        }

        index_table(const index_table &rhs) : size_(rhs.size_), last_ix_(rhs.last_ix_) {
            copy_index_table(rhs);
        }

        index_table(index_table &&rhs) : size_(rhs.size_), last_ix_(rhs.last_ix_), ix_bin_(rhs.ix_bin_), bin_loc_(rhs.bin_loc_) {
            rhs.size_ = {0};
            rhs.last_ix_ = rhs.INVALID_IX;
            rhs.ix_bin_ = {nullptr};
            rhs.bin_loc_ = {nullptr};
        }

        auto operator=(const index_table &rhs) -> index_table & {
            del_ix_bin_loc();
            
            size_ = rhs.size_;
            last_ix_ = rhs.last_ix_;
            new_ix_bin_loc();
            copy_index_table(rhs);
            return *this;
        }

        auto operator=(index_table &&rhs) -> index_table & {
            
            del_ix_bin_loc();
            
            size_ = rhs.size_;
            last_ix_ = rhs.last_ix_;
            ix_bin_ = rhs.ix_bin_;
            bin_loc_ = rhs.bin_loc_;

            rhs.size_ = {0};
            rhs.last_ix_ = rhs.INVALID_IX;
            rhs.ix_bin_ = {nullptr};
            rhs.bin_loc_ = {nullptr};

            return *this;
        }

        ~index_table() {
            del_ix_bin_loc();
        }

    /**
     * Public Interface
     * 
     */

    public:

        auto add_to_bin(uint_type ix_to_add) -> bool {
            #ifndef UNSAFE_OPTIM
            if (ix_to_add >= size_) return false;
            if (bin_loc_[ix_to_add] != INVALID_IX) return false;
            #endif

            ix_bin_[++last_ix_] = ix_to_add;
            bin_loc_[ix_to_add] = last_ix_;
            return true;
        }

        auto remove_from_bin(uint_type ix_to_remove) -> bool {
            #ifndef UNSAFE_OPTIM
            if (ix_to_remove >= size_) return false;
            if (bin_loc_[ix_to_remove] == INVALID_IX) return false;
            #endif

            std::swap(ix_bin_[bin_loc_[ix_to_remove]], ix_bin_[last_ix_--]);
            bin_loc_[ix_to_remove] = INVALID_IX;
            return true;
        }

        inline auto size() -> uint_type {
            return last_ix_ + 1;
        }

        inline auto get_ix_bin() const -> const uint_type *& {return ix_bin_;}
        inline auto get_bin_loc() const -> const uint_type *& {return bin_loc_;}
        inline auto get_bin_ptr() const -> uint_type {return last_ix_;}

    /**
     * Iterator functions
     * 
     */

    public:

        struct iterator {
        private:
            uint_type *ptr;
        public:
            iterator(uint_type *data) {ptr = data;}
            auto operator*() -> uint_type & {return *ptr;}
            auto operator->() -> uint_type * {return ptr;}
            auto operator++() -> iterator & {++ptr; return *this;};
            auto operator++(int) -> iterator {iterator t = *this; ++ptr; return t;};
            friend auto operator ==(const iterator &lhs, const iterator &rhs) -> bool {return lhs.ptr == rhs.ptr;}
            friend auto operator !=(const iterator &lhs, const iterator &rhs) -> bool {return lhs.ptr != rhs.ptr;}
        };

        auto begin() const -> iterator {return iterator(ix_bin_);}
        auto end() const -> iterator {return iterator(ix_bin_ + last_ix_ + 1);}

    /**
     * Internal table index variables 
     * 
     */

    private:
    
        static constexpr uint_type INVALID_IX = ~static_cast<uint_type>(0);
        uint_type size_{0};
        uint_type last_ix_{INVALID_IX};  
        uint_type *ix_bin_{nullptr}, *bin_loc_{nullptr};
    };
}

#endif