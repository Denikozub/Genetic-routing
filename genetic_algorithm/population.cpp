#include "population.hpp"
#include <algorithm>
#include <stdexcept>
#include <random>


void Population::add_gene(const Gene& gene) {
    population.insert(std::upper_bound(population.begin(), population.end(), gene), gene);
}


Population::Population(size_t set_size, const Data* set_data) :
        data(set_data), max_size(set_size), range(set_data->get_range()) {
    if (range == 0) {
        throw std::logic_error("Range cannot be zero");
    }
}


size_t Population::size() const {
    return population.size();
}


void Population::fill() {
    size_t curr_size = population.size();
    if (curr_size >= max_size) {
        return;
    }
    for (size_t i = 0; i < max_size - curr_size; ++i) {
        Gene gene(data);
        gene.init(range);
        add_gene(gene);
    }
}


void Population::update_chance() {
    double average = 0;
    for (const auto& g : population) {
        average += g.get_fitness_value();
    }
    average /= population.size();
    for (auto& g : population) {
        g.update_chance(average);
    }
}


void Population::remove_duplicates() {
    population.erase(std::unique(population.begin(), population.end()), population.end());
}


void Population::cross(double cross_percent) {
    if (cross_percent < 0) {
        throw std::invalid_argument("Wrong cross percent");
    }
    std::random_device r;
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size * cross_percent / 2; ++i) {
        size_t elite = population_size * cross_percent / 8;
        Gene parent1(nullptr), parent2(nullptr);
        size_t parent1_index, parent2_index;
        do {
            parent1_index = i <= elite ? i : r() % population_size;
            parent1 = population[parent1_index];
        } while (!parent1.selected());
        do {
            do {
                parent2_index = r() % population_size;
            } while (parent2_index == parent1_index);
            parent2 = population[parent2_index];
        } while (!parent2.selected());

        if (parent1.size() <= 1 && parent2.size() <= 1) {
            continue;
        }
        const auto& children = parent1.cross(parent2);
        add_gene(children.first);
        add_gene(children.second);
    }
}


void Population::mutate(double mutate_percent) {
    if (mutate_percent < 0) {
        throw std::invalid_argument("Wrong mutate percent");
    }
    std::random_device r;
    size_t population_size = population.size();
    for (size_t i = 0; i < population_size * mutate_percent; ++i) {
        Gene gene(nullptr);
        do {
            gene = i <= population_size * mutate_percent / 4 ? population[i] : population[r() % population_size];
        } while (!gene.selected());
        if (gene.size() == 0) {
            continue;
        }
        add_gene(gene.mutate(range));
    }
}


void Population::select(size_t preserve_best, size_t preserve_worst) {
    if (preserve_best + preserve_worst > max_size) {
        throw std::invalid_argument("Wrong preserve_best & preserve_worst ratio");
    }
    size_t current_size = population.size();
    if (current_size <= max_size) {
        return;
    }
    size_t killed = 0;
    while (killed < current_size - max_size) {
        for (auto it = population.end() - preserve_worst - 1; it != population.begin() + preserve_best - 1;) {
            if ((*it).survived()) {
                --it;
                continue;
            }
            it = population.erase(it);
            --it;
            ++killed;
            if (killed == current_size - max_size) {
                return;
            }
        }
    }
}


double Population::best_value() const {
    return population[0].get_fitness_value();
}


const std::vector<size_t>& Population::best_gene() const {
    return population[0].get_gene();
}


std::ostream& operator<< (std::ostream& out, const Population& population) {
    for (const Gene& gene : population.population) {
        out << gene << " ";
    }
    return out;
}