/*
     * Component By Component(CBC) Algorithm for Product Weights
     * author Dawid Majchrowski
*/

#include "cbc.h"

std::pair<long double, int> product (0,0); // product(i) = product(i-1) * (1 + weight(i) * 1/3)
std::vector<long double> sum_products;     // sum_products(i) = 1/n * Sum(1..n) Products(j<i) (1 + weight(j) * 1/3)
std::vector<long double> weights;

void init_all(int n, int weights_size){
    long double weight = 0.9;
    for(int i = 0; i < weights_size; ++i){
        weights.push_back(weight);
        weight *= 0.9;
    }
    for(int i = 0; i < n; ++i){
        sum_products.push_back(1.);
    }

    product.first = (1 + (weights.at(0) * 1./3));
    product.second = 1;
}

void update_cache(int z, int d, int n){
    for(int i = 0; i<n; ++i){
        sum_products.at(i) = sum_products.at(i) * (1+weights.at(d-1)*(1./3 + B2((((i+1)*z % n)*1./n))));
    }
}

const long double B2(double x){
    assert(x <= 1 && x >= 0);
    /*
     * Calculate second-degree Bernoulli polynomial
     * B2(x) := x^2 - x + 1/6
     */
    return x*x - x + 1./6;
}

const long double get_error(int z, int n, int d){
    if(product.second == d-1){
        product.first = product.first * (1 + weights[d-1]/3.);
        product.second = d;
    }
    long double prod_sum = 0.;
    for(int i = 0; i < n; ++i){
        prod_sum = prod_sum + (sum_products.at(i) * (1+weights.at(d-1)*(1./3 + B2((((i+1)*z % n)*1./n)))));
    }

    return prod_sum/n - product.first;
}

std::vector<long double> cbc(int n, int d_max, bool save) {
    std::vector<long double> z = {1.};
    std::ofstream file;
    if(save) {
        file.open("result.txt", std::fstream::in | std::fstream::out | std::fstream::app);
        file << "d z_d D(z)" << std::endl;
        file << 1 << " " << 1 << " " << sqrt(get_error(1, n, 1)) << std::endl;
    }
    update_cache(1, 1, n);
    for(int d = 2; d <= d_max; ++d){
        long double best_error =  10.;
        int best_z = 0;
        for(int cur_z = 1; cur_z <= (n-1)/2; ++cur_z){
            long double cur_err  = get_error(cur_z, n, d);
            if(cur_err < best_error){
                best_error = cur_err;
                best_z = cur_z;
            }
        }
        update_cache(best_z, d, n);
        z.push_back(best_z);
        if(save){
            file << d << " " << best_z << " " << sqrt(best_error) << std::endl;
        }
    }
    if(save) file.close();
    return z;
}
