#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/copy.h>

#include "Rcpp.h"

struct simple_negate : public thrust::unary_function<double,double>
{
    __host__ __device__
    double operator()(double x)
    {
        return -x;
    }
};

// [[Rcpp::export]]
Rcpp::NumericVector myfunctor(Rcpp::NumericVector x) {

    size_t N = x.size();

    thrust::device_vector<double> y(N);
    thrust::copy(x.begin(), x.end(), y.begin());
    thrust::sort(y.begin(), y.end());
    thrust::transform(y.begin(), y.end(), y.begin(), simple_negate());
    thrust::copy(y.begin(), y.end(), x.begin());

    return(x);

}
