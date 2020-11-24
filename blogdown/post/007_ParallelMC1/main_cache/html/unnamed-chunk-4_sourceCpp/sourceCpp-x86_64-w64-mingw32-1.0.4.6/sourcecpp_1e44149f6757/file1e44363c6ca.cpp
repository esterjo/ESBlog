#include <Rcpp.h>
#include <RcppParallel.h>

// [[Rcpp::depends(dqrng, RcppParallel)]]
// [[Rcpp::plugins(cpp11)]]

#include <pcg_random.hpp>
#include <random>
#include <algorithm>



// [[Rcpp::export]]
Rcpp::NumericVector tbbCP(const double lambda,
                          const double mu,
                          const double sigma,
                          const int N,
                          const uint64_t seed)
{
	using brange = tbb::blocked_range<size_t>;
	
	// Allocate vector
	Rcpp::NumericVector out(N);
	
	// Getting pointer to data
	auto begin = out.begin();
	
	tbb::parallel_for(brange(0, N), [=](brange& range){
		
		// Distribution for frequency
		std::poisson_distribution<int> Freq(lambda);
    
    	// Distribution for severity
    	std::lognormal_distribution<double> Sev(mu, sigma);
    	
    	// RNG local to thread, with unique stream
    	pcg64 rng(seed, range.end());
		
		// Serial version of sampler
		auto seq_CP = [&](){
			
			// Simulating loss event count
			int n = Freq(rng);
			
			// Accumulating loss severities
			double s = 0;
			for(int i = 0; i < n; ++i) s += Sev(rng);
			
			return s;
		};
		
		// Loop to simulate samples
		std::generate(begin + range.begin(), begin + range.end(), seq_CP);
	});
	
	return out;
}


#include <Rcpp.h>
// tbbCP
Rcpp::NumericVector tbbCP(const double lambda, const double mu, const double sigma, const int N, const uint64_t seed);
RcppExport SEXP sourceCpp_1_tbbCP(SEXP lambdaSEXP, SEXP muSEXP, SEXP sigmaSEXP, SEXP NSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const double >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< const double >::type mu(muSEXP);
    Rcpp::traits::input_parameter< const double >::type sigma(sigmaSEXP);
    Rcpp::traits::input_parameter< const int >::type N(NSEXP);
    Rcpp::traits::input_parameter< const uint64_t >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(tbbCP(lambda, mu, sigma, N, seed));
    return rcpp_result_gen;
END_RCPP
}
