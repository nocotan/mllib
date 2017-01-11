/**
 * Created by noco on 2017/01/10.
 *
 * @file Bernoulli.h
 * Header of distributions classes.
 *
 * ==========================================
 *
 * - A Bernoulli discrete random variable.
 */

#ifndef MLLIB_DISTRIBUTIONS_H
#define MLLIB_DISTRIBUTIONS_H


#include <string>
#include "AbstractDistribution.h"
#include "Binom.h"

namespace mllib {
    namespace stats {

        class Bernoulli : public AbstractDistribution {

        private:

            static constexpr char* distribution_name = (char*)"Bernoulli";

            double b;
            Binom bi;

            void args_validation(int, double);
            const bool arg_check(int, double);

        public:

            explicit Bernoulli();

            /**
             *
             * @return
             */
            const std::string get_distribution_name() const;

            /**
             * Random variates.
             *
             * @param p
             * @param loc
             * @param size
             * @return
             */
            double rvs(double p, int loc=0, int size=1);

            /**
             * Log of the probability mass function.
             *
             * @param x
             * @param p
             * @param loc
             * @return
             */
            double logpmf(double x, double p, int loc=0);

            /**
             * Probability mass function.
             *
             * @param x
             * @param p
             * @param loc
             * @return
             */
            double pmf(double x, double p, int loc=0);

            /**
             * Cumulative distribution function.
             *
             * @param x
             * @param p
             * @param loc
             * @return
             */
            double cdf(double x, double p, int loc=0);

            /**
             * Survival function.
             *
             * @param x
             * @param p
             * @param loc
             * @return
             */
            double sf(double x, double p, int loc=0);

            /**
             * Mean('m'), variance('v'), skew('s'), and/or kurtosis('k').
             *
             * @param p
             * @param loc
             * @return
             */
            std::tuple<double, double, double, double> stats(double p, int loc=0);

            /**
             * Entropy of the RV.
             *
             * @param p
             * @param loc
             * @return
             */
            double entropy(double p, int loc=0);
        };
    }
}

#endif //MLLIB_DISTRIBUTIONS_H
