#ifndef GENETIC_ALGO_HPP
#define GENETIC_ALGO_HPP

#include <vector>
#include "../genetic_data/data.hpp"

class GeneticAlgo {
public:
    GeneticAlgo() = default;
    std::vector<size_t> find_path(const Data*, size_t, size_t, size_t, size_t,
        size_t, double=0.5, double=0.5, bool = false) const;
};

#endif