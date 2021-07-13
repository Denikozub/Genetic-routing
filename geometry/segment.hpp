/*
Segment class:
- constuctor takes 2 Point objects
- bool crosses(const T&): check intersection with Polygon and Segment objects
- touches and overlays are NOT considered as intersections
- TODO: currently segment intersecting a polygon overlapping
  its diagonal does not count as an intersection
*/

#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "point.hpp"
#include <iostream>

class Segment {
    Point a, b;
public:
    Segment(const Point&, const Point&);
    double len();
    template <typename T> bool crosses(const T&);
    friend bool operator== (const Segment&, const Segment&);
    friend std::ostream& operator<< (std::ostream&, const Segment&);
};

#endif