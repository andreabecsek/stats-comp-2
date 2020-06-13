// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
using namespace arma;

// [[Rcpp::export(name = "dmvnInt")]]
vec dmvnInt(mat& X, const rowvec& mu, mat& L)
{
  unsigned int d = X.n_cols;
  unsigned int m = X.n_rows;
  
  vec D = L.diag();
  vec out(m);
  vec z(d);
  
  double acc;
  unsigned int icol, irow, ii;
  for(icol = 0; icol < m; icol++)
  {
    for(irow = 0; irow < d; irow++)
    {
      acc = 0.0;
      for(ii = 0; ii < irow; ii++) 
        acc += z.at(ii) * L.at(irow, ii);
      z.at(irow) = ( X.at(icol, irow) - mu.at(irow) - acc ) / D.at(irow);
    }
    out.at(icol) = sum(square(z));
  }
  
  out = exp( - 0.5 * out - ( (d / 2.0) * log(2.0 * M_PI) + sum(log(D)) ) );
  
  return out;
}

// [[Rcpp::export(name = "lm_chol_Rcpp")]]
arma::vec lm_chol_Rcpp(arma::mat& X, arma::vec& y) {
  // get upper triangular cholesky factor
  arma::mat U = chol(X.t() * X);
  
  // solve for U*beta
  arma::vec C = solve(trimatl(U.t()), X.t() * y);
  
  // solve for beta
  arma::vec beta = solve(trimatu(U),C);
  return beta;
}

// [[Rcpp::export(name = "lm_qr_Rcpp")]]
arma::mat lm_qr_Rcpp(arma::mat& X, arma::vec& y) {
  // allocate memory and get Q and R
  arma::mat Q, R;
  qr_econ(Q,R,X);
  
  // solve for beta
  arma::vec beta = solve(R, Q.t()*y);
  return beta;
}


// [[Rcpp::export(name = "lm_local_Rcpp")]]
Rcpp::NumericVector lm_local_Rcpp(vec& y, 
                                  mat& x0, 
                                  mat& X0, 
                                  mat& x, 
                                  mat& X, 
                                  mat& H) {
  unsigned int n = x0.n_rows;
  arma::vec out(n, fill::zeros);
  
  // allocate memory
  mat Q,R;
  
  // get cholesky lower factor
  mat chol_dec = chol(H,"lower");
  
  for(int i=0; i<n; i++){
  
    // get weights and convert into diagonal matrix
    vec w = sqrt(dmvnInt(x,x0.row(i),chol_dec));
    //mat W = zeros<mat>(w.n_elem,w.n_elem);
    //W.each_col() += w;
    //mat W = diagmat(w);
    
    // get weighted X and y
    //mat X_tilde = sqrt(W)*X;
    //vec y_tilde = sqrt(W)*y;
    
    // get qr decomposition and solve for beta
    qr_econ(Q,R,X.each_col()%w);
    // vec coef = solve(R, Q.t()*(y.each_col()%w));
    // vec coef = lm_qr_Rcpp(X_tilde,y_tilde);
    
    // fitted values
    out(i) = dot(
      X0.row(i), 
      solve(R, Q.t()*(y.each_col()%w))
      );
  }
  
  return Rcpp::wrap(out);
}