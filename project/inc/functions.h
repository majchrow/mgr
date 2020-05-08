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

// f(x) = Sum_{i=1}^{infty} x_i | integral is 4.5
long double f_infty_basic(int scope, std::valarray<long double> points); // integral is 4.5

#endif //MGR_FUNCTIONS_H
