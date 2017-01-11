//
// Created by noco on 2017/01/10.
//

#include <iostream>

#include "../stats/Bernoulli.h"
#include "../stats/Binom.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotAssignable"
using namespace std;
using namespace mllib::stats;

int main() {
    int n = 5;
    double p = 0.4;
    double x = 1.0;

    /**
     * Binomial
     */
    Binom bi = Binom();
    cout << bi.get_distribution_name() << endl;
    cout << "rvs: " << bi.rvs(n, p) << endl;

    double m, v, s, k;
    std::tie(m, v, s, k) = bi.stats(n, p);
    cout << "stats: " << m << " " << v << " " << s << " " << k << endl;

    cout << "logpmf: " << bi.logpmf(x, n, p) << endl;

    cout << "pmf: " << bi.pmf(x, n, p) << endl;

    cout << "entropy: " << bi.entropy(n, p) << endl;

    cout << endl;

    /**
     * Bernoulli
     */
    Bernoulli ber = Bernoulli();
    cout << ber.get_distribution_name() << endl;
    return 0;
}
#pragma clang diagnostic pop