//#define _GRIBCXX_DEBUG
#include "datasets.hpp"
#include "cluster/k_means.hpp"
#include "metrics/distances.hpp"
#include "metrics/similarity.hpp"
#include "embeddings/node2vec.hpp"

#include <iostream>
#include <string>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

#define int long long

auto main() -> signed {
    cout << "test" << endl;
    vector<vector<double> > X;
    vector<double> y;
    tie(X, y) = cpplearn::datasets::load_iris();

    vector<vector<double> > wine_X;
    vector<double> wine_y;
    tie(wine_X, wine_y) = cpplearn::datasets::load_wine();

    cout << "[";
    for(int i=0; i<X.size(); ++i) {
        cout << "[";
        for(int j=0; j<X[i].size(); ++j) cout << X[i][j] << " ";
        cout << "]," << endl;
    }
    cout << "]";
    cout << endl;

    cout << "[";
    for(int i=0; i<y.size(); ++i) cout << y[i] << " ";
    cout << "]";
    cout << endl;

    cpplearn::cluster::k_means<vector<vector<double> > > kmeans;
    kmeans.set_n_clusters(3);
    kmeans.fit(X);
    auto&& pred = kmeans.predict(X);
    cout << "[";
    for(const auto& e : pred) cout << e << " ";
    cout << "]";
    cout << endl;

    cout << endl;

    cout << "============== metrics test ===============" << endl;
    cout << "distances:" << endl;
    cout << cpplearn::distances::euclidean_distance(pred, y) << endl;
    cout << cpplearn::distances::standard_euclidean_distance(pred, y) << endl;
    cout << cpplearn::distances::cosine_distance(pred, y) << endl;
    cout << cpplearn::distances::manhattan_distance(pred, y) << endl;
    cout << cpplearn::distances::chebyshev_distance(pred, y) << endl;
    cout << endl;


    set<int> st1{3, 1, 5};
    set<int> st2{3, 1, 4};

    cout << "similarity:" << endl;
    cout << cpplearn::similarity::cosine_similarity(pred, y) << endl;
    cout << cpplearn::similarity::jaccard_similarity(st1, st2) << endl;
    cout << cpplearn::similarity::dice_similarity(st1, st2) << endl;
    cout << cpplearn::similarity::simpson_similarity(st1, st2) << endl;

    cout << "============== node2vec test =============" << endl;
    using mati32 = vector<vector<int> >;
    using mati64 = vector<vector<int> >;
    using i64 = long long;


    int n, m;
    cin >> n >> m;
    mati32 G(n);
    mati32 W(n, vector<int>(n));
    set<pair<i64, i64> > E;
    /** input graph */
    for(int i=0; i<m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].push_back(b);
        G[b].push_back(a);
        W[a][b] = c;
        E.insert(make_pair(a, b));
        E.insert(make_pair(b, a));
    }

    cpplearn::embeddings::node2vec<mati32> n2v(G, W, E, true, 20, 3);
    mati64 walks = n2v.simulate_walk(2, 3);
    cout << "walks" << endl;
    for(int i=0; i<walks.size(); ++i) {
        for(int j=0; j<walks[i].size(); ++j) {
            cout << walks[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

