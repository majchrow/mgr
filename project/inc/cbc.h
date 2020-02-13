#ifndef MGR_CBC_H
#define MGR_CBC_H

#include <cassert>
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

void init_all(int n, int weights_size);
void update_cache(int z, int d, int n);
const long double B2(const double x);
const long double get_error(int z, int n, int d);
std::vector<long double> cbc(int n, int d_max, bool save);

#endif //MGR_CBC_H
