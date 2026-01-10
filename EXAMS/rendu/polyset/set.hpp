#pragma once

#include "searchable_bag.hpp"


class set {
    private:
        searchable_bag *bag;
    public:
        set(searchable_bag &b) : bag(&b) {};
        set(const set &s) : bag(s.bag) {};
        set &operator=(const set &s) {if (this != &s) bag = s.bag; return *this;}
        ~set() {};

        bool has(int v) const {return bag->has(v);}

        void insert(int v) {if (!bag->has(v)) bag->insert(v);}
        void insert(int *v, int size ) {
            if (!v || size <= 0) return;
            for (int i =0; i < size; i++)
                if (!bag->has(v[i])) bag->insert(v[i]);
        }
        void print() const {bag->print();}
        void clear() {bag->clear();}

        const searchable_bag &get_bag() {return *this->bag;}


 };