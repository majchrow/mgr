#include "qmc.h"

qmc::qmc(int n, std::function<long double(int, std::valarray<long double>)> f) {
    this->n = n;
    this->f = std::move(f);
}

long double qmc::calculate_qmc(int start, int end) {
    auto cbc_obj = cbc(this->n, end);
    std::vector<long double> generators = cbc_obj.get_generators_with_shift();
    std::valarray<long double> points(generators.size());
    std::valarray<long double> increment(generators.data(), generators.size());
    increment /= this->n;
    long double sum = 0;
    for (int i = 1; i <= this->n; ++i) {
        points += increment;
        points = points.apply([](long double point) -> long double {
            return point - int(point);
        });
        sum += this->f(end, points);
        sum -= this->f(start, points);
    }

    return sum / this->n;
}
