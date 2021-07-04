#include "pathfinder.hpp"

Pathfinder::Pathfinder(const vector<Polygon>& set_obstacles, const Point& set_start,
        const Point& set_end) : obstacles(set_obstacles), start(set_start), end(set_end) {
    for (const auto& polygon : obstacles) {
        for (auto it = polygon.geometry().begin(); it != polygon.geometry().end() - 1; ++it) {
            pts.push_back(*it);
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
    //vector<Gene> population(population_size);
}