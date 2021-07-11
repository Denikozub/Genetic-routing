#ifndef GENE_HPP
#define GENE_HPP

#include "../genetic_data/data.hpp"
#include <vector>

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
    double size() const;
    void init(size_t);
    double get_fitness_value() const;
    void update_chance(double);
    bool selected();
    bool survived() const;
    friend std::pair<Gene, Gene> cross_one_point(const Gene&, const Gene&);
    friend std::vector<Gene> mutate_triple(const Gene&);
    friend Gene mutate_one_point(const Gene&, size_t);
    friend bool operator< (const Gene&, const Gene&);
    const std::vector<size_t>& get_gene() const;
};

#endif