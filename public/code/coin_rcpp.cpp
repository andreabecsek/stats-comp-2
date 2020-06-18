#include <iostream>
#include <Rcpp.h>
using namespace Rcpp;


//[[Rcpp::export(flips)]]
NumericVector coin()
{
  NumericVector out(100);
  for(int i=0; i<100; i++)
  {
    out[i] = rand() % 2;
  }
  return out;
}
