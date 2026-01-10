#pragma once

#include "searchable_bag.hpp"

class set {
    private:
        searchable_bag *bag;
    public:
        set(searchable_bag &b) : bag(&b) {};
        set(const set &b) : bag(b.bag) {};
        virtual ~set() {};
        set &operator=(const set &b) {if (this != &b) bag = b.bag; return *this;}
        void insert(int v) {if (!bag->has(v)) bag->insert(v);}
        void insert(int *values, int size){
            if(!values || size <= 0)
                return;
            for (int i = 0; i < size; i++)
                if(!bag->has(values[i]))
                    bag->insert(values[i]);
        }
        bool has(int v) const {return bag->has(v);}
        void print() const { bag->print();}
        void clear() {bag->clear();}

        const searchable_bag &get_bag() {return *this->bag;}

};