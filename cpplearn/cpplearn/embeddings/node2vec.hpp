#ifndef NODE2VEC_HPP
#define NODE2VEC_HPP

#include <map>
#include <set>
#include <tuple>
#include <utility>

#include "embeddings/abstract_embeddings.hpp"
#include "data_type.hpp"

namespace cpplearn {
namespace embeddings {

template<typename T>
class node2vec : public abstract_embeddings<T> {
    private:
        T G;
        T W;
        std::set<std::pair<i64, i64> > E;
        bool is_directed;
        f64 p;
        f64 q;

        std::map<i64, std::tuple<vecf64, vecf64> > alias_nodes;
        std::map<std::pair<i64, i64>, std::tuple<vecf64, vecf64> > alias_edges;

        auto node2vec_walk(i32, i64) -> veci64;
        auto preprocess() -> void;
        auto alias_setup(vecf64) -> std::tuple<vecf64, vecf64>;
        auto get_alias_edge(i64, i64) -> std::tuple<vecf64, vecf64>;
        auto alias_draw(vecf64, vecf64) -> i64;
    public:
        node2vec();
        node2vec(T, T, std::set<std::pair<i64, i64> >, bool, double, double);
        ~node2vec();

        auto simulate_walk(i32, i32) -> mati64;
};

} // namespace embeddings
} // namespace cpplearn

#endif
