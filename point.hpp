#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
using std::ostream;

class Point {
public:
    double x, y;
    Point(double, double);
    friend bool operator== (const Point&, const Point&);
    friend bool operator!= (const Point&, const Point&);
    friend ostream& operator<< (ostream&, const Point&);
};

#endif
