#include <iostream>
#include <Rcpp.h>
using namespace Rcpp;

int flip_coin(){
  int n = rand() % 2;
  return n;
}

//[[Rcpp::export(mean_flips)]]
NumericVector coin()
{
  NumericVector out(100);
  for(int i=0; i<100; i++)
  {
    out[i] = flip_coin();
  }
  return out;
}
