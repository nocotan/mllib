//#define _GRIBCXX_DEBUG
#include <bits/stdc++.h>
#include "all_distances_sketch.hpp"
using namespace std;

int V, E;

vector<vector<mllib::edge> > G;

auto main() -> signed {
    cin >> V;
    int E;
    cin >> E;

    G.resize(V);

    for (int i=0; i<E; ++i) {
        int a, b;
        double c;
        cin >> a >> b >> c;
        mllib::edge e = {b, c};
        G[a].push_back(e);
        mllib::edge e2 = {a, c};
        G[b].push_back(e2);
    }
    mllib::all_distances_sketch ads(1000);
    ads.fit(G);

    auto sketch = ads.get_sketch();
    for(int i=0; i<sketch.size(); ++i) {
        cout << "ノード: " << i << endl;
        for(auto e : sketch[i]) {
            cout << "d(" << i << "," << e.first << ") = " << e.second << endl;
        }
    }

    cout << "ノード0とノード1のJaccard係数: " << ads.estimate_jaccard(0, 1, 300) << endl;
    cout << "ノード0とノード10のJaccard係数: " << ads.estimate_jaccard(0, 10, 300) << endl;
    cout << "ノード0とノード100のJaccard係数: " << ads.estimate_jaccard(0, 100, 300) << endl;
    return 0;
}

