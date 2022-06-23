#pragma once
#ifndef _KNAPSACK_H
#define _KNAPSACK_H_

#include "genetic.h"

class knapsack : genetic_algorithm{
public:

	knapsack(std::vector<int> values, std::vector<int> weight, int K, int max_gen, int pop_size, int chromosome_length)
		: genetic_algorithm(max_gen, pop_size, chromosome_length){
		assert(values.size() == weight.size());
		this->values = values;
		this->weight = weight;
		this->K = K;
	}

	std::string solve_ks() {

		std::function<void()> evaluate = [&] {
			this->fitness.resize(this->population.size());
			this->fitness.assign(this->fitness.size(), 0);

			int P = 35;

			std::function<int(std::string)> f = [&](std::string s) {
				int vSum = 0, wSum = 0;

				for (int i = 0; i < this->values.size(); i++) {
					vSum += (this->values[i] * (s[i] - '0'));
					wSum += (this->weight[i] * (s[i] - '0'));
				}

				return (wSum <= this->K) ? vSum : 0;
			};

			std::transform(this->population.begin(), this->population.end(), this->fitness.begin(), f);
		};

		return this->solve(evaluate);
	}


private:
	std::vector<int> values;
	std::vector<int> weight;
	int K;
};
#endif
