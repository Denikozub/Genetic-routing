#ifndef GENE_HPP
#define GENE_HPP

#include "../geometry/point.hpp"
#include "../geometry/polygon.hpp"
#include <vector>
using std::vector;
using std::pair;

class Gene {
    size_t len = 0;
    vector<size_t> gene;
    double value = 0;
    double chance = 1;
    void remove_duplicates();
public:
    Gene() = default;
    double size() const;
    double get_value() const;
    void init(size_t);
    void update_value(const vector<Point>&, const vector<pair<Polygon, int>>&, const Point&, const Point&);
    void update_chance(double);
    bool selected();
    bool survived() const;
    friend pair<Gene, Gene> one_point_cross(const Gene&, const Gene&);
    friend Gene one_point_mutate(const Gene&, size_t);
    vector<Point> path(const vector<Point>&);
};

#endif