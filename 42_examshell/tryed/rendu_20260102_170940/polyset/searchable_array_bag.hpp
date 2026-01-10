#pragma once

#include "searchable_bag.hpp"
#include "array_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag {
    public:
        searchable_array_bag() : array_bag() {};
        searchable_array_bag(const searchable_array_bag &src) : array_bag(src) {};
        ~searchable_array_bag() {};
        searchable_array_bag &operator=(const searchable_array_bag &src) {
            if (this != &src)
                array_bag::operator=(src);
            return *this;
        }
        virtual bool has(int value) const {
            for (int i = 0; i < size; ++i)
                if (data[i] == value)
                    return true;
            return false;
        }
};