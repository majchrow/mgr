#include "multilevel.h"

multilevel::multilevel(int S, std::function<long double(int, std::valarray<long double>)> f) {
    this->S = S;
    int best_M = 1;
    int best_m = 1;
    while (S >= 2 * best_M) {
        this->M = best_M;
        this->m = best_m;
        best_M += (1 << best_m);
        ++best_m;
    }
    this->f = std::move(f);
    this->tau = 1;
    this->cache = 0;
    long double weight = 0.9;
    for (int i = 0; i < 1 << this->m; ++i) {
        weights.push_back(weight);
        weight *= 0.9;
    }
}

std::pair<int, long double> multilevel::calculate_multilevel() {
    long double approximation = 0.;
    int cost = 0;
    int start = 0;
    int end = 0;
    int counter = 0;
    while (counter < this->m) {
        ++counter;
        start = end;
        if (end == 0) {
            end = 1;
        } else {
            end *= 2;
        }
        long double x = get_x(counter);
        int number = (int) x + 1;
        int n = get_next_prime(number);
        auto qmc_instance = qmc(n, this->f);
//        cost += n * (start + end);
        cost += n * (start * (start - 1) / 2. + end * (end - 1) / 2.);
        approximation += qmc_instance.calculate_qmc(start, end);
    }
    return std::pair<int, long double>(cost, approximation);
}

long double multilevel::get_omega(int k) {
    if (k == 0) return weights.at(k);
    long double omega = 0.;
    for (int j = (1 << (k - 1)) + 1; j <= (1 << k); ++j) {
        omega += weights.at(j);
    }
    return omega;
}

long double multilevel::get_cache() {
    if (std::abs(this->cache) < 1e-9) {
        long double sum = 0.;
        for (int i = 0; i < this->m; ++i) {
            long double omega = get_omega(i);
            omega = powl(omega, 1 / (tau + 1));
            sum += powl(1 << i, this->tau / (1 + this->tau)) * omega;
        }
        this->cache = 1 / sum;

    }
    return this->cache;
}

long double multilevel::get_x(int k) {
    assert(k > 0 && this->M <= 2 * this->S);
    long double C = (this->S - this->M) * this->get_cache();
    long double result =
            C * powl(get_omega(k - 1), 1. / (this->tau + 1)) * powl((1 << (k - 1)), -1. / (this->tau + 1)) + 1.;
    return result;
}

int multilevel::get_next_prime(int number) {
    if (number == 2) return number;
    if (number % 2 == 0) ++number;
    while (true) {
        if (is_prime(number)) return number;
        number += 2;
    }
}

bool multilevel::is_prime(int number) {
    if (number <= 1) return false;
    if (number <= 3) return true;
    if (number % 2 == 0 || number % 3 == 0) return false;

    for (int i = 5; i * i <= number; i = i + 6)
        if (number % i == 0 || number % (i + 2) == 0)
            return false;

    return true;
}
