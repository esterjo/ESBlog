#include <Rcpp.h>

// [[Rcpp::depends(dqrng)]]
// [[Rcpp::plugins(cpp11)]]

#include <pcg_random.hpp>
#include <random>
#include <algorithm>

// [[Rcpp::export]]
Rcpp::NumericVector cppCP(const double lambda,
                          const double mu,
                          const double sigma,
                          const int N)
{
	// Seed with a real random value, if available
	pcg_extras::seed_seq_from<std::random_device> seed_source;

	// Make a random number engine
	pcg64 rng(seed_source);
    
	// Distribution for frequency
	std::poisson_distribution<int> Freq(lambda);
    
	// Distribution for severity
	std::lognormal_distribution<double> Sev(mu, sigma);
	
	// Allocate vector
	Rcpp::NumericVector out(N);

    // Simulate samples
    std::generate(out.begin(), out.end(), [&](){
    	
    	// Simulating loss event count
    	int n = Freq(rng);
    	
    	// Accumulating loss severities
    	double s = 0;
    	for(int i = 0; i < n; ++i) s += Sev(rng);
    	
    	return s;
    });
    
    return out;
}


#include <Rcpp.h>
// cppCP
Rcpp::NumericVector cppCP(const double lambda, const double mu, const double sigma, const int N);
RcppExport SEXP sourceCpp_17_cppCP(SEXP lambdaSEXP, SEXP muSEXP, SEXP sigmaSEXP, SEXP NSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const double >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< const double >::type mu(muSEXP);
    Rcpp::traits::input_parameter< const double >::type sigma(sigmaSEXP);
    Rcpp::traits::input_parameter< const int >::type N(NSEXP);
    rcpp_result_gen = Rcpp::wrap(cppCP(lambda, mu, sigma, N));
    return rcpp_result_gen;
END_RCPP
}
