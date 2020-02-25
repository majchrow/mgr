#ifndef MGR_MULTILEVEL_H
#define MGR_MULTILEVEL_H

#include <cassert>
#include "cbc.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <random>


class multilevel {
private:
    cbc cbc_instance;
public:
    int n;
    int d_max;
    long double eta;
    std::vector<int> points;
    std::vector<long double> shift;
    long double best_error;
    std::vector<long double> weights;

    void find_shift(int number_of_tries, int k);

    long double get_right_side(int k);

    std::vector<int> get_V(int k);

    long double get_W();

    long double get_error(std::vector<long double>);

    multilevel(long double eta, cbc cbc_instance);
};


#endif //MGR_MULTILEVEL_H
