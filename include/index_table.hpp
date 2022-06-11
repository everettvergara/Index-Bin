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
        
        // Maximum values that can be stored in index table = 2^size_in_bits(uint_type) - 1
        // Index Table uses ~static_cast<uint_type>(0) as invalid ix

        index_table(uint_type size) : size_(size) {
            reset(size_);
        }
        
        auto copy_index_table(const index_table &rhs) -> void {
            reset(size_);
            std::copy(rhs.ix_bin_, rhs.ix_bin_ + size_, ix_bin_);
            std::copy(rhs.bin_loc_, rhs.bin_loc_ + size_, bin_loc_);
        }

        auto delete_index_bin_loc() -> void {
            delete []ix_bin_;
            delete []bin_loc_;
            ix_bin_ = {nullptr};
            bin_loc_ = {nullptr};
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
            size_ = rhs.size_;
            last_ix_ = rhs.last_ix_;
            copy_index_table(rhs);
            return *this;
        }

        auto operator=(index_table &&rhs) -> index_table & {
            
            size_ = rhs.size_;
            last_ix_ = rhs.last_ix_;
            
            delete_index_bin_loc();
            ix_bin_ = rhs.ix_bin_;
            bin_loc_ = rhs.bin_loc_;

            rhs.size_ = {0};
            rhs.last_ix_ = rhs.INVALID_IX;
            rhs.ix_bin_ = {nullptr};
            rhs.bin_loc_ = {nullptr};

            return *this;
        }

        ~index_table() {
            delete_index_bin_loc();
        }

        auto reset(uint_type size) -> void {

            delete []ix_bin_;
            delete []bin_loc_;
            ix_bin_ = new uint_type[size_];
            bin_loc_ = new uint_type[size_];

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

    private:
    
        static constexpr uint_type INVALID_IX {~static_cast<uint_type>(0)};
        uint_type size_{0};
        uint_type last_ix_{INVALID_IX};  
        uint_type *ix_bin_{nullptr}, *bin_loc_{nullptr};
    };

}

#endif