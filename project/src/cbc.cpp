/*
     * Component By Component(CBC) Algorithm for Product Weights
     * author Dawid Majchrowski
*/

#include "cbc.h"

cbc::cbc() {
    this->n = 0;
    this->d_max = 0;
}

cbc::cbc(int n, int d_max) {
    this->n = n;
    this->d_max = d_max;
    product = std::pair(0, 0);
    long double weight = 0.9;
    for (int i = 0; i < d_max; ++i) {
        weights.push_back(weight);
        weight *= 0.9;
    }
    for (int i = 0; i < n; ++i) {
        sum_products.push_back(1.);
    }

    product.first = (1 + (weights.at(0) * 1. / 3));
    product.second = 1;
}

void cbc::update_cache(int z, int d) {
    for (int i = 0; i < n; ++i) {
        sum_products.at(i) = sum_products.at(i) * (1 + weights.at(d - 1) * (1. / 3 + B2((((i + 1) * z % n) * 1. / n))));
    }
}

long double cbc::B2(long double x) {
    assert(x <= 1 && x >= 0);
    /*
     * Calculate second-degree Bernoulli polynomial
     * B2(x) := x^2 - x + 1/6
     */
    return x * x - x + 1. / 6;
}

long double cbc::get_error(int z, int d) {
    if (product.second == d - 1) {
        product.first = product.first * (1 + weights[d - 1] / 3.);
        product.second = d;
    }
    long double prod_sum = 0.;
    for (int i = 0; i < n; ++i) {
        prod_sum =
                prod_sum + (sum_products.at(i) * (1 + weights.at(d - 1) * (1. / 3 + B2((((i + 1) * z % n) * 1. / n)))));
    }

    return prod_sum / n - product.first;
}

std::vector<int> cbc::get_generators(bool save) {
    std::vector<int> z = {1};
    std::ofstream file;
    if (save) {
        file.open("result.txt", std::fstream::in | std::fstream::out | std::fstream::app);
        file << "d z_d D(z)" << std::endl;
        file << 1 << " " << 1 << " " << sqrtl(get_error(1, 1)) << std::endl;
    }
    update_cache(1, 1);
    for (int d = 2; d <= d_max; ++d) {
        long double best_error = 10.;
        int best_z = 0;
        for (int cur_z = 1; cur_z <= (n - 1) / 2; ++cur_z) {
            long double cur_err = get_error(cur_z, d);
            if (cur_err < best_error) {
                best_error = cur_err;
                best_z = cur_z;
            }
        }
        update_cache(best_z, d);
        z.push_back(best_z);
        if (save) {
            file << d << " " << best_z << " " << sqrtl(best_error) << std::endl;
        }
    }
    if (save) file.close();
    return z;
}
