/**
 * Created by noco on 2017/01/11.
 *
 * @file ExtFunctions.h
 * This file contains important functions.
 */

#ifndef MLLIB_EXTFUNCTIONS_H
#define MLLIB_EXTFUNCTIONS_H


#include <cmath>
#include <boost/math/distributions/beta.hpp>

namespace mllib {
    namespace utils {

        double xlogy(double, double);
        double xlog1py(double, double);
        double entr(double);
        double incbet(double, double, double);
        double incbcf(double, double, double);
        double incbd(double, double, double);
        double pseries(double, double, double);
        double bdtr(double, int, double);
        double bdtrc(double, int, double);
    }
}


#endif //MLLIB_EXTFUNCTIONS_H
