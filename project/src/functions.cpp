#include "functions.h"

long double f_basic(int scope, std::valarray<long double> points) {
    assert(scope <= 16 && scope >= 0);
    assert(points.size() >= scope);
    long double sum = 0.;
    for (int i = 0; i < scope; ++i) {
        sum += pow(0.9, i + 1) * points[i];
    }
    return sum;
}

long double f_basic_2(int scope, std::valarray<long double> points) {
    long double sum = 0.;
    if (scope > 0) {
        sum += 0.9 * points[0];
    }

    if (scope > 1) {
        sum += 0.9 * points[1] + 0.9 * 0.9 * points[0] * points[1];
    }


    if (scope > 2) {
        sum += 0.9 * 0.9 * 0.9 * points[0] * points[1] * points[2];
    }

    return sum;
}

long double f_infty_basic(int scope, std::valarray<long double> points) {
    long double sum = 0.;
    for (int i = 0; i < scope; ++i) {
        sum += pow(0.9, i + 1) * points[i];
    }
    return sum;
}
