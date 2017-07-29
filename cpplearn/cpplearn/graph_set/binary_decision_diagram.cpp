#include "binary_decision_diagram.hpp"

namespace cpplearn {
namespace graph_set {

auto pair_(unsigned a, unsigned b) -> unsigned {
    return ((a+b)*(a+b+1) / 2) + a;
}

auto triple_(unsigned a, unsigned b, unsigned c) -> unsigned {
    return pair_(c, pair_(a, b));
}

bdd::bdd(int v, int ptr, std::shared_ptr<bdd> hi, std::shared_ptr<bdd> lo)
    : index(v), val(ptr), hi(hi), lo(lo) { }

auto bdd::make_node(int v, int ptr, std::shared_ptr<bdd> hi, std::shared_ptr<bdd> lo) -> std::shared_ptr<bdd> {
    unsigned hsh = node_hash(v, hi->val, lo->val);
    if(table[hsh] == nullptr) {
        table[hsh] = std::shared_ptr<bdd>(new bdd(v, ptr+1, hi, lo));
        return table[hsh];
    }

    std::shared_ptr<bdd> node = table[hsh];

    while(node->next && (node->index != v || node->hi != hi || node->lo != lo)) {
        node = node->next;
    }

    if(node->index != v || node->hi != hi || node->lo != lo) {
        std::shared_ptr<bdd> new_node = std::shared_ptr<bdd>(new bdd(v, ptr+1, hi, lo));
        node->next = new_node;
        return new_node;
    }

    return node;
}

auto bdd::restrict(std::shared_ptr<bdd> subtree, int v, bool b) -> std::shared_ptr<bdd> {
    if(subtree->index > v) return subtree;
    else if(subtree->index < v) {
        return make_node(subtree->index,
                subtree->val,
                restrict(subtree->hi, v, b),
                restrict(subtree->lo, v, b));
    }
    else {
        if(v) return restrict(subtree->hi, v, b);
        else return restrict(subtree->lo, v, b);
    }
}

auto bdd::node_hash(int v, unsigned lo, unsigned hi) -> unsigned {
    return triple_(v, lo, hi) % node_size;
}

} // graph_set
} // cpplearn
