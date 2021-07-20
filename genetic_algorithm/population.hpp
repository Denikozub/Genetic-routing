/*
Population class:
- constructor takes max number of genes in population and
  a pointer to Data object for a particular task
- size_t size() const: return current size of population
- void fill(): fill population up to max number of genes
- void update_chance(): update chance values of all genes
- void remove_duplicates(): remove duplicates
- void cross(double cross_percent): perform crossing on a given percent of genes
  first population_size * cross_percent / 8 genes are guaranteed to
  be chosen as one of the parents, others are chosen randomly
- void mutate(double mutate_percent): perform mutation on a given percent of genes
  first population_size * cross_percent / 4 genes are guaranteed to be mutated, others are chosen randomly
- void select(size_t preserve_best, size_t preserve_worst):
  perform selection preserving best and worst genes
  killing attempts will be made unlil there are max number of genes in population
- double best_value() const: return fitness value of best gene
- const std::vector<size_t>& best_gene() const: return best gene
*/

#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <vector>
#include "gene.hpp"
#include "../genetic_data/data.hpp"

class Population {
    const Data* data;
    size_t max_size;
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