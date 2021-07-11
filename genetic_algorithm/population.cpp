#include "population.hpp"
#include <algorithm>
#include <random>


void Population::add_gene(const Gene& gene) {
    population.insert(std::upper_bound(population.begin(), population.end(), gene), gene);
}


Population::Population(size_t set_size, size_t set_range, const Fitness& fitness) :
        max_size(set_size), range(set_range), population(max_size, fitness) {}


size_t Population::size() {
    return population.size();
}


void Population::init_population() {
    for (auto& g : population) {
        g.init(range);
    }
    std::sort(population.begin(), population.end());
}


void Population::update_population_chance() {
    double average = 0;
    for (const auto& g : population) {
        average += g.get_fitness_value();
    }
    average /= population.size();
    for (auto& g : population) {
        g.update_chance(average);
    }
}


void Population::cross_population_chance() {
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
            const auto& children = cross(parent1, parent2);
            add_gene(children.first);
            add_gene(children.second);
            break;
        }
    }
}


void Population::cross_population_random(double cross_percent) {
    std::random_device r;
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size * cross_percent / 2; ++i) {
        Gene parent1 = population[r() % population_size];
        Gene parent2 = population[r() % population_size];
        if (parent1.size() <= 1 && parent2.size() <= 1) {
            continue;
        }
        const auto& children = cross(parent1, parent2);
        add_gene(children.first);
        add_gene(children.second);
    }
}


void Population::mutate_population_chance() {
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size; ++i) {
        Gene src = population[i];
        if (src.size() == 0) {
            continue;
        }
        if (!src.selected()) {
            continue;
        }
        const auto& mutants = mutate(src);
        for (const auto& mutant : mutants) {
            add_gene(mutant);
        }
    }
}


void Population::mutate_population_random(double mutate_percent) {
    std::random_device r;
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size * mutate_percent; ++i) {
        Gene src = population[r() % population_size];
        if (src.size() == 0) {
            continue;
        }
        const auto& mutants = mutate(src);
        for (const auto& mutant : mutants) {
            add_gene(mutant);
        }
    }
}


void Population::select_population_chance(size_t preserve_best, size_t preserve_worst) {
    size_t current_size = population.size();
    if (current_size == max_size) {
        return;
    }
    size_t killed = 0;
    while (killed < current_size - max_size) {
        for (auto it = population.begin() + preserve_best; it != population.end() - preserve_worst;) {
            if ((*it).survived()) {
                ++it;
                continue;
            }
            it = population.erase(it);
            ++killed;
            if (killed == current_size - max_size) {
                return;
            }
        }
    }
}


void Population::select_population_best(size_t preserve_best, size_t preserve_worst) {
    std::vector<Gene> best = { population.begin(), population.begin() + max_size - preserve_worst };
    best.insert(best.end(), population.end() - preserve_worst, population.end());
    population = best;
}


template <typename T> std::vector<T> Population::best_values() {
    return population[0].values(pts);
}