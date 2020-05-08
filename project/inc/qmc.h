#ifndef MGR_QMC_H
#define MGR_QMC_H

#include "cbc.h"
#include <valarray>
#include <vector>

/*
     * Quasi-Monte Carlo (QMC) Algorithm
     *
     * author Dawid Majchrowski
*/

class qmc {
private:
    int n; // Prime number indicating number of iterations (and input for CBC)
    std::function<long double(int, std::valarray<long double>)> f; // function to perform computations
public:

    /*
         * QMC
         * 1) Get generators from CBC with random shift.
         * 2) Perform QMC algorithm for function points between start and end interval.
         *
         * As a note, it is calculated as a difference between end and start, therefore cost will be
         * a summation instead of difference (just for exact value, asymptotically it is the same)
    */
    long double calculate_qmc(int start, int end);

    // Input for this algorithm class is prime number and function to perform qmc
    qmc(int n, std::function<long double(int, std::valarray<long double>)> f);
};


#endif //MGR_QMC_H
