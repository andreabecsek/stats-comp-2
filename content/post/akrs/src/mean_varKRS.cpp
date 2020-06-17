#include <Rcpp.h>

using namespace Rcpp;

//'#'Estimate conditional expectation using a Gaussian Kernel with changing bandwidth.
//'
//' @param y numeric vector
//' @param x numeric vector
//' @param x0 numeric vector
//' @param lambda double
//' @return conditional expectation
// [[Rcpp::export(name = "varKRS_cpp")]]
NumericVector varKRS_cpp(const NumericVector y, const NumericVector x, const NumericVector x0, const double lambda){
  int n = x.size();
  int n0 = x0.size();
  NumericVector res(n);
  NumericVector mu(n);
  
  NumericVector madHat(n0);
  NumericVector out(n0);
  
  for(int i = 0; i < n; i++){
    NumericVector kernel = dnorm(x, x[i],lambda,0);
    
    double num = 0;
    for(int j = 0; j < n; j++){
      num = num + kernel[j] * y[j];
    }
    
    double denom = 0;
    for(int j = 0; j < n; j++){
      denom = denom + kernel[j];
    }
    mu[i] = num / denom;
  }
  
  NumericVector resAbs(n);
  resAbs = abs(y - mu);
  
  
  NumericVector w(n0);
  double sum_w = 0;
  
  for(int i=0; i < n0; i++){
    NumericVector kernel = dnorm(x, x0[i],lambda,0);
    
    double num = 0;
    for(int j = 0; j < n; j++){
      num = num + kernel[j] * resAbs[j];
    }
    
    double denom = 0;
    for(int j = 0; j < n; j++){
      denom = denom + kernel[j];
    }
    madHat[i] = num / denom;
    w[i] = denom / num;
    sum_w = sum_w + w[i];
    
  }
  
  for(int i = 0; i < n0; i++){
    w[i] = n0 * w[i] / sum_w;
  }
  
  for(int i=0; i < n0; i++){
    NumericVector kernel = dnorm(x, x0[i],lambda*w[i],0);
    
    double num = 0;
    for(int j = 0; j < n; j++){
      num = num + kernel[j] * y[j];
    }
    
    double denom = 0;
    for(int j = 0; j < n; j++){
      denom = denom + kernel[j];
    }
    out[i] = num / denom;
  }
  
  
  return out;
}