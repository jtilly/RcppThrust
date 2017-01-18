#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/copy.h>

#include "Rth.h"

#include "Rcpp.h"

// [[Rcpp::export]]
Rcpp::NumericVector mysort(Rcpp::NumericVector x) {

    size_t N = x.size();

    thrust::device_vector<double> y(N);
    thrust::copy(x.begin(), x.end(), y.begin());
    thrust::sort(y.begin(), y.end());
    thrust::copy(y.begin(), y.end(), x.begin());

    return(x);

}
