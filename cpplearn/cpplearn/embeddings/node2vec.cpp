#include <algorithm>
#include <numeric>
#include <random>
#include <stack>
#include "embeddings/node2vec.hpp"
#include "ext_container.hpp"

namespace cpplearn {
namespace embeddings {

template<typename T>
node2vec<T>::node2vec() { }

template<typename T>
node2vec<T>::node2vec(T G, T W, std::set<std::pair<i64, i64> > E,
        bool is_directed, double p, double q)
  : G(G), W(W), E(E), is_directed(is_directed), p(p), q(q) { }

template<typename T>
node2vec<T>::~node2vec() { }

template<typename T>
auto node2vec<T>::simulate_walk(i32 num_walks, i32 walk_length) -> mati64 {
    mati64 walks;
    veci64 nodes(this->G.size());
    std::iota(nodes.begin(), nodes.end(), 0);

    for(int i=0; i<num_walks; ++i) {
        std::random_shuffle(nodes.begin(), nodes.end());
        for(const auto& node : nodes) {
            walks.push_back(this->node2vec_walk(walk_length, node));
        }
    }

    return walks;
}

template<typename T>
auto node2vec<T>::node2vec_walk(i32 walk_length, i64 start_node) -> veci64 {
    veci64 walk;
    walk.push_back(start_node);

    while(walk.size() < walk_length) {
        i64 cur = walk[walk.size()-1];
        auto cur_nbrs = G[cur];

        std::sort(cur_nbrs.begin(), cur_nbrs.end(), [=](auto a, auto b) {
            return W[cur][a] > W[cur][b];
        });

        if(cur_nbrs.size() > 0) {
            if(cur_nbrs.size() == 1) {
                auto&& alias_node = alias_nodes[cur];
                i64 ad = alias_draw(std::get<0>(alias_node),
                        std::get<1>(alias_node));

                walk.push_back(cur_nbrs[ad]);
            } else {
                i64 prev_node = walk[walk.size()-2];

                auto&& alias_edge = alias_edges[std::make_pair(prev_node, cur)];
                i64 ad = alias_draw(std::get<0>(alias_edge),
                        std::get<1>(alias_edge));

                i64 next_node = cur_nbrs[ad];

                walk.push_back(next_node);
            }
        } else {
            break;
        }
    }

    return walk;
}

template<typename T>
auto node2vec<T>::preprocess() -> void {
    std::map<i64, std::tuple<vecf64, vecf64> > alias_nodes;

    for(int node=0; node<G.size(); ++node) {
        vecf64 unnormalized_probs;
        auto neighbors = G[node];

        std::sort(neighbors.begin(), neighbors.end(), [=](auto a, auto b) {
            return W[node][a] > W[node][b];
        });

        for(const auto& nbr : neighbors) {
            unnormalized_probs.push_back(W[node][nbr]);
        }

        f64 norm_const = std::accumulate(unnormalized_probs.begin(),
                unnormalized_probs.end(), 0.0);

        vecf64 normarized_probs = unnormalized_probs / norm_const;
        alias_nodes[node] = this->alias_setup(normarized_probs);
    }

    std::map<std::pair<i64, i64>, std::tuple<vecf64, vecf64> > alias_edges;
    if(this->is_directed) {
        for(const auto& edge : this->E) {
            alias_edges[edge] = this->get_alias_edge(edge.first, edge.second);
        }
    } else {
        for(const auto& edge : this->E) {
            alias_edges[edge] = this->get_alias_edge(edge.first, edge.second);
            alias_edges[std::make_pair(edge.second, edge.first)] =
                this->get_alias_edge(edge.second, edge.first);
        }
    }

    this->alias_nodes = alias_nodes;
    this->alias_edges = alias_edges;
}

template<typename T>
auto node2vec<T>::alias_setup(vecf64 probs) -> std::tuple<vecf64, vecf64> {
    i64 k = probs.size();
    vecf64 q(k);
    vecf64 J(k);

    std::stack<f64> smaller;
    std::stack<f64> larger;

    for(int i=0; i<probs.size(); ++i) {
        q[i] = k*probs[i];
        if(q[i] < 1.0) smaller.push(i);
        else larger.push(i);
    }

    while(smaller.size()>0 && larger.size() > 0) {
        f64 small = smaller.top(); smaller.pop();
        f64 large = larger.top(); larger.pop();
        J[small] = large;
        q[large] = q[large] + q[small] - 1.0;
        if(q[large] < 1.0) smaller.push(large);
        else larger.push(large);
    }

    return std::make_tuple(J, q);
}

template<typename T>
auto node2vec<T>::get_alias_edge(i64 src, i64 dst) -> std::tuple<vecf64, vecf64> {
    vecf64 unnormalized_probs;

    auto neighbors = G[dst];
    std::sort(neighbors.begin(), neighbors.end(), [=](auto a, auto b) {
        return W[dst][a] > W[dst][b];
    });

    for(const auto& nbr : neighbors) {
        if(nbr == src) unnormalized_probs.push_back(W[dst][nbr]/p);
        else if(W[nbr][src] != 0) unnormalized_probs.push_back(W[dst][nbr]);
        else unnormalized_probs.push_back(W[dst][nbr]/q);
    }

    f64 norm_const = std::accumulate(unnormalized_probs.begin(),
            unnormalized_probs.end(), 0.0);

    vecf64 normarized_probs = unnormalized_probs / norm_const;

    return this->alias_setup(normarized_probs);
}

template<typename T>
auto node2vec<T>::alias_draw(vecf64 J, vecf64 q) -> i64 {
    i64 k = J.size();
    std::random_device rd;
    std::mt19937 mt(rd());
    i64 kk = floor(mt()*k);
    if(mt() < q[kk]) return kk;
    else return (i64)J[kk];
}

template class node2vec<mati32>;
template class node2vec<mati64>;
template class node2vec<matf64>;

} // namespace embeddings
} // namespace cpplearn
