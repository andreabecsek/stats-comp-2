#include <Rcpp.h>
#include <Rmath.h>
#include <algorithm>
#include <random> 
using namespace Rcpp;

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

// mean squared error
double mse(const NumericVector a, const NumericVector b){
  return mean(pow((a-b),2));
}

// shuffle randomly
int randWrapper(const int n){
  return(floor(unif_rand()));
}

// create a sequence of n samples from 0 to k
// [[Rcpp::export(name = "sample_rcpp")]]
NumericVector sample_rcpp(int k, int n){
  NumericVector seq(n);
  
  // create ordered sequence
  for(int i = 1; i <= k; i++){
    for(int j = i; j <= n; j= j + k){
      seq[j-1] = i-1;
    }
  }
  //seq = Rcpp::sample(seq, n);
  std::random_shuffle(seq.begin(), seq.end(), randWrapper);
  return seq;
}




// [[Rcpp::export(name = "cv_varKRS_cpp")]]
NumericVector cv_varKRS_cpp(const NumericVector y, const NumericVector x, const NumericVector lambdas, const int k){
  int n = x.size();
  int m = lambdas.size();
  
  NumericVector errors(m);
  NumericVector folds = sample_rcpp(k, n);
  
  // iterate over lambdas
  for(int i=0; i < m; i++){
    double error = 0;
    
    // iterate over folds
    for(int j = 0; j < k; j++){
      
      // split the data into train and test set
      NumericVector x_test = x[(folds==j)];
      NumericVector x_train = x[(folds!=j)];
      NumericVector y_test = y[(folds==j)];
      NumericVector y_train = y[(folds!=j)];
      
      // fit model on training data and obtain predictions for test set
      NumericVector fit = varKRS_cpp(y_train, x_train, x_test, lambdas[i]);
      
      // calculate error for fold
      error = error + mse(fit, y_test)/k;
    }
    errors[i] = error;
  }
  
  return errors;
}