/*
Gene class - work with genes of variable length
- constructor takes a pointer to Data object for a particular task
- size_t size() const: return current gene length
- void init(size_t range) : initialize a gene with values in range
- double get_fitness_value() const : return current fitness value
- void update_chance(double average) : update chance value due to population average fitness value
- bool selected() : according to chance check if gene is selected for crossing / mutating
- bool survived() const : according to chance check if gene escaped killing attempt
- friend std::pair<Gene, Gene> cross_one_point(const Gene&, const Gene&) : perform one-point crossing
- friend std::vector<Gene> mutate_triple(const Gene&) : perform triple-operator mutation
- friend std::vector<Gene> mutate_one_point(const Gene&, size_t) : perform one-point mutation
- const std::vector<size_t>& get_gene() const: return gene sequence
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
public:
    Gene(const Data*);
    size_t size() const;
    void init(size_t);
    double get_fitness_value() const;
    void update_chance(double);
    bool selected();
    bool survived() const;
    friend std::pair<Gene, Gene> cross_one_point(const Gene&, const Gene&);
    friend std::vector<Gene> mutate_triple(const Gene&);
    friend std::vector<Gene> mutate_one_point(const Gene&, size_t);
    friend bool operator< (const Gene&, const Gene&);
    friend bool operator== (const Gene&, const Gene&);
    const std::vector<size_t>& get_gene() const;
    friend std::ostream& operator<< (std::ostream&, const Gene&);
};

#endif