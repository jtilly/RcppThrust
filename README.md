RcppThrust
===
[![Build Status](https://travis-ci.org/jtilly/RcppThrust.svg?branch=master)](https://travis-ci.org/jtilly/RcppThrust)

Based on Norm Matloff and Drew Schmidt's Rth package (see https://github.com/Rth-org/Rth/). The idea is to use Thrust in a package that uses Rcpp to expose C++ functions to R.

### Requirements for CUDA backend
 * CUDA 8.0
 * One issue in Rcpp needs to be resolved. In Version `0.12.9` of Rcpp, in file `system.file("include/Rcpp/vector/proxy.h", package="Rcpp")` line 98 must be `string_name_proxy& operator=( string_name_proxy& other){`, i.e. you need to remove `const`.

### Install with CUDA backend
```{r}
devtools::install_github("jtilly/RcppThrust",
                         args = "--configure-args=\"--with-backend=CUDA
                                 --with-cuda-home=/usr/local/cuda-8.0/\"")
```

### Install with OpenMP backend
```{r}
devtools::install_github("jtilly/RcppThrust")
```

### Examples

*Use thrust::sort()*
```{c++}
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
```
*Use user-defined functor*
```{c++}
#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/copy.h>

#include "Rth.h"

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
```