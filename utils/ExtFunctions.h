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

        constexpr long double MAXGAM = 171.624376956302725;
        constexpr long double MACHEP = 1.38777878078144567553E-17;
        constexpr long double MAXLOG = 8.8029691931113054295988E1;
        constexpr long double MINLOG = -8.872283911167299960540E1;
        constexpr long double BIG = 4.503599627370496e15;
        constexpr long double BIGINV = 2.22044604925031308085e-16;

        double xlogy(double, double);
        double xlog1py(double, double);
        double entr(double);
        double incbet(double, double, double);
        static double incbcf(double, double, double);
        static double incbd(double, double, double);
        static double pseries(double, double, double);
        double bdtr(double, int, double);


        double xlogy(double x, double y) {
            if (x==0 || std::isnan(std::log(y))) {
                return 0;
            }
            else {
                return x * std::log(y);
            }
        }

        double xlog1py(double x, double y) {
            if (x==0 || std::isnan(std::log1p(y))) {
                return 0;
            }
            else {
                return x * std::log1p(y);
            }
        }

        double entr(double x) {
            if (x > 0) {
                return -x * std::log(x);
            }
            else if (x ==0) {
                return 0;
            }
            else {
                return -INFINITY;
            }
        }

        double incbet(double aa, double bb, double xx) {
            if (xx == 0.0) {
                return 0.0;
            }
            else if (xx == 1.0) {
                return 1.0;
            }

            int flag = 0;
            double t = 0;
            if (bb * xx <= 1.0 && xx <= 0.95) {
                t = pseries(aa, bb, xx);
                return t;
            }

            double w = 1.0 - xx;

            double a, b, xc, x;
            if (xx > aa / (aa + bb)) {
                flag = 1;
                a = bb;
                b = aa;
                xc = xx;
                x = w;
            }
            else {
                a = aa;
                b = bb;
                xc = w;
                x = xx;
            }

            if (flag == 1 && b * x <= 1.0 && x <= 0.95) {
                t = pseries(a, b, x);
                if (t <= MACHEP) {
                    return 1.0 - MACHEP;
                }
                else {
                    return 1.0 - t;
                }
            }

            double y = x * (a + b - 2.0) - (a - 1.0);
            if (y < 0.0) {
                w = incbcf(a, b, x);
            }
            else {
                w = incbd(a, b, x) / xc;
            }

            y = a * std::log(x);
            t = b * std::log(xc);
            if (a + b < MAXGAM && std::fabs(y) < MAXLOG && std::fabs(t) < MAXLOG) {
                t = std::pow(xc, b);
                t *= std::pow(x, a);
                t /= a;
                t *= w;
                t *= 1.0 / boost::math::beta(a, b);
            }

            y += t - std::log(std::abs(boost::math::beta(a, b)));
            y += std::log(w/ a);
            if (y < MINLOG) {
                t = 0.0;
            }
            else {
                t = std::exp(y);
            }

            if (flag == 1) {
                if (t <= MACHEP) {
                    t = 1.0 - MACHEP;
                }
                else {
                    t = 1.0 - t;
                }
            }
            return t;
        }

        static double incbcf(double a, double b, double x) {
            double k1 = a;
            double k2 = a + b;
            double k3 = a;
            double k4 = a + 1.0;
            double k5 = 1.0;
            double k6 = b - 1.0;
            double k7 = k4;
            double k8 = a + 2.0;

            double pkm2 = 0.0;
            double qkm2 = 1.0;
            double pkm1 = 1.0;
            double qkm1 = 1.0;
            double ans = 1.0;
            double r = 1.0;
            int n = 0;
            double thresh = 3.0 * MACHEP;

            while(++n <= 300) {
                double xk = -(x * k1 * k2) / (k3 * k4);
                double pk = pkm1 + pkm2 * xk;
                double qk = qkm1 + qkm2 * xk;

                pkm2 = pkm1;
                pkm1 = pk;
                qkm2 = qkm1;
                qkm1 = qk;

                xk = (x * k5 * k6) / (k7 * k8);
                pk = pkm1 + pkm2 * xk;
                qk = qkm1 + qkm2 * xk;
                pkm2 = qkm1;
                pkm1 = pk;
                qkm2 = qkm1;
                qkm1 = qk;

                double t;
                if (qk != 0) {
                    r = pk / qk;
                }

                if (r != 0) {
                    t = std::fabs((ans - r) / r);
                    ans = r;
                }
                else {
                    t = 1.0;
                }

                if (t < thresh) {
                    return ans;
                }

                k1 += 1.0;
                k2 += 1.0;
                k3 += 2.0;
                k4 += 2.0;
                k5 += 1.0;
                k6 -= 1.0;
                k7 += 2.0;
                k8 += 2.0;

                if (std::fabs(qk) + std::fabs(pk) > BIG) {
                    pkm2 *= BIGINV;
                    pkm1 *= BIGINV;
                    qkm2 *= BIGINV;
                    qkm1 *= BIGINV;
                }

                if (std::fabs(qk) < BIGINV || std::fabs(pk) < BIGINV) {
                    pkm2 *= BIG;
                    pkm1 *= BIG;
                    qkm2 *= BIG;
                    qkm1 *= BIG;
                }
            }

            return ans;
        }

        static double incbd(double a, double b, double x) {
            double k1 = a;
            double k2 = b - 1.0;
            double k3 = a;
            double k4 = a + 1.0;
            double k5 = 1.0;
            double k6 = a + b;
            double k7 = a + 1.0;
            double k8 = a + 2.0;

            double pkm2 = 0.0;
            double qkm2 = 1.0;
            double pkm1 = 1.0;
            double qkm1 = 1.0;
            double z = x / (1.0 - x);
            double ans = 1.0;
            double r = 1.0;
            int n = 0;
            double thresh = 3.0 * MACHEP;

            while (++n <= 300) {
                double xk = -(z * k1 * k2) / (k3 * k4);
                double pk = pkm1 + pkm2 * xk;
                double qk = qkm1 + qkm2 * xk;

                pkm2 = pkm1;
                pkm1 = pk;
                qkm2 = qkm1;
                qkm1 = qk;

                xk = (z * k5 * k6) / (k7 * k8);
                pk = pkm1 + pkm2 * xk;
                qk = qkm1 + qkm2 * xk;
                pkm2 = pkm1;
                pkm1 = pk;
                qkm2 = qkm1;
                qkm1 = qk;

                if (qk != 0) {
                    r = pk / qk;
                }

                double t;
                if (r != 0) {
                    t = std::fabs((ans - r) / r);
                    ans = r;
                }
                else {
                    t = 1.0;
                }

                if (t < thresh) {
                    return ans;
                }

                k1 += 1.0;
                k2 -= 1.0;
                k3 += 2.0;
                k4 += 2.0;
                k5 += 1.0;
                k6 += 1.0;
                k7 += 2.0;
                k8 += 2.0;

                if (std::fabs(qk) + std::fabs(pk) > BIG) {
                    pkm2 *= BIGINV;
                    pkm1 *= BIGINV;
                    qkm2 *= BIGINV;
                    qkm1 *= BIGINV;
                }

                if (std::fabs(qk) < BIGINV || std::fabs(pk) < BIGINV) {
                    pkm2 *= BIG;
                    pkm1 *= BIG;
                    qkm2 *= BIG;
                    qkm1 *= BIG;
                }
            }

            return ans;
        }

        static double pseries(double a, double b, double x) {
            double ai = 1.0 / a;
            double u = (1.0 - b) * x;
            double v = u / (a + 1.0);
            double t1 = v;
            double t = u;
            double n = 2.0;
            double s = 0.0;
            double z = MACHEP * ai;

            while (std::fabs(v) > z) {
                u = (n - b) * x / n;
                t *= u;
                v = t / (a + n);
                s += v;
                n += 1.0;
            }

            s += t1;
            s += ai;

            u = a * std::log(x);
            if (a + b < MAXGAM && std::fabs(u) < MAXLOG) {
                t = 1.0 / boost::math::beta(a, b);
                s = s * t * std::pow(x, a);
            }
            else {
                t = -std::log(std::abs(boost::math::beta(a, b))) + u + std::log(s);
                if (t < MINLOG) {
                    s = 0.0;
                }
                else {
                    s = std::exp(t);
                }
            }

            return s;
        }

        double bdtr(double k, int n, double p) {
            if (k == n) {
                return 1.0;
            }

            double dn = n - k;
            double dk;
            if (k == 0) {
                dk = std::pow(1.0 - p, dn);
            }
            else {
                dk = k + 1;
                dk = incbet(dn, dk, 1.0 - p);
            }

            return dk;
        }
    }
}


#endif //MLLIB_EXTFUNCTIONS_H
