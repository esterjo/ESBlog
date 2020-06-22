static const double Pi = 3.14159265358979 ;
static const double Euler = 2.71828182845905 ;
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector timesFoo(NumericVector x) 
{
	return x * Pi + Euler;
}
