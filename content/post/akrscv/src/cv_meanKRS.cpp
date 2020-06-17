#include <Rcpp.h>

#include <akrs.h>

using namespace Rcpp;

// mean squared error
double mse(const NumericVector a, const NumericVector b){
  return mean(pow((a-b),2));
}

// shuffle randomly
int randWrapper(const int n){
  return(floor(unif_rand()));
}

// create a sequence of n samples from 0 to k
NumericVector sample_rcpp(int k, int n){
  NumericVector seq(n);
  
  // create ordered sequence
  for(int i = 1; i <= k; i++){
    for(int j = i; j <= n; j= j + k){
      seq[j-1] = i-1;
    }
  }
  
  // randomly shuffle the sequence of indeces
  std::random_shuffle(seq.begin(), seq.end(), randWrapper);
  return seq;
}


//' Perform cross-validation for meanKRS function based on different lambdas.
//' 
//' @param y numeric vector
//' @param x numeric vector
//' @param lambdas numeric vector
//' @param k int
//' @return Vector of mean squared errors for each lamdba.
// [[Rcpp::export(name = "cv_meanKRS_cpp")]]
NumericVector cv_meanKRS_cpp(const NumericVector y, const NumericVector x, const NumericVector lambdas, const int k){
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
      
      // fit model on training data and get 
      NumericVector fit = akrs::meanKRS_cpp(y_train, x_train, x_test, lambdas[i]);
      
      // calculate error for fold
      error = error + mse(fit, y_test)/k;
    }
    errors[i] = error;
  }
  
  return errors;
}