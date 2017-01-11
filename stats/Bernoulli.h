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

namespace mllib {
    namespace stats {

        class Bernoulli : public AbstractDistribution {

        private:

            static constexpr char* distribution_name = (char*)"Bernoulli";

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

        };
    }
}

#endif //MLLIB_DISTRIBUTIONS_H
