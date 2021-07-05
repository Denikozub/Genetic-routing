#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "point.hpp"

class Vector {
    double x, y;
public:
    Vector(const Point&, const Point&);
    double len();
    friend double cross_prod(const Vector&, const Vector&);
};

#endif