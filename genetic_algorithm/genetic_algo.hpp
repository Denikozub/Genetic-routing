#ifndef GENETIC_ALGO_HPP
#define GENETIC_ALGO_HPP

#include <vector>
#include "route_fitness.hpp"

class GeneticAlgo {
public:
    GeneticAlgo() = default;
    template <typename T> std::vector<T> find_path(const Fitness&, size_t, size_t, size_t,
        size_t, size_t, size_t, int, int, int, double=0.5, double=0.5, bool = false) const;
};

#endif