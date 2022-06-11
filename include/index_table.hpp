/**
 * @file index_table.hpp
 * @author Everett Gaius S. Vergara (me@everettgaius.com)
 * @brief A fast but expensive datastruct for hashtables 
 * @version 0.1
 * @date 2022-06-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef INDEX_TABLE_HPP
#define INDEX_TABLE_HPP

#include <array>

namespace g80 {

    // #define UNSAFE_OPTIM

    template<typename uint_type, uint_type N>
    class index_table {
    

    public:
    
        index_table() {reset();}

        auto reset() -> void {
            bin_ptr_ = {invalid_ptr_};
            memset(bin_loc_.data(), ~0, sizeof(uint_type) * N);
        }

        auto add_to_bin(uint_type ix) -> bool {
            #ifndef UNSAFE_OPTIM
            if (ix >= N) return false;
            if (bin_loc_[ix] != invalid_ptr_) return false;
            #endif

            ix_bin_[++bin_ptr_] = ix;
            bin_loc_[ix] = bin_ptr_;
            return bin_ptr_ != invalid_ptr_;
        }

        auto remove_from_bin(uint_type ix) -> bool {
            #ifndef UNSAFE_OPTIM
            if (ix >= N) return false;
            if (bin_loc_[ix] == invalid_ptr_) return false;
            #endif

            std::swap(ix_bin_[bin_loc_[ix]], ix_bin_[bin_ptr_--]);
            bin_loc_[ix] = invalid_ptr_;
            return true;
        }

        inline auto size() -> uint_type {
            return bin_ptr_ + 1;
        }

        inline auto get_ix_bin() const -> const std::array<uint_type, N> & {return ix_bin_;}
        inline auto get_bin_loc() const -> const std::array<uint_type, N> & {return bin_loc_;}
        inline auto get_bin_ptr() const -> uint_type {return bin_ptr_;}

        

    public:

        struct iterator {
        private:
            uint_type *ptr;
        
        public:
            iterator(uint_type *begin) :  ptr = begin {}
            auto operator*() const -> uint_type & {return *ptr;}
            auto operator->() -> uint_type * {return ptr;}
            auto operator++() -> iterator & {++ptr; return *this;}
            auto operator++(int) -> iterator {iterator t = *this; ++ptr; return t;}
            friend auto operator==(const iterator &lhs, const iterator &rhs) -> bool {return lhs.ptr == rhs.ptr;}
            friend auto operator!=(const iterator &lhs, const iterator &rhs) -> bool {return lhs.ptr != rhs.ptr;}
        };

        auto begin() const -> iterator {return iterator(ix_bin_.data())}
        auto end() const -> iterator {return iterator(ix_bin_.data() + bin_ptr_ + 1)}
        auto cbegin() const -> iterator {return iterator(ix_bin_.data())}
        auto cend() const -> iterator {return iterator(ix_bin_.data() + bin_ptr_ + 1)}

    // Private Variables of index_table

    private:
    
        const uint_type invalid_ptr_{~static_cast<uint_type>(0)};
        std::array<uint_type, N> ix_bin_;
        std::array<uint_type, N> bin_loc_;
        uint_type bin_ptr_{invalid_ptr_};  
    };
}

#endif