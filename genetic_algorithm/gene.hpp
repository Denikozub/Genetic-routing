#ifndef GENE_HPP
#define GENE_HPP

#include "map_data.hpp"
#include <vector>

class Gene {
    MapData& data;
    size_t len;
    std::vector<size_t> gene;
    double fitness_value, chance;
    void remove_duplicates();
    void inverse(size_t, size_t);
    void insert(size_t, size_t);
    void swap(size_t, size_t);
public:
    Gene(MapData&);
    double size() const;
    void init(size_t);
    double get_fitness_value() const;
    void update_chance(double);
    bool selected();
    bool survived() const;
    double fitness();
    friend std::pair<Gene, Gene> cross(const Gene&, const Gene&);
    friend std::vector<Gene> mutate(const Gene&);
    friend bool operator>= (const Gene&, const Gene&);
    friend bool operator<= (const Gene&, const Gene&);
    friend bool operator> (const Gene&, const Gene&);
    friend bool operator< (const Gene&, const Gene&);
    Gene& operator= (const Gene&);
    const std::vector<size_t>& get_gene();
};

#endif