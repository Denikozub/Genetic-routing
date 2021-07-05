#include "genetic_algo.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <stdexcept>
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
        g.update_value(pts, obstacles, start, end);
    }
}

void GeneticAlgo::update_population_chance(vector<Gene>& population) const {
    double average = 0;
    for (auto& g : population) {
        average += g.get_value();
    }
    average /= population.size();
    for (auto& g : population) {
        g.update_chance(average);
    }
}

void GeneticAlgo::sort_population(vector<Gene>& population) const {
    sort(population.begin(), population.end(),
        [](const Gene& gene1, const Gene& gene2) { return gene1.get_value() < gene2.get_value(); });
}

void GeneticAlgo::cross_population_chance(vector<Gene>& population, double cross_percent) const {
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size; ++i) {
        Gene parent1 = population[i];
        if (!parent1.selected()) {
            continue;
        }
        for (size_t j = i + 1; j < population_size; ++j) {
            Gene parent2 = population[j];
            if (parent1.size() <= 1 && parent2.size() <= 1) {
                continue;
            }
            if (!parent2.selected()) {
                continue;
            }
            auto children = one_point_cross(parent1, parent2);
            children.first.update_value(pts, obstacles, start, end);
            children.second.update_value(pts, obstacles, start, end);
            population.push_back(children.first);
            population.push_back(children.second);
            break;
        }
    }
}

void GeneticAlgo::cross_population_random(vector<Gene>& population, double cross_percent) const {
    random_device r;
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size * 0.5 / 2; ++i) {
        Gene parent1 = population[r() % population_size];
        Gene parent2 = population[r() % population_size];
        if (parent1.size() <= 1 && parent2.size() <= 1) {
            continue;
        }
        auto children = one_point_cross(parent1, parent2);
        children.first.update_value(pts, obstacles, start, end);
        children.second.update_value(pts, obstacles, start, end);
        population.push_back(children.first);
        population.push_back(children.second);
    }
}

void GeneticAlgo::mutate_population_chance(vector<Gene>& population, double mutate_percent) const {
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size; ++i) {
        Gene src = population[i];
        if (src.size() == 0) {
            continue;
        }
        if (!src.selected()) {
            continue;
        }
        auto mutant = one_point_mutate(src, pts.size());
        mutant.update_value(pts, obstacles, start, end);
        population.push_back(mutant);
    }
}

void GeneticAlgo::mutate_population_random(vector<Gene>& population, double mutate_percent) const {
    random_device r;
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size * 0.5; ++i) {
        Gene src = population[r() % population_size];
        if (src.size() == 0) {
            continue;
        }
        auto mutant = one_point_mutate(src, pts.size());
        mutant.update_value(pts, obstacles, start, end);
        population.push_back(mutant);
    }
}

void GeneticAlgo::select_population_chance(vector<Gene>& population,
        size_t population_size, size_t preserve_best, size_t preserve_worst) const {
    size_t current_size = population.size();
    if (current_size == population_size) {
        return;
    }
    size_t killed = 0;
    while (killed < current_size - population_size) {
        for (auto it = population.begin() + preserve_best; it != population.end() - preserve_worst;) {
            if ((*it).survived()) {
                ++it;
                continue;
            }
            it = population.erase(it);
            ++killed;
            if (killed == current_size - population_size) {
                return;
            }
        }
    }
}

void GeneticAlgo::select_population_best(vector<Gene>& population,
        size_t population_size, size_t preserve_best, size_t preserve_worst) const {
    vector<Gene> best = { population.begin(), population.begin() + population_size - preserve_worst };
    best.insert(best.end(), population.end() - preserve_worst, population.end());
    population = best;
}


vector<Point> GeneticAlgo::find_path(size_t population_size, size_t epoch_number,
        size_t valueless_epoch_number, size_t preserve_best, size_t preserve_worst,
        double cross_percent, double mutate_percent, int cross_mode, int mutate_mode,
        int select_mode, bool report) const {

    if (population_size <= 0) {
        throw invalid_argument("Wrong population size");
    }
    if (epoch_number <= 0) {
        throw invalid_argument("Wrong epoch number");
    }
    if (valueless_epoch_number < 0) {
        throw invalid_argument("Wrong valueless epoch number");
    }
    if (preserve_best <= 0 || preserve_best > population_size) {
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
    if (cross_mode < 0 || cross_mode > 1) {
        throw invalid_argument("Wrong cross mode percent");
    }
    if (mutate_mode < 0 || mutate_mode > 1) {
        throw invalid_argument("Wrong mutate mode percent");
    }
    if (select_mode < 0 || select_mode > 1) {
        throw invalid_argument("Wrong select mode percent");
    }

    vector<Gene> population(population_size);
    init_population(population);

    double last_value = 0;
    size_t valueless_epochs = 0;
    for (size_t i = 0; i < epoch_number; ++i) {
        if (report) cout << "==================== Iteration " << i + 1 << " ====================\n";
        
        if (report) cout << "Crossing...\n";
        if (cross_mode == 0) {
            update_population_chance(population);
            cross_population_chance(population, cross_percent);
        }
        else {
            cross_population_random(population, cross_percent);
        }
        if (report) cout << "Population: " << population.size() << endl;

        if (report) cout << "Crossing...\n";
        if (mutate_mode == 0) {
            update_population_chance(population);
            mutate_population_chance(population, mutate_percent);
        }
        else {
            mutate_population_random(population, mutate_percent);
        }
        if (report) cout << "Population: " << population.size() << endl;

        if (report) cout << "Selecting...\n";
        sort_population(population);
        if (mutate_mode == 0) {
            update_population_chance(population);
            select_population_chance(population, population_size, preserve_best, preserve_worst);
        }
        else {
            select_population_best(population, population_size, preserve_best, preserve_worst);
        }
        if (report) cout << "Population: " << population.size() << endl;

        double curr_value = population[0].get_value();
        if (report) cout << "Current best value: " << curr_value << "\n\n";
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
        cout << "Max epoch number reached\n\n";
    }

    return population[0].path(pts);
}