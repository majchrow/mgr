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
    const long double NORM = 3;

    long double sum = 0.;
    for (int i = 0; i < scope; ++i) {
        sum += pow(0.9, i + 1) * points[i];
    }
    return sum / NORM;
}

long double f_infty_exponent(int scope, std::valarray<long double> points) {
    const long double NORM = 4.240401909495261331576021509025032849799081202287591825594;

    long double sum = 0.;
    for (int i = 0; i < scope; ++i) {
        sum += pow(0.9, i + 1) * points[i] * points[i] * exp(cos(points[i]) * cos(points[i]));
    }
    return sum / NORM;
}

long double f_infty_products(int scope, std::valarray<long double> points) {
    const long double NORM = 5.403710913225487161271285234189044743121036544770606571157;

    long double sum = 0.;
    for (int i = 0; i < scope; ++i) {
        for (int j = i + 1; j < scope; ++j) {
            sum += pow(0.9, i + 1) * pow(0.9, j + 1) * sinl(points[i] * points[j]);
        }
    }
    return sum / NORM;
}

long double f_infty_basic_2(int scope, std::valarray<long double> points) {
    const long double NORM = M_PI / sqrt(6);
    long double sum = 0.;
    for (int i = 0; i < scope; ++i) {
        sum += (1. / pow(i + 1, 2)) * points[i];
    }
    return sum / NORM;
}

long double f_infty_exponent_2(int scope, std::valarray<long double> points) {
    const long double NORM = 1.812842249613730542147351739694744454522181344260841667565;
    long double sum = 0.;
    for (int i = 0; i < scope; ++i) {
        sum += (1. / pow(i + 1, 2)) * points[i] * points[i] * exp(cos(points[i]) * cos(points[i]));
    }
    return sum / NORM;
}

long double f_infty_products_2(int scope, std::valarray<long double> points) {
    const long double NORM = 0.785985014380567852624666239896424898672966013218760629037;

    long double sum = 0.;
    for (int i = 0; i < scope; ++i) {
        for (int j = i + 1; j < scope; ++j) {
            sum += (1. / pow(i + 1, 2)) * (1. / pow(j + 1, 2)) * sinl(points[i] * points[j]);
        }
    }
    return sum / NORM;
}