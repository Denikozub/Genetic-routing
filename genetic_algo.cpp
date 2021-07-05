#include "genetic_algo.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <random>
using std::random_device;
using std::sort;
using std::cout;
using std::endl;
using std::invalid_argument;

GeneticAlgo::GeneticAlgo(const vector<pair<Polygon, int>>& set_obstacles, const Point& set_start,
        const Point& set_end) : obstacles(set_obstacles), start(set_start), end(set_end) {
    for (const auto& polygon : obstacles) {
        for (auto it = polygon.first.geometry().begin(); it != polygon.first.geometry().end() - 1; ++it) {
            pts.push_back(*it);
        }
    }
}

void GeneticAlgo::set_start(const Point& set_start) {
    start = set_start;
}

void GeneticAlgo::set_end(const Point& set_end) {
    end = set_end;
}

void GeneticAlgo::init_population(vector<Gene>& population) const {
    for (auto& g : population) {
        g.init(pts.size());
    }
}

void GeneticAlgo::sort_population(vector<Gene>& population) const {
    for (auto& g : population) {
        g.update_value(pts, obstacles, start, end);
    }
    sort(population.begin(), population.end(),
        [](const Gene& gene1, const Gene& gene2) { return gene1.value < gene2.value; });
}

void GeneticAlgo::cross_population(vector<Gene>& population, double cross_percent) const {
    random_device r;
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size * cross_percent / 2; ++i) {
        Gene parent1 = population[r() % population_size];
        Gene parent2 = population[r() % population_size];
        if (parent1.gene.size() > 1 || parent2.gene.size() > 1) {
            auto children = one_point_cross(parent1, parent2);
            population.push_back(children.first);
            population.push_back(children.second);
        }
    }
}

void GeneticAlgo::mutate_population(vector<Gene>& population, double mutate_percent) const {
    random_device r;
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size * mutate_percent; ++i) {
        Gene src = population[r() % population_size];
        if (src.gene.size() > 0) {
            auto mutant = one_point_mutate(src, pts.size());
            population.push_back(mutant);
        }
    }
}

void GeneticAlgo::select_population(vector<Gene>& population,
        size_t population_size, size_t preserve_best, size_t preserve_worst) const {
    vector<Gene> best = { population.begin(), population.begin() + population_size - preserve_worst };
    best.insert(best.end(), population.end() - preserve_worst, population.end());
    population = best;
}

vector<Point> GeneticAlgo::find_path(size_t population_size, size_t epoch_number,
        size_t valueless_epoch_number, size_t preserve_best, size_t preserve_worst,
        double cross_percent, double mutate_percent, bool report) const {
    if (population_size <= 0) {
        throw invalid_argument("Wrong population size");
    }
    if (epoch_number <= 0) {
        throw invalid_argument("Wrong epoch number");
    }
    if (valueless_epoch_number < 0) {
        throw invalid_argument("Wrong valueless epoch number");
    }
    if (preserve_best < 0 || preserve_best > population_size) {
        throw invalid_argument("Wrong preserve_best number");
    }
    if (preserve_worst < 0 || preserve_worst > population_size) {
        throw invalid_argument("Wrong preserve_worst number");
    }
    if (preserve_best + preserve_worst > population_size) {
        throw invalid_argument("Wrong preserve_best & preserve_worst ratio");
    }
    if (cross_percent < 0) {
        throw invalid_argument("Wrong cross percent");
    }
    if (mutate_percent <= 0) {
        throw invalid_argument("Wrong mutate percent");
    }
    vector<Gene> population(population_size);
    double last_value = 0;
    size_t valueless_epochs = 0;
    init_population(population);
    for (size_t i = 0; i < epoch_number; ++i) {
        cross_population(population, cross_percent);
        mutate_population(population, mutate_percent);
        sort_population(population);
        select_population(population, population_size, preserve_best, preserve_worst);
        double curr_value = population[0].value;
        if (report) {
            cout << "==================== Iteration " << i + 1 << " ====================\n";
            cout << "Current best value: " << curr_value << "\n\n";
        }
        if (valueless_epoch_number == 0) {
            continue;
        }
        if (last_value == curr_value) {
            ++valueless_epochs;
            if (valueless_epochs == valueless_epoch_number) {
                if (report) {
                    cout << "Max valueless epoch number reached\n\n";
                }
                break;
            }
        } else {
            last_value = curr_value;
            valueless_epochs = 0;
        }
    }

    if (report && valueless_epoch_number == 0 || valueless_epochs != valueless_epoch_number) {
        cout << "Max valueless epoch number reached\n\n";
    }

    vector<Point> path;
    for (size_t i : population[0].gene) {
        path.push_back(pts[i]);
    }
    return path;
}