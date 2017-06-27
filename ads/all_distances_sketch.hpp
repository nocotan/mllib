#ifndef ALL_DISTANCES_SKETCH_HPP
#define ALL_DISTANCES_SKETCH_HPP

#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

namespace mllib {

struct edge {
    int to;
    double cost;
};

struct cmp {
    bool operator ()(const std::pair<int, double> &a, const std::pair<int, double> &b) {
        return a.second < b.second;
    }
};

using graph = std::vector<std::vector<edge> >;
using sketch = std::set<std::pair<int, double>, cmp>;

class all_distances_sketch {
    private:
        int k;
        int V;
        graph G;
        std::vector<sketch> ads;
        std::vector<std::pair<int, int> > r;

        auto dijkstra(int s) -> std::tuple<std::vector<double>, std::set<int> >;

    public:
        all_distances_sketch(int);

        auto fit(graph) -> void;
        const auto get_sketch() const -> std::vector<sketch>;
        const auto get_nd(int, double) const -> std::set<int>;

        const auto estimate_jaccard(int v, int u, double d) const -> double;
};

all_distances_sketch::all_distances_sketch(int k)
    : k(k) { }

auto all_distances_sketch::fit(graph G) -> void {
    this->G = G;
    this->V = G.size();

    this->ads.resize(this->V);
    this->r.resize(this->V);

    std::vector<int> nodes(this->V);
    std::iota(nodes.begin(), nodes.end(), 0);
    std::random_shuffle(nodes.begin(), nodes.end());
    for(int i=0; i<V; ++i) {
        this->r[i] = std::make_pair(nodes[i], i);
    }

    std::sort(r.begin(), r.end());

    int f = r.size();
    int f_count = 1;
    for(auto itr=r.begin(); itr!=r.end(); ++itr) {
        if(f_count%100==0)
            std::cout << f_count << "/" << f << std::endl;
        f_count++;

        int u = (*itr).second;
        int r_u = (*itr).first;

        std::set<int> scanned_nodes;
        std::vector<double> d;
        std::tie(d, scanned_nodes) = this->dijkstra(u);
        for(auto nd : scanned_nodes) {
            int count_d = 0;
            for(auto e : ads[nd]) {
                if(e.second<d[nd]) count_d++;
            }
            if(count_d==k) continue;
            else ads[nd].insert(std::make_pair(u, d[nd]));
        }
    }
}

const auto all_distances_sketch::get_sketch() const -> std::vector<sketch> {
    return this->ads;
}

const auto all_distances_sketch::get_nd(int v, double d) const -> std::set<int> {
    sketch s = ads[v];
    std::set<int> nd;
    int cnt = 0;
    for(auto itr=s.begin(); itr!=s.end(); ++itr) {
        if((*itr).second < d) nd.insert((*itr).first);
        cnt++;
        if(cnt==k) break;
    }

    return nd;
}

const auto all_distances_sketch::estimate_jaccard(int v, int u, double d) const -> double {
    auto nd_v = this->get_nd(v, d);
    auto nd_u = this->get_nd(u, d);
    std::set<int> union_nd = nd_v;
    std::set<int> product_nd;
    for(auto itr=nd_u.begin(); itr!=nd_u.end(); ++itr) {
        if(nd_v.find(*itr)!=nd_v.end()) product_nd.insert(*itr);
        union_nd.insert(*itr);
    }

    return (double)product_nd.size() / (double)union_nd.size();
}

auto all_distances_sketch::dijkstra(int s) -> std::tuple<std::vector<double>, std::set<int> > {
    std::vector<double> d(this->V);
    for(int i=0; i<d.size(); ++i) d[i] = 1e+9;

    std::set<int> nodes;
    nodes.insert(s);

    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P> > que;
    d[s] = 0;
    que.push(std::make_pair(0, s));

    while(!que.empty()) {
        P p = que.top();
        que.pop();
        int v = p.second;
        if(d[v] < p.first) continue;
        for(int i=0; i<G[v].size(); ++i) {
            edge e = G[v][i];
            if(d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(std::make_pair(d[e.to], e.to));
                nodes.insert(e.to);
            }
        }
    }

    return make_tuple(d, nodes);
}

} // mllib

#endif
