#ifndef FITNESS_HPP
#define FITNESS_HPP

#include "gene.hpp"

class Fitness {
public:
    virtual double eval(const Gene&) const = 0;
};

#endif