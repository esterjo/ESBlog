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


#include <Rcpp.h>
// EigenDecomp
Rcpp::List EigenDecomp(const Map<MatrixXd> M);
RcppExport SEXP sourceCpp_1_EigenDecomp(SEXP MSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Map<MatrixXd> >::type M(MSEXP);
    rcpp_result_gen = Rcpp::wrap(EigenDecomp(M));
    return rcpp_result_gen;
END_RCPP
}
