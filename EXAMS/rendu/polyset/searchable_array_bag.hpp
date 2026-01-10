#pragma once

#include "array_bag.hpp"
#include "searchable_bag.hpp"


class searchable_array_bag : public array_bag, public searchable_bag {
    public:
        searchable_array_bag() : array_bag() {}
        searchable_array_bag(const searchable_array_bag &b) : array_bag(b) {}
        searchable_array_bag &operator=(const searchable_array_bag &b) {if (this != &b) array_bag::operator=(b); return *this;}
        ~searchable_array_bag() {}

        virtual bool has(int v) const {
            for (int i = 0; i < size; i++)
                if(data[i] == v)
                    return true;
            return false;
        }
};