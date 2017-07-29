#ifndef BINARY_DECISION_DIAGRAM_HPP
#define BINARY_DECISION_DIAGRAM_HPP

#include <memory>
#include <vector>

namespace cpplearn {
namespace graph_set {

struct bdd {
    unsigned index;
    unsigned val;

    unsigned node_size;
    int nv = 0;

    std::shared_ptr<bdd> hi;
    std::shared_ptr<bdd> lo;
    std::shared_ptr<bdd> next;

    std::vector<std::shared_ptr<bdd>> table;

    bdd(int, int, std::shared_ptr<bdd>, std::shared_ptr<bdd>);

    auto make_node(int, int, std::shared_ptr<bdd>, std::shared_ptr<bdd>) -> std::shared_ptr<bdd>;
    auto restrict(std::shared_ptr<bdd>, int, bool) -> std::shared_ptr<bdd>;

    // TODO
    auto ite(std::shared_ptr<bdd>, std::shared_ptr<bdd>, std::shared_ptr<bdd>);


    private:
        auto node_hash(int, unsigned, unsigned) -> unsigned;
};

auto pair_(unsigned, unsigned) -> unsigned;
auto triple_(unsigned, unsigned, unsigned) -> unsigned;


} // namespace graph_set
} // namespace cpplearn

#endif
