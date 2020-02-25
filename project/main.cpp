#include <iostream>
#include "utils.h"
#include "cbc.h"
#include <chrono>
#include "multilevel.h"

int main() {
    int n = 2003;
    int d = 10;
    std::chrono::steady_clock sc;
    auto start = sc.now();

    auto x = cbc(n, d);
    auto xd = multilevel(1, x);
    xd.find_shift(5, 5);
    auto end = sc.now();
    auto time_span = static_cast<std::chrono::duration<double>>(end - start);
    std::cout<<"Algorithm done, took : "<<time_span.count()<<" seconds." << std::endl;
    std::cout<<"Final z vector" << std::endl;
//    for(auto &s: x){
//        std::cout << s << ' ';
//    }
    return 0;
}