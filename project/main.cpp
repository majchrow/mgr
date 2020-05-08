#include "multilevel.h"
#include <functions.h>

/*
     * Implementation of Multilevel Algorithm for Product Weights
     * Tested for weights of form w(i) = 0.9^(i)
     * Can be easily extended for any product weights
     *
     * author Dawid Majchrowski
*/

int main() {
    double s = 3;
    while (s < double(1 << 20)) {
        s *= 1.3;
        int S = (int) s;
        auto ml = multilevel(S, f_infty_basic);
        auto result = ml.calculate_multilevel();
        std::cout << "Error: " << 4.5 - result.second << " Cost: " << result.first << std::endl;
    }
    return 0;
}
