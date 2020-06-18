#include <iostream>
#include <Rcpp.h>
using namespace Rcpp;

//[[Rcpp::export(is_prime)]]
int is_prime(int x)
{
  int isprime = 1;
  
  for(int i = 2; i<=x/2; i++){
    if (x%i == 0){
      isprime = 0;
      break;
    }
  }
  return isprime;
}