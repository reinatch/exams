#pragma once

#include "tree_bag.hpp"
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