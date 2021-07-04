#include "pathfinder.hpp"

Pathfinder::Pathfinder(const vector<Polygon>& set_obstacles, const Point& set_start,
        const Point& set_end) : obstacles(set_obstacles), start(set_start), end(set_end) {
    for (const auto& polygon : obstacles) {
        for (const auto& point : polygon.pts) {
            pts.push_back(point);
        }
    }
}

void Pathfinder::set_start(const Point& set_start) {
    start = set_start;
}

void Pathfinder::set_end(const Point& set_end) {
    end = set_end;
}

void Pathfinder::find_path(int population_size, int cross_mult) {
    vector<Gene> population(population_size);
}