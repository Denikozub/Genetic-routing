#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>
#include "gene.hpp"
#include "../genetic_data/data.hpp"

class Population {
    size_t max_size, range;
    std::vector<Gene> population;
    void add_gene(const Gene&);
public:
    Population(size_t, const Data*);
    size_t size() const;
    void init_population();
    void update_population_chance();
    void cross_population_chance();
    void cross_population_random(double);
    void mutate_population_chance();
    void mutate_population_random(double);
    void select_population_chance(size_t, size_t);
    void select_population_best(size_t, size_t);
    double best_value() const;
    const std::vector<size_t>& best_gene() const;
};

#endif