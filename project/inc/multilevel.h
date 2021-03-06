#ifndef MGR_MULTILEVEL_H
#define MGR_MULTILEVEL_H

#include "cbc.h"
#include "qmc.h"
#include <cassert>
#include <cmath>
#include <random>
#include <vector>

/*
     * Multilevel Algorithm
     *
     * Description:
     * For each `level` apply QMC with points
     * generated by CBC with random shift
     *
     * author Dawid Majchrowski
*/

class multilevel {
private:
    int S; // Approximation cost for algorithm is O(S), but exact cost will be extracted from algorithm.
    int m; // Upper bound for number of variables to be used, extracted from S
    int M; // Algorithm constant, extracted from S
    long double cache; // Caching calculating intense values for speedup
    long double tau; // Algorithm constant from [1, decay), for this implementation 1 is taken
    std::function<long double(int, std::valarray<long double>)> f; // function to approximate
    std::vector<long double> weights; // product weights (see in main.cpp)

    long double get_cache();

    // Algorithm specific calculations
    long double get_omega(int k);

    long double get_x(int k);

    int static get_next_prime(int number);

    bool static is_prime(int number);

public:

    // Perform multilevel approximation return exact pair (cost, approximation)
    std::pair<int, long double> calculate_multilevel();

    // Input for this algorithm class is S (explained above) and function to approximate
    multilevel(int S, std::function<long double(int, std::valarray<long double>)> f);
};

#endif //MGR_MULTILEVEL_H
