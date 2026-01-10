#pragma once

#include "tree_bag.hpp"
#include "array_bag.hpp"
#include "searchable_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag {
    public:
        searchable_tree_bag() : tree_bag() {}
        searchable_tree_bag(const searchable_tree_bag &b) : tree_bag(b) {}
        searchable_tree_bag &operator=(const searchable_tree_bag &b) {if (this != &b) tree_bag::operator=(b); return *this;}
        ~searchable_tree_bag() {}

        virtual bool has(int v) const {
            node *current = tree;

            while(current){
                if(current->value == v)
                    return true;
                current = current->value > v ? current->l : current->r;
            }
            return false;
        }
};
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