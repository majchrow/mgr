#ifndef MGR_CBC_H
#define MGR_CBC_H

#include <cassert>
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

class cbc {
public:
    int n;
    int d_max;
    std::pair<long double, int> product;
    std::vector<long double> sum_products;
    std::vector<long double> weights;

    void update_cache(int z, int d);

    long double B2(long double x);

    long double get_error(int z, int d);

    std::vector<int> get_generators(bool save);

    cbc(int n, int d_max);

    cbc();

};

#endif //MGR_CBC_H
