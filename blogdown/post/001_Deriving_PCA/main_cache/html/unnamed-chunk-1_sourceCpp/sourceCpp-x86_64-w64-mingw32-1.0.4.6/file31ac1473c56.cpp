#include <RcppEigen.h>

// [[Rcpp::depends(RcppEigen)]]

using namespace Eigen;


// [[Rcpp::export]]
Rcpp::List EigenDecomp(const Map<MatrixXd> M) 
{
	//Constructing sample covariance matrix 
	MatrixXd centered = M.rowwise() - M.colwise().mean();
	MatrixXd cov = centered.adjoint() * centered/(M.rows()-1);
	
	//Using Eigen's eigensolver (with default settings)
	SelfAdjointEigenSolver<MatrixXd> eig(cov);
	
	VectorXd values = eig.eigenvalues();
	MatrixXd vectors = eig.eigenvectors();
	
	//Returning results as a R-list
	return Rcpp::List::create(Rcpp::Named("Cov") = cov,
                           Rcpp::Named("values") = values,
                           Rcpp::Named("vectors") = vectors);
}
