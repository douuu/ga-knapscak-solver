#pragma once
#ifndef _GENETIC_H_
#define _GENETIC_H_

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <assert.h>

#define _ROLL_() (rand() % 10 < 5)
#define _RUNIFORM_ (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))
#define _RAND_BITSTRING_ (_ROLL_() ? '1' : '0')
#define _LAMBDA_GENERATE_BITSTRING_ ([&] { return _RAND_BITSTRING_; })

class genetic_algorithm {

public:
	genetic_algorithm(int max_gen, int pop_size, int chromosome_length);

	std::vector<std::string> population, mating_pool;
	std::vector<int> fitness;

	void calculate_population_fitness();
	void generate_random_population();
	void rw_selection();
	std::vector<std::string> crossover(std::string p1, std::string p2);
	
	std::string solve(std::function<void(void)> evaluation_function = nullptr);
private:
	int max_gen, pop_size, chromosome_length;
};


#endif
