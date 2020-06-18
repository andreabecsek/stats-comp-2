#include <iostream>
#include <Rcpp.h>
#include <RcppParallel.h>
using namespace Rcpp;

// [[Rcpp::plugins(openmp)]]
// [[Rcpp::depends(RcppParallel)]]

// int flip_coin(){
//   int n = rand() % 2;
//   return n;
// }

//[[Rcpp::export(flips_par)]]
NumericVector coin(int ncores)
{
  NumericVector out(100);
  RcppParallel::RVector<double> vo(out);
  
#if defined(_OPENMP)
  #pragma omp parallel for num_threads(ncores)
#endif
  
  for(int i=0; i<100; i++)
  {
    vo[i] = rand() % 2;
  }
  return out;
}
