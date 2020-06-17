#include <Rcpp.h>

// [[Rcpp::interfaces(cpp)]]

using namespace Rcpp;

//'Estimate conditional expectation using a Gaussian Kernel with fixed variance.
//'
//' @param y numeric vector
//' @param x numeric vector
//' @param x0 numeric vector
//' @param lambda double
//' @return conditional expectation
// [[Rcpp::export(name = "meanKRS_cpp")]]
NumericVector meanKRS_cpp(const NumericVector y, const NumericVector x, const NumericVector x0, const double lambda){
  // define required variables and output vector
  int n = x.size();
  int n0 = x0.size();
  NumericVector out(n0);
  
  // estimate conditional expectation
  for(int i = 0; i < n0; i++){
    NumericVector kernel = dnorm(x, x0[i],lambda,0);
    
    // numerator
    double num = 0;
    for(int j = 0; j < n; j++){
      num = num + kernel[j] * y[j];
    }
    
    //denominator
    double denom = 0;
    for(int j = 0; j < n; j++){
      denom = denom + kernel[j];
    }
    out[i] = num / denom;
  }
  return out;
}