/**
 * Created by noco on 2017/01/10.
 *
 * @file Distributions.cpp
 * Implementation of distributions classes.
 *
 * ==========================================
 *
 * - A Bernoulli discrete random variable.
 */

#include <iostream>
#include "Bernoulli.h"
#include "../utils/ExtFunctions.h"


namespace mllib {
    namespace stats {

        Bernoulli::Bernoulli()
                : b(0) {
            bi = Binom();
        }

        const std::string Bernoulli::get_distribution_name() const {
            return distribution_name;
        }

        const bool Bernoulli::arg_check(int n, double p) {
            b = n;
            return (n >= 0) & (p >= 0) & (p <= 1);
        }

        void Bernoulli::args_validation(int n, double p) {
            if (!arg_check(n, p)) {
                std::cerr << "[Argument Error] arguments must be (n >=0 && 0 <= p <= 1)." << std::endl;
                exit(1);
            }
        }

        double Bernoulli::rvs(double p, int loc, int size) {
            return bi.rvs(1, p);
        }

        double Bernoulli::logpmf(double x, double p, int loc) {
            return bi.logpmf(x, 1, p);
        }

        double Bernoulli::pmf(double x, double p, int loc) {
            return bi.pmf(x, 1, p);
        }

        double Bernoulli::cdf(double x, double p, int loc) {
            return bi.cdf(x, 1, p);
        }

        double Bernoulli::sf(double x, double p, int loc) {
            return bi.sf(x, 1, p);
        }

        std::tuple<double, double, double, double> Bernoulli::stats(double p, int loc) {
            return bi.stats(1, p);
        }

        double Bernoulli::entropy(double p, int loc) {
            return utils::entr(p) + utils::entr(1 - p);
        }
    }
}