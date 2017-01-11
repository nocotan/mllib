/**
 * Created by noco on 2017/01/11.
 *
 * @file Bernoulli.h
 * Header of distributions classes.
 *
 * ==========================================
 *
 * - A Binomial discrete random variable.
 */

#ifndef MLLIB_BINOM_H
#define MLLIB_BINOM_H

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include "AbstractDistribution.h"


namespace mllib {
    namespace stats {

        class Binom : public AbstractDistribution {

        private:

            static constexpr char* distribution_name = (char*)"Binom";
            double b;

            const bool arg_check(int n, double p);

        public:

            explicit Binom();

            /**
             *
             * @return
             */
            const std::string get_distribution_name() const;

            /**
             * Random variates.
             *
             * @param n
             * @param p
             * @param loc
             * @param size
             * @return
             */
            double rvs(int n, double p, int loc=0, int size=1);

            /**
             * Log of the probability mass function.
             * @param x
             * @param n
             * @param p
             * @param loc
             * @return
             */
            double logpmf(double x, int n, double p, int loc=0);

            /**
             * Probability mass function.
             *
             * @param x
             * @param n
             * @param p
             * @param loc
             * @return
             */
            double pmf(double x, int n, double p, int loc=0);

            /**
             * Cumulative distribution function.
             *
             * @param x
             * @param n
             * @param p
             * @param loc
             * @return
             */
            double cdf(double x, int n, double p, int loc=0);

            /**
             * Mean('m'), variance('v'), skew('s'), and/or kurtosis('k').
             *
             * @param loc
             * @param moments
             * @return
             */
            std::tuple<double, double, double, double> stats(int, double, int loc=0);

            /**
             * Entropy of the RV.
             * @param n
             * @param p
             * @param loc
             * @return
             */
            double entropy(int n, double p, int loc=0);
        };
    }
}

#endif //MLLIB_BINOM_H
