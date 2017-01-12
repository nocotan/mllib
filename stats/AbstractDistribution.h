/**
 * Created by noco on 2017/01/10.
 *
 * @file AbstractDistributions.h
 * Abstract class for distributions.
 */

#ifndef MLLIB_ABSTRACTDISTRIBUTION_H
#define MLLIB_ABSTRACTDISTRIBUTION_H

#include <string>
#include <tuple>
#include "../utils/ExtFunctions.h"

namespace mllib {
    namespace stats {

        class AbstractDistribution {

        private:

            virtual void args_validation(int, double) { }
            virtual void args_validation(double) { }

        protected:

            AbstractDistribution() { }

        public:

            virtual ~AbstractDistribution() { }

            virtual const std::string get_distribution_name() const = 0;


            virtual double rvs(double, int loc=0, int size=1) { return 0; }
            virtual double rvs(int, double, int loc=0, int size=1) { return 0; }

            virtual double pmf(double, double, int loc=0) { return 0; }
            virtual double pmf(double, int, double, int loc=0) { return 0; }

            virtual double logpmf(double, double, int loc=0) { return 0; }
            virtual double logpmf(double, int, double, int loc=0) { return 0; }

            virtual double cdf(double, double, int loc=0) { return 0; }
            virtual double cdf(double, int, double, int loc=0) { return 0; }

            virtual double logcdf(double, double, int loc=0) { return 0; }

            virtual double sf(double, double, int loc=0) { return 0; }
            virtual double sf(double, int, double, int loc=0) { return 0; }

            virtual double logsf(double, double, int loc=0) { return 0; }

            virtual double ppf(double, double, int loc=0) { return 0; }

            virtual double isf(double, double, int loc=0) { return 0; }

            virtual std::tuple<double, double, double, double> stats(int, double, int loc=0) { return std::forward_as_tuple(0, 0, 0, 0); };
            virtual std::tuple<double, double, double, double> stats(double, int loc=0) { return std::forward_as_tuple(0, 0, 0, 0); };

            virtual double entropy(double, int loc=0) { return 0; }
            virtual double entropy(int, double, int loc=0) { return 0; }

            virtual double median(double, int loc=0) { return 0; }

            virtual double mean(double, int loc=0) { return 0; }

            virtual double var(double, int loc=0) { return 0; }

            virtual double std(double, int loc=0) { return 0; }

            virtual double interval(double, double, int loc=0) { return 0; }
        };
    }
}

#endif //MLLIB_ABSTRACTDISTRIBUTION_H
