#ifndef GENETIC_ALGO_HPP
#define GENETIC_ALGO_HPP

#include "../pathfinder/pathfinder.hpp"
#include "../geometry/polygon.hpp"
#include "gene.hpp"
using std::pair;

class GeneticAlgo : Pathfinder {
    vector<pair<Polygon, int>> obstacles;
    Point start, end;
    vector<Point> pts;
    void init_population(vector<Gene>&) const;
    void sort_population(vector<Gene>&) const;
    void cross_population(vector<Gene>&, double) const;
    void mutate_population(vector<Gene>&, double) const;
    void select_population(vector<Gene>&, size_t, size_t, size_t) const;
public:
    GeneticAlgo(const vector<pair<Polygon, int>>&, const Point&, const Point&);
    void set_start(const Point&) override;
    void set_end(const Point&) override;
    vector<Point> find_path(size_t, size_t, size_t, size_t, size_t, double, double, bool = false) const override;
};

#endif