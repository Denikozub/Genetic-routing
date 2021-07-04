#include "pathfinder.hpp"
#include <algorithm>
#include <random>
using std::random_device;
using std::sort;

Pathfinder::Pathfinder(const vector<pair<Polygon, int>>& set_obstacles, const Point& set_start,
        const Point& set_end) : obstacles(set_obstacles), start(set_start), end(set_end) {
    for (const auto& polygon : obstacles) {
        for (auto it = polygon.first.geometry().begin(); it != polygon.first.geometry().end() - 1; ++it) {
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

void Pathfinder::init_population(vector<Gene>& population) const {
    for (auto& g : population) {
        g.init(pts.size());
    }
}

void Pathfinder::sort_population(vector<Gene>& population) const {
    sort(population.begin(), population.end(),
        [](const Gene& gene1, const Gene& gene2) { return gene1.value < gene2.value; });
}

void Pathfinder::update_population(vector<Gene>& population) const {
    for (auto& g : population) {
        g.update_value(pts, obstacles, start, end);
    }
}

void Pathfinder::cross_population(vector<Gene>& population, double cross_percent) const {
    random_device r;
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size * cross_percent / 2; ++i) {
        Gene parent1 = population[r() % population_size];
        Gene parent2 = population[r() % population_size];
        if (parent1.gene.size() > 1 || parent2.gene.size() > 1) {
            auto children = cross(parent1, parent2);
            population.push_back(children.first);
            population.push_back(children.second);
        }
    }
}

void Pathfinder::select_population(vector<Gene>& population, size_t population_size) const {
    population = { population.begin(), population.begin() + population_size };
}

vector<Point> Pathfinder::find_path(size_t population_size, size_t epoch_number, double cross_percent) const {
    vector<Gene> population(population_size);
    init_population(population);
    for (size_t i = 0; i < population_size; ++i) {
        cross_population(population, cross_percent);
        update_population(population);
        sort_population(population);
        select_population(population, population_size);
    }

    //for (auto i : population)
    //    std::cout << i.value << " ";
    //std::cout << "\n\n";

    for (auto i : population[0].gene)
        std::cout << i << " ";
    std::cout << "\n Value: " << population[0].value << "\n";

    vector<Point> path;
    for (size_t i : population[0].gene) {
        path.push_back(pts[i]);
    }
    return path;
}