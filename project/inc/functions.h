#ifndef MGR_FUNCTIONS_H
#define MGR_FUNCTIONS_H

#include <cassert>
#include <valarray>

/*
     * Basic functions for integration tests
     * It can be any (infinite or finite) function that uses product weights
     *
     * author Dawid Majchrowski
*/

// f(x) = x1 + x2 + x3 + x4 | 1.54755
long double f_basic(int scope, std::valarray<long double> points);

// f(x) = x1 + x2 + x1x2 + x1x2x3 | integral is 1.19363
long double f_basic_2(int scope, std::valarray<long double> points);

// test functions

// Product weights given by w_i = 0.9^i

// f(x) = Sum_{i=1}^{infty} x_i
// integral 4.5
// norm     3
long double f_infty_basic(int scope, std::valarray<long double> points);

// f(x) = Sum_{i=1}^{infty} x^2*e^((cos(x_i))^2)
// integral  5.17466
// norm      4.24040
long double f_infty_exponent(int scope, std::valarray<long double> points);

// f(x) = Sum_{i=1}^{infty} Sum_{j=i}^{infty} sin(x_i*x_j)
// integral  9.20120
// norm      5.40371
long double f_infty_products(int scope, std::valarray<long double> points);


// Product weights given by w_i = 1/i^2

// f(x) = Sum_{i=1}^{infty} x_i
// integral  pi^2/16
// norm      pi/sqrt(6)
long double f_infty_basic_2(int scope, std::valarray<long double> points);

// f(x) = Sum_{i=1}^{infty} x^2*e^((cos(x_i))^2)
// integral  0.945775
// norm      1.812842
long double f_infty_exponent_2(int scope, std::valarray<long double> points);

// f(x) = Sum_{i=1}^{infty} Sum_{j=i}^{infty} sin(x_i*x_j)
// integral is 0.19467
// norm     is 0.78599
long double f_infty_products_2(int scope, std::valarray<long double> points);

#endif //MGR_FUNCTIONS_H
