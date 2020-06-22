static const double Pi = 3.14159265358979 ;
static const double Euler = 2.71828182845905 ;
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector timesFoo(NumericVector x) 
{
	return x * Pi + Euler;
}


#include <Rcpp.h>
// timesFoo
NumericVector timesFoo(NumericVector x);
RcppExport SEXP sourceCpp_3_timesFoo(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(timesFoo(x));
    return rcpp_result_gen;
END_RCPP
}
