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

// Product weights 0.9^i

// f(x) = Sum_{i=1}^{infty} x_i
// integral is 4.5
// norm is 3
long double f_infty_basic(int scope, std::valarray<long double> points);

// f(x) = Sum_{i=1}^{infty} x^2*e^((cos(x_i))^2)
// integral is 5.174660292067218426
// norm is     4.240401909495261331
long double f_infty_exponent(int scope, std::valarray<long double> points);

// f(x) = Sum_{i=1}^{infty} Sum_{j=i}^{infty} sin(x_i*x_j)
// integral is ?
// norm is     ?
long double f_infty_products(int scope, std::valarray<long double> points);


// Product weights 1/i^2

// f(x) = Sum_{i=1}^{infty} x_i
// integral is pi^2/16
// norm is pi/sqrt(6)
long double f_infty_basic_2(int scope, std::valarray<long double> points);

// f(x) = Sum_{i=1}^{infty} x^2*e^((cos(x_i))^2)
// integral is 0.945775
// norm is 1.812842249613730542147351739694744454522181344260841667565
long double f_infty_exponent_2(int scope, std::valarray<long double> points);

// f(x) = Sum_{i=1}^{infty} Sum_{j=i}^{infty} sin(x_i*x_j)
// integral is 0.194665365062964292889930975996617503428954559581367742855
// norm     is 0.785985014380567852624666239896424898672966013218760629037
long double f_infty_products_2(int scope, std::valarray<long double> points);

#endif //MGR_FUNCTIONS_H
