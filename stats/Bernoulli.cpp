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

#include "Bernoulli.h"


namespace mllib {
    namespace stats {

        Bernoulli::Bernoulli() { }

        const std::string Bernoulli::get_distribution_name() const {
            return distribution_name;
        }

        double Bernoulli::rvs(double p, int loc, int size) { }
    }
}