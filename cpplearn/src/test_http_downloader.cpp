//#define _GRIBCXX_DEBUG
#include <bits/stdc++.h>
#include "http_downloader.hpp"
using namespace std;

#define int long long

auto main() -> signed {
    cpplearn::http_downloader downloader;
    string content = downloader.download("https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data");
    cout << content << endl;
    return 0;
}

