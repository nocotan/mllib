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
        constexpr long double MACHEP = 1.11022302462515654042E-16;
        constexpr long double MAXLOG = 7.09782712893383996732E2;
        constexpr long double MINLOG = -7.451332191019412076235E2;
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
            double a, b, t, x, xc, w, y;
            int flag;

            if ((xx <= 0.0) || (xx >= 1.0)) {
                if (xx == 0.0)
                    return (0.0);
                if (xx == 1.0)
                    return (1.0);
            }

            flag = 0;
            if ((bb * xx) <= 1.0 && xx <= 0.95) {
                t = pseries(aa, bb, xx);
                goto done;
            }

            w = 1.0 - xx;

/* Reverse a and b if x is greater than the mean. */
            if (xx > (aa / (aa + bb))) {
                flag = 1;
                a = bb;
                b = aa;
                xc = xx;
                x = w;
            } else {
                a = aa;
                b = bb;
                xc = w;
                x = xx;
            }

            if (flag == 1 && (b * x) <= 1.0 && x <= 0.95) {
                t = pseries(a, b, x);
                goto done;
            }

/* Choose expansion for better convergence. */
            y = x * (a + b - 2.0) - (a - 1.0);
            if (y < 0.0)
                w = incbcf(a, b, x);
            else
                w = incbd(a, b, x) / xc;

/* Multiply w by the factor
 * a      b   _             _     _
 * x  (1-x)   | (a+b) / ( a | (a) | (b) ) .   */

            y = a * log(x);
            t = b * log(xc);
            if ((a + b) < MAXGAM && fabs(y) < MAXLOG && fabs(t) < MAXLOG) {
                t = pow(xc, b);
                t *= pow(x, a);
                t /= a;
                t *= w;
                t *= 1.0 / boost::math::beta(a, b);
                goto done;
            }
/* Resort to logarithms.  */
            y += t - std::log(std::abs(boost::math::beta(a, b)));
            y += log(w / a);
            if (y < MINLOG)
                t = 0.0;
            else
                t = exp(y);

            done:

            if (flag == 1) {
                if (t <= MACHEP)
                    t = (double) (1.0 - MACHEP);
                else
                    t = 1.0 - t;
            }
            return (t);
        }

/* Continued fraction expansion #1
 * for incomplete beta integral
 */

        static double incbcf(double a, double b, double x) {
            double xk, pk, pkm1, pkm2, qk, qkm1, qkm2;
            double k1, k2, k3, k4, k5, k6, k7, k8;
            double r, t, ans, thresh;
            int n;

            k1 = a;
            k2 = a + b;
            k3 = a;
            k4 = a + 1.0;
            k5 = 1.0;
            k6 = b - 1.0;
            k7 = k4;
            k8 = a + 2.0;

            pkm2 = 0.0;
            qkm2 = 1.0;
            pkm1 = 1.0;
            qkm1 = 1.0;
            ans = 1.0;
            r = 1.0;
            n = 0;
            thresh = (double) (3.0 * MACHEP);
            do {

                xk = -(x * k1 * k2) / (k3 * k4);
                pk = pkm1 + pkm2 * xk;
                qk = qkm1 + qkm2 * xk;
                pkm2 = pkm1;
                pkm1 = pk;
                qkm2 = qkm1;
                qkm1 = qk;

                xk = (x * k5 * k6) / (k7 * k8);
                pk = pkm1 + pkm2 * xk;
                qk = qkm1 + qkm2 * xk;
                pkm2 = pkm1;
                pkm1 = pk;
                qkm2 = qkm1;
                qkm1 = qk;

                if (qk != 0)
                    r = pk / qk;
                if (r != 0) {
                    t = fabs((ans - r) / r);
                    ans = r;
                } else
                    t = 1.0;

                if (t < thresh)
                    goto cdone;

                k1 += 1.0;
                k2 += 1.0;
                k3 += 2.0;
                k4 += 2.0;
                k5 += 1.0;
                k6 -= 1.0;
                k7 += 2.0;
                k8 += 2.0;

                if ((fabs(qk) + fabs(pk)) > BIG) {
                    pkm2 *= BIGINV;
                    pkm1 *= BIGINV;
                    qkm2 *= BIGINV;
                    qkm1 *= BIGINV;
                }
                if ((fabs(qk) < BIGINV) || (fabs(pk) < BIGINV)) {
                    pkm2 *= BIG;
                    pkm1 *= BIG;
                    qkm2 *= BIG;
                    qkm1 *= BIG;
                }
            } while (++n < 300);

            cdone:
            return (ans);
        }


/* Continued fraction expansion #2
 * for incomplete beta integral
 */

        static double incbd(double a, double b, double x) {
            double xk, pk, pkm1, pkm2, qk, qkm1, qkm2;
            double k1, k2, k3, k4, k5, k6, k7, k8;
            double r, t, ans, z, thresh;
            int n;

            k1 = a;
            k2 = b - 1.0;
            k3 = a;
            k4 = a + 1.0;
            k5 = 1.0;
            k6 = a + b;
            k7 = a + 1.0;;
            k8 = a + 2.0;

            pkm2 = 0.0;
            qkm2 = 1.0;
            pkm1 = 1.0;
            qkm1 = 1.0;
            z = x / (1.0 - x);
            ans = 1.0;
            r = 1.0;
            n = 0;
            thresh = (double) (3.0 * MACHEP);
            do {

                xk = -(z * k1 * k2) / (k3 * k4);
                pk = pkm1 + pkm2 * xk;
                qk = qkm1 + qkm2 * xk;
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

                if (qk != 0)
                    r = pk / qk;
                if (r != 0) {
                    t = fabs((ans - r) / r);
                    ans = r;
                } else
                    t = 1.0;

                if (t < thresh)
                    goto cdone;

                k1 += 1.0;
                k2 -= 1.0;
                k3 += 2.0;
                k4 += 2.0;
                k5 += 1.0;
                k6 += 1.0;
                k7 += 2.0;
                k8 += 2.0;

                if ((fabs(qk) + fabs(pk)) > BIG) {
                    pkm2 *= BIGINV;
                    pkm1 *= BIGINV;
                    qkm2 *= BIGINV;
                    qkm1 *= BIGINV;
                }
                if ((fabs(qk) < BIGINV) || (fabs(pk) < BIGINV)) {
                    pkm2 *= BIG;
                    pkm1 *= BIG;
                    qkm2 *= BIG;
                    qkm1 *= BIG;
                }
            } while (++n < 300);
            cdone:
            return (ans);
        }

/* Power series for incomplete beta integral.
 * Use when b*x is small and x not too close to 1.  */

        static double pseries(double a, double b, double x) {
            double s, t, u, v, n, t1, z, ai;

            ai = 1.0 / a;
            u = (1.0 - b) * x;
            v = u / (a + 1.0);
            t1 = v;
            t = u;
            n = 2.0;
            s = 0.0;
            z = (double) (MACHEP * ai);
            while (fabs(v) > z) {
                u = (n - b) * x / n;
                t *= u;
                v = t / (a + n);
                s += v;
                n += 1.0;
            }
            s += t1;
            s += ai;

            u = a * log(x);
            if ((a + b) < MAXGAM && fabs(u) < MAXLOG) {
                t = 1.0 / boost::math::beta(a, b);
                s = s * t * pow(x, a);
            } else {
                t = -std::log(std::abs(boost::math::beta(a, b))) + u + log(s);
                if (t < MINLOG)
                    s = 0.0;
                else
                    s = exp(t);
            }
            return (s);
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
