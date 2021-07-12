#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>
#include "gene.hpp"
#include "../genetic_data/data.hpp"

class Population {
    const Data* data;
    size_t max_size, range;
    std::vector<Gene> population;
    void add_gene(const Gene&);
public:
    Population(size_t, const Data*);
    size_t size() const;
    void fill();
    void update_chance();
    void remove_duplicates();
    void cross(double);
    void mutate(double);
    void select(size_t, size_t);
    double best_value() const;
    const std::vector<size_t>& best_gene() const;
    friend std::ostream& operator<< (std::ostream&, const Population&);
};

#endif