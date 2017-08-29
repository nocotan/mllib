/**
 * Zero-Supressed Binary Decision Diagram
 */

#ifndef ZDD_HPP
#define ZDD_HPP


struct dd_node {
    unsigned idx;
    unsigned value;
    bool is_base;

    dd_node* hi;
    dd_node* lo;

    node(int, int, bool, dd_node*, dd_node*,  is_base=false) noexcept;
};

struct dd_tree {
    unsigned idx;
    unsigned value;
    node* root;
}

class zdd {
};

#endif
