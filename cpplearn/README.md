# cpplearn
C++で機械学習関係の実装

# build
```
$ cmake -DCMAKE_CXX_COMPILER=/usr/local/bin/g++-7 .
$ make
```

## clustering

### k-means

```c++
#include "cluster/k_means.hpp"

cpplearn::cluster::k_means<vector<vector<double> > > kmeans;
kmeans.set_n_clusters(3);
double pred = kmeans.fit_predict(X);
```


## metrics

### distances

#### ユークリッド距離

```c++
template<typename T>
double cpplearn::distances::euclidian_distances(const T x1, const T x2);
```

#### 標準ユークリッド距離

```c++
template<typename T>
double cpplearn::distances::standard_euclidian_distances(const T x1, const T x2);
```

#### コサイン距離

```c++
template<typename T>
double cpplearn::distances::cosine_distance(const T x1, const T x2);
```

#### マンハッタン距離

```c++
template<typename T>
double cpplearn::distances::manhattan_distance(const T x1, const T x2);
```

#### チェビシェフ距離

```c++
template<typename T>
double cpplearn::distances::chebyshev_distance(const T x1, const T x2);
```

### similarity

#### コサイン類似度

```c++
template<typename T>
double cpplearn::similarity::cosine_similarity(const T x1, const T x2);
```

#### Jaccard係数

```c++
template<typename T>
double cpplearn::similarity::jaccard_similarity(const T x1, const T x2);
```

#### Dice係数

```c++
template<typename T>
double cpplearn::similarity::dice_similarity(const T x1, const T x2);
```


#### Simpson係数

```c++
template<typename T>
double cpplearn::similarity::simpson_similarity(const T x1, const T x2);
```
## datasets

### load_iris()
[Irisデータセット](https://archive.ics.uci.edu/ml/datasets/iris)の読み込み.

```c++
#include <bits/stdc++.h>
#include "datasets.hpp"
using namespace std;

#define int long long

auto main() -> signed {
    vector<vector<double> > X;
    vector<double> y;

    // データセットの読み込み
    tie(X, y) = cpplearn::datasets::load_iris();

    /** 以下出力 **/
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
    return 0;
}
```

### load_wine()
[Wineデータセット](https://archive.ics.uci.edu/ml/datasets/Wine)の読み込み.
