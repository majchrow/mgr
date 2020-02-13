#include <iostream>
#include "utils.h"
#include "cbc.h"
#include <chrono>

int main() {
    int n = 2003;
    int d = 10;
    std::chrono::steady_clock sc;
    auto start = sc.now();
    init_all(n, d);
    auto x = cbc(n, d, false);
    auto end = sc.now();
    auto time_span = static_cast<std::chrono::duration<double>>(end - start);
    std::cout<<"Algorithm done, took : "<<time_span.count()<<" seconds." << std::endl;
    std::cout<<"Final z vector" << std::endl;
    for(auto &s: x){
        std::cout << s << ' ';
    }
    return 0;
}