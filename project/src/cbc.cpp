#include "cbc.h"

cbc::cbc(int n, int d_max) {
    this->n = n;
    this->d_max = d_max;
    this->random_search = (int) 100;
    product = std::pair(0, 0);
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
    return x * x - x + 1. / 6;
}

long double cbc::get_error_with_cache(int z, int d) {
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
        file << 1 << " " << 1 << " " << sqrtl(get_error_with_cache(1, 1)) << std::endl;
    }
    update_cache(1, 1);
    for (int d = 2; d <= d_max; ++d) {
        long double best_error = 10.;
        int best_z = 0;
        for (int cur_z = 1; cur_z <= (n - 1) / 2; ++cur_z) {
            long double cur_err = get_error_with_cache(cur_z, d);
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

std::vector<long double> cbc::get_generators_with_shift() {
    std::vector<int> generators = get_generators(false);
    std::vector<int> best_shift(generators.size(), 0.0);

//    std::vector<long double> result;
//    result.reserve(generators.size());
//    for (int i = 0; i < generators.size(); ++i) {
//        result.push_back((long) (generators.at(i) + best_shift.at(i)) % this->n);
//    }
//    return result;

    std::vector<int> shift(generators.size(), 0.0);
    long double best_error = get_error(generators, shift);

    std::random_device rnd_device;
    std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
    std::uniform_int_distribution<int> dist{0, this->n};
    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    for (int i = 0; i < this->random_search; ++i) {
        generate(begin(shift), end(shift), gen);
        long double error = get_error(generators, shift);
        if (error < best_error) {
            best_error = error;
            best_shift = shift;
        }
    }
    std::vector<long double> result;
    result.reserve(generators.size());
    for (int i = 0; i < generators.size(); ++i) {
        result.push_back((long) (generators.at(i) + best_shift.at(i)) % this->n);
    }
    return result;
}

long double cbc::get_error(const std::vector<int> &generators, const std::vector<int> &shift) {
    assert(generators.size() == this->d_max);
    long double first_prod = 1.;
    for (int i = 0; i < this->d_max; ++i) {
        first_prod = first_prod * (1 + weights.at(i) / 3.);
    }
    long double sum_second = 0.;
    for (int i = 0; i < this->n; ++i) {
        long double prod_second = 1;
        for (int j = 0; j < this->d_max; ++j) {
            prod_second *= 1. + weights.at(j) *
                                (B2((((i + 1) * (shift.at(j) + generators.at(j))) % this->n) / (1. * this->n)) +
                                 1 / 3.);
        }
        sum_second += prod_second;
    }
    return sum_second / this->n - first_prod;
}
