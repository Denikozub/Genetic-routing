/*
GeneticAlgo class
std::vector<size_t> solve() starts genetic algorithm
parameters:
- const Data* data: pointer to Data object for a particular task
- size_t population_size: max number of genes in population
- size_t epoch_number: max number of iterations
- size_t valueless_epoch_number: max number of iterations without improvements
- size_t preserve_best: number of best genes preserved during selection
- size_t preserve_worst: number of worst genes preserved during selection 
- size_t remove_duplicates: remove duplicate genes each ...th iteration
- double cross_percent: number of genes crossed
- double mutate_percent: number of genes mutated
- bool report = false: whether to print info about each iteration
returns: best gene
*/

#ifndef GENETIC_ALGO_HPP
#define GENETIC_ALGO_HPP

#include <vector>
#include "../genetic_data/data.hpp"

class GeneticAlgo {
public:
    GeneticAlgo() = default;
    std::vector<size_t> solve(const Data*, size_t, size_t, size_t, size_t,
        size_t, size_t, double, double, bool = false) const;
};

#endif