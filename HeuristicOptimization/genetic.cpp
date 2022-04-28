#include "genetic.h"

genetic_algorithm::genetic_algorithm(int max_gen, int pop_size, int chromosome_length) {
	assert(pop_size > 0 && chromosome_length > 0);

	this->max_gen = max_gen;
	this->pop_size = pop_size;
	this->chromosome_length = chromosome_length;

	this->mating_pool = std::vector<std::string>(pop_size);
	this->population = std::vector<std::string>(pop_size);
	this->fitness = std::vector<int>(pop_size);
}


void genetic_algorithm::calculate_population_fitness() {
	this->fitness.resize(this->population.size());
	this->fitness.assign(this->fitness.size(), 0);

	std::function<int(std::string)> f = [&](std::string s) {
		return std::count(s.begin(), s.end(), '1');
	};

	std::transform(this->population.begin(), this->population.end(), this->fitness.begin(), f);
}

void genetic_algorithm::generate_random_population() {

	std::function<std::string(void)> f = [&] {
		std::string s(this->chromosome_length, ' ');
		std::generate(s.begin(), s.end(), _LAMBDA_GENERATE_BITSTRING_);
		return s;
	};

	std::generate(this->population.begin(), this->population.end(), f);
}

void genetic_algorithm::rw_selection() {
	std::vector<float> pop_freq(this->fitness.size());

	int pop_total_fitness = std::accumulate(this->fitness.begin(), this->fitness.end(), 0);

	std::function<float(float)> f = [&](float sample_fitness) {
		return sample_fitness / pop_total_fitness;
	};

	std::transform(fitness.begin(), fitness.end(), pop_freq.begin(), f);

	std::vector<float> pop_prob(this->fitness.size());

	std::partial_sum(pop_freq.begin(), pop_freq.end(), pop_prob.begin());

	int current_member = 0;
	while (current_member < this->pop_size) {
		int i = 0;

		while (pop_prob[i] < _RUNIFORM_) i++;

		mating_pool[current_member++] = this->population[i];
	}
}

std::string genetic_algorithm::solve(std::function<void(void)> evaluation_function) {
	int no_iter = 0, best_fitness;
	std::string best;

	this->generate_random_population();
	
	if (evaluation_function != nullptr) {
		evaluation_function();
	}
	else {
		this->calculate_population_fitness();
	}

	best = this->population[0];
	best_fitness = this->fitness[0];

	while (no_iter < this->max_gen) {

		for (int i = 0; i < this->fitness.size(); i++) {
			if (best_fitness < this->fitness[i]) {
				
				best_fitness = this->fitness[i];
				best = this->population[i];
			}
		}

		std::vector<std::string> children;
		for (int i = 0; i < this->pop_size - 1; i += 2) {

			this->rw_selection();
			std::string p1 = this->mating_pool[i];
			std::string p2 = this->mating_pool[i + 1];
			children  = this->crossover(p1, p2);
		}

		this->population = children;

		if (evaluation_function != nullptr) {
			evaluation_function();
		}
		else {
			this->calculate_population_fitness();
		}

		no_iter++;
	}

	return best;
}

std::vector<std::string> genetic_algorithm::crossover(std::string p1, std::string p2) {
	std::string c1, c2;
	std::vector<std::string> children;
	int split_index;

	c1 = p1;
	c2 = p2;

	if (_RUNIFORM_ < 1) {
		split_index = rand() % (this->chromosome_length - 2) + 1;

		c1 = p1.substr(0, split_index) + p2.substr(split_index, this->chromosome_length);
		c2 = p2.substr(0, split_index) + p1.substr(split_index, this->chromosome_length);

		children.push_back(c1);
		children.push_back(c2);
	}

	return children;
}
