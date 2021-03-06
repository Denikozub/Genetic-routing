/*
Data interface class
- size_t get_range(): return maximum value to be coded (number of coded elements)
- double fitness(const std::vector<size_t>&): return fitness value of a gene
*/

#ifndef DATA_HPP
#define DATA_HPP

#include <vector>

struct Data {
    virtual size_t get_range() const = 0;
    virtual double fitness(const std::vector<size_t>&) const = 0;
};

#endif