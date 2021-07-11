#ifndef DATA_HPP
#define DATA_HPP

#include <vector>

struct Data {
    virtual size_t get_range() const = 0;
    virtual double fitness(const std::vector<size_t>&) const = 0;
};

#endif