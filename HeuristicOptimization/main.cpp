#include <memory>
#include "genetic.h"
#include "knapsack.h"

#define MAX_GENERATIONS 100

using namespace std;

inline shared_ptr<genetic_algorithm> setup_ga(int pop_size, int chromosome_length) {
	return make_shared<genetic_algorithm>(MAX_GENERATIONS, pop_size, chromosome_length);
}

shared_ptr<knapsack> setup_ks(int pop_size, int chromosome_length) {
	vector<int> values = { 60, 100, 120};
	vector<int> weights = { 10, 20, 30};
	constexpr int K = 50;

	return make_shared<knapsack>(values, weights, K, MAX_GENERATIONS, pop_size, chromosome_length);
}

int main() {
	int pop_size, chromosome_length;
	shared_ptr<knapsack> ks;
	shared_ptr<genetic_algorithm> ga;

	cout << "Enter population size : ";
	cin >> pop_size;

	cout << "Enter chromosome length : ";
	cin >> chromosome_length;

	ga = setup_ga(pop_size, chromosome_length);
	ks = setup_ks(pop_size, chromosome_length);
	
	cout << "running SGA " << '\n';
	string result_ga = ga.get()->solve();
	
	cout << "running SGA for knapsack problem " << '\n';
	string result_ks = ks.get()->solve_ks();

	cout << "result GA : " << result_ga << '\n';
	cout << "result KS : " << result_ks << '\n';
	

	return 0;
}