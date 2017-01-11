/**
 * Created by noco on 2017/01/11.
 *
 * @file Distributions.cpp
 * Implementation of distributions classes.
 *
 * ==========================================
 *
 * - A Binomial discrete random variable.
 */

#include <cmath>
#include <iostream>
#include <random>
#include "Binom.h"
#include "../utils/ExtFunctions.h"


namespace mllib {
    namespace stats {

        Binom::Binom()
                : b(0) { }

        const bool Binom::arg_check(int n, double p) {
            b = n;
            return (n >= 0) & (p >= 0) & (p <= 1);
        }

        void Binom::args_validation(int n, double p) {
            if (!arg_check(n, p)) {
                std::cerr << "[Argument Error] arguments must be (n >=0 && 0 <= p <= 1)." << std::endl;
                exit(1);
            }
        }

        const std::string Binom::get_distribution_name() const {
            return distribution_name;
        }


        double Binom::rvs(int n, double p, int loc, int size) {
            args_validation(n, p);

            std::random_device seed_gen;
            std::mt19937 engine(seed_gen());

            std::binomial_distribution<> dist(n, p);

            int res = dist(engine);
            return res;
        }

        double Binom::logpmf(double x, int n, double p, int loc) {
            args_validation(n, p);

            double k = floor(x);
            double combiln = (lgamma(n + 1) - (lgamma(k + 1) + lgamma(n - k + 1)));
            return combiln + utils::xlogy(k, p) + utils::xlog1py(n - k, -p);
        }

        double Binom::pmf(double x, int n, double p, int loc) {
            args_validation(n, p);

            return exp(logpmf(x, n, p));
        }

        double Binom::cdf(double x, int n, double p, int loc) {
            args_validation(n, p);

            double k = std::floor(x);
            double vals = utils::bdtr(k, n, p);
            return vals;
        }

        double Binom::sf(double x, int n, double p, int loc) {
            args_validation(n, p);

            double k = std::floor(x);
            return utils::bdtrc(k, n, p);
        }

        std::tuple<double, double, double, double> Binom::stats(int n, double p, int loc) {
            args_validation(n, p);

            double q = 1.0 - p;
            double mu = n * p;
            double var = n * p * q;
            double g1 = (q - p) / sqrt(n * p * q);
            double g2 = (1.0 - 6.0 * p * q) / (n * p * q);

            return std::forward_as_tuple(mu, var, g1, g2);
        }

        double Binom::entropy(int n, double p, int loc) {
            args_validation(n, p);

            std::vector<double> k((unsigned long) (n + 1));
            std::iota(k.begin(), k.end(), 0);

            std::vector<double> vals;
            for (int i=0; i<n+1; ++i) {
                double val = pmf(k[i], n, p);;
                vals.push_back(utils::entr(val));
            }

            return std::accumulate(vals.begin(), vals.end(), (double)0.0);
        }
    }
}