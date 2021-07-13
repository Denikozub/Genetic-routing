/*
Vector class
- constuctor takes 2 Point objects
- double len(): return length of vector
- double cross_prod(const Vector&, const Vector&): return cross product of 2 vectors
*/

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