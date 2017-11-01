#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

const int max_int = ~(1<<31);

class Random
{
	public:
		Random(bool pseudo = false);
		int poisson(double mean);	
	private:
		int reseed();
		double random_real();
		int seed;
		int multiplier;
		int add_on;	
};

#endif