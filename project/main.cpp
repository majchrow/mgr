#include "multilevel.h"
#include <functions.h>
#include <iomanip>
#include <chrono>

/*
     * Implementation of Multilevel Algorithm for Product Weights
     * Tested for weights of form w(i) = 0.9^(i) and w(i) = 1/i^2
     * Can be easily extended for any product weights
     *
     * author Dawid Majchrowski
*/

int main() {
    std::ofstream file;
    file.open("result.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    for (int counter = 0; counter < 2; ++counter) {
        if (counter != 0) {
            file << std::endl;
        }

        const long double res_const = 9.201197890442720274372538475520024257973672112905565906276
                                      / 5.403710913225487161271285234189044743121036544770606571157;
//        double s = 3;
        double s = 50;
        while (s < 100000) {
            auto start = std::chrono::steady_clock::now();
            s *= 1.3;
//            s+=250;

            int S = (int) s;
            auto ml = multilevel(S, f_infty_products);
            auto result = ml.calculate_multilevel();
            std::cout << "S: " << S << std::endl;
            std::cout << "Cost: " << result.first << std::endl;

            auto end = std::chrono::steady_clock::now();
            auto time_span = static_cast<std::chrono::duration<double>>(end - start);
            std::cout << "Cost: " << result.first << " Error: " << std::setprecision(15)
                      << res_const - result.second
                      << std::endl;
            if (counter == 0) {
                file << result.first;
            } else {
//                file << time_span.count() << std::setprecision(5);

                file << std::setprecision(15) << res_const - result.second;
            }
            if (s < 100000) {
                file << ",";
            }
        }
    }
    file.close();
    return 0;
}
