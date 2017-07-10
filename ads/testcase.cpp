//#define _GRIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;

#define int long long

int memo[100000][100000];

auto main() -> signed {
    int V = 10;
    int E = 20;
    cout << V << " " << E << endl;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dice(1, V);
    std::uniform_int_distribution<int> w(0, 15);
    for(int i=0; i<E; ++i) {
        int from = dice(mt);
        int to = dice(mt);
        from--;
        to--;
        if(from==to) continue;
        if(memo[from][to]!=0) continue;
        if(memo[to][from]!=0) continue;
        cout << from << " " << to << " " << w(mt) << endl;
        memo[from][to]++;
    }
    return 0;
}

