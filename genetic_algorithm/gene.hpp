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

namespace std {
    template <> struct hash<vector<size_t>>
    {
        size_t operator()(const vector<size_t>& vec) const
        {
            size_t seed = vec.size();
            for (auto& i : vec) {
                seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
    template <> struct hash<Gene>
    {
        size_t operator()(const Gene& x) const
        {
            return hash<vector<size_t>>()(x.get_gene());
        }
    };
}

#endif