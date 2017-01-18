#ifndef __RTH__
#define __RTH__

// this header file is taken from Rth
// https://github.com/Rth-org/Rth/
// written by Norm Matlof and Drew Schmidt

#include <thrust/detail/config.h>

// FIXME should we include CPP ?
#if THRUST_VERSION >= 100700
#if THRUST_DEVICE_SYSTEM == THRUST_DEVICE_SYSTEM_OMP
#include <omp.h>
#define RTH_OMP 1

#elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_SYSTEM_TBB
#include "tbb/task_scheduler_init.h"
#define RTH_TBB 1

#elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_SYSTEM_CUDA
#define RTH_CUDA 1
#endif
#else
#if THRUST_DEVICE_SYSTEM == THRUST_DEVICE_BACKEND_OMP
#include <omp.h>
#define RTH_OMP 1

#elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_BACKEND_TBB
#include "tbb/task_scheduler_init.h"
#define RTH_TBB 1

#elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_BACKEND_CUDA
#define RTH_CUDA 1
#endif
#endif

#define RTH_ERROR -2147483648 // int NA in R

#define RTH_INT(x) INTEGER(x)[0]

#if RTH_OMP
  #define RTH_GEN_NTHREADS(nthreads) omp_set_num_threads(RTH_INT(nthreads))
#elif RTH_TBB
  #define RTH_GEN_NTHREADS(nthreads) tbb::task_scheduler_init init(RTH_INT(nthreads))
#else
  #define RTH_GEN_NTHREADS(nthreads) // nothing
  // we don't want Rcpp sugar sample when we use CUDA (because it won't compile)
  #define Rcpp__sugar__sample_h
#endif

#define RTH_INT(x) INTEGER(x)[0]

#endif
