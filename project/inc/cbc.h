#ifndef MGR_CBC_H
#define MGR_CBC_H

#include <cassert>
#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

/*
     * Component By Component(CBC) Algorithm for Product Weights
     * Optionally CBC with Random Shift
     *
     * author Dawid Majchrowski
*/

class cbc {
private:
    int n; // Prime number indicating max range of generators
    int d_max; // Dimension of vector to generate
    int random_search; // Number of iterations for random shift search. Set proportionately to dimension.
    std::pair<long double, int> product; // Cache storage to computations speedup
    std::vector<long double> sum_products; // Cache storage for computations speedup
    std::vector<long double> weights; // product weights (see in main.cpp)

    // Algorithm specific calculations
    void update_cache(int z, int d);

    // Calculate second-degree Bernoulli polynomial |  B2(x) := x^2 - x + 1/6
    static long double B2(long double x);

    long double get_error(const std::vector<int> &generators, const std::vector<int> &shift);

    long double get_error_with_cache(int z, int d);

public:

    // Perform CBC algorithm with optionally saving results to file
    std::vector<int> get_generators(bool save);

    // Perform CBC algorithm with Random Shift
    std::vector<long double> get_generators_with_shift();

    // Input for this algorithm class is vector dimensions and max range.
    cbc(int n, int d_max);
};

#endif //MGR_CBC_H
