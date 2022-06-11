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

namespace g80 {

    // #define UNSAFE_OPTIM

    template<typename uint_type>
    class index_table {
    

    public:
        // Maximum values that can be stored in index table = 2^sizeof(uint_type) - 1
        // Index Table uses ~static_cast<uint_type>(0) as invalid ix

        index_table(uint_type size) : size_(size) {reset(size_);}

        auto reset(uint_type size) -> void {

            if (size != size_) {
                delete []ix_bin_;
                delete []bin_loc_;
                ix_bin_ = new uint_type[size_];
                bin_loc_ = new uint_type[size_];
            }

            last_ix_ = INVALID_IX;
            memset(bin_loc_, ~0, sizeof(uint_type) * size_);
        }

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

    private:
    
        static constexpr uint_type INVALID_IX {~static_cast<uint_type>(0)};
        uint_type size_;
        uint_type *ix_bin_{nullptr}, *bin_loc_{nullptr};
        uint_type last_ix_{INVALID_IX};  
    };

    // template<typename uint_type>
    // constexpr uint_type index_table<uint_type>::INVALID_IX {~static_cast<uint_type>(0)};
}

#endif