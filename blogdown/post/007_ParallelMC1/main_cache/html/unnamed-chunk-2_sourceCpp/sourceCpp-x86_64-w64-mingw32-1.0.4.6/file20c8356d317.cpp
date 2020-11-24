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
