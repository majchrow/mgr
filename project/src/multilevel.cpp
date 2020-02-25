#include "multilevel.h"

multilevel::multilevel(long double eta, cbc cbc_instance) {
    this->eta = eta;
    this->cbc_instance = std::move(cbc_instance);
    this->n = this->cbc_instance.n;
    this->d_max = this->cbc_instance.d_max;
    this->weights = this->cbc_instance.weights;
    this->best_error = -1.;
}

void multilevel::find_shift(int number_of_tries, int k) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0., 1.); // random numbers from [0,1)

    this->points = cbc_instance.get_generators(false); // get generators from cbc

    std::vector<long double> tmp_shift;
    tmp_shift.reserve(this->d_max);
    for (int j = 0; j < this->d_max; ++j) {
        tmp_shift.push_back(0.);
    }
    this->shift = tmp_shift; // search for best possible (or suitable) shift

    this->best_error = this->get_error(tmp_shift);
    std::cout << "Error: " << best_error << std::endl;

    for (int i = 0; i < number_of_tries; ++i) {
        std::vector<long double> t_shift;
        t_shift.reserve(this->d_max);
        for (int j = 0; j < this->d_max; ++j) {
            t_shift.push_back(dist(mt));
        }
        long double error = this->get_error(tmp_shift);
        std::cout << "Error: " << error << std::endl;
        if (error < best_error) {
            std::cout << "Better shift!" << std::endl;
            this->best_error = error;
            this->shift = t_shift;
            if (error < get_right_side(k)) {
                std::cout << "Suitable shift found" << std::endl;
                return;
            }
        }
    }
    std::cout << "Suitable shift not found, taking best one" << std::endl;
    for (auto &s: shift) {
        std::cout << s << ' ';
    }
    std::cout << std::endl;
    for (auto &s: points) {
        std::cout << s << ' ';
    }
}

long double multilevel::get_right_side(int k) { // TODO last powl exponent
    long double result = 0.;
    for (int &j: get_V(k)) {
        result = result + powl((weights.at(j - 1)), 1. / eta) * powl(powl(3, -1. / eta) + get_W(), 0);
    }
    return powl(result, eta) * powl(n - 1, -eta);
}

std::vector<int> multilevel::get_V(int k) { // TODO
    return std::vector<int>();
}

long double multilevel::get_W() {
    return powl(2 * M_PI * M_PI, -1 / eta) * (2 * std::riemann_zeta(2 / eta));
}

long double multilevel::get_error(std::vector<long double> t_shift) {
    long double sum = 0.;

    for (int i = 0; i < n; ++i) {
        long double products = 1.;
        for (int j = 0; j < d_max; ++j) {
            long double point = fmodl((((i + 1) * points.at(j) % n) * 1. / n) + t_shift.at(j), 1);
            products = products * (1. + weights.at(j) * (cbc_instance.B2(point) + 1. / 3));
        }
        sum += products;
    }

    return sum / n - cbc_instance.product.first;
}


