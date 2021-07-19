/*
Gene class - work with genes of variable length
- constructor takes a pointer to Data object for a particular task
- size_t size() const: return current gene length
- void init(size_t range) : randomly initialize a gene with values in range
- double get_fitness_value() const : return current fitness value
- const std::vector<size_t>& get_gene() const: return gene sequence
- void update_chance(double average) : update chance value due to population average fitness value
- bool selected() : according to chance check if gene is selected for crossing / mutating
  if chance >= 1 it is decreased by 1 if gene is selected
- bool survived() const : according to chance check if gene escaped killing attempt
  formula survive_chance = chance / (chance + 1) makes it easier to survive for ganes with high chance
- std::pair<Gene, Gene> cross(const Gene& partner) : perform one-point crossing
  point is chosen randomly and parents swap their genes around this point
- Gene mutate(const Gene&) : perform either Wang greedy hybrid operator (>= 6 points) or one-point mutation:
  ramdomly choose 2 points of a gene and perform 3 operators: inverse, insert, swap and return best mutant or
  ramdomly choose 1 point of a gene and perform 3 operators: change, insert, remove and return best mutant
*/

#ifndef GENE_HPP
#define GENE_HPP

#include "../genetic_data/data.hpp"
#include <vector>
#include <iostream>

class Gene {
    const Data* data;
    size_t len;
    std::vector<size_t> gene;
    double fitness_value, chance;
    void remove_duplicates();
    void inverse(size_t, size_t);
    void insert(size_t, size_t);
    void swap(size_t, size_t);
    void cut_fill(size_t, size_t, const Gene&);
    Gene mutate_one_point(size_t);
    Gene mutate_hybrid();
public:
    Gene(const Data*);
    size_t size() const;
    void init(size_t);
    double get_fitness_value() const;
    const std::vector<size_t>& get_gene() const;
    void update_chance(double);
    bool selected();
    bool survived() const;
    std::pair<Gene, Gene> cross(const Gene&);
    Gene mutate(size_t);
    friend bool operator< (const Gene&, const Gene&);
    friend bool operator== (const Gene&, const Gene&);
    friend std::ostream& operator<< (std::ostream&, const Gene&);
};

#endif