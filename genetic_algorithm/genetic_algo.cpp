#include "genetic_algo.hpp"
#include "population.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>


std::vector<size_t> GeneticAlgo::solve(const Data* data, size_t population_size, size_t epoch_number,
        size_t valueless_epoch_number, size_t preserve_best, size_t preserve_worst, size_t remove_duplicates,
        double cross_percent, double mutate_percent, bool report) const {

    if (population_size == 0) {
        throw std::invalid_argument("Wrong population size");
    }
    if (epoch_number == 0) {
        throw std::invalid_argument("Wrong epoch number");
    }
    if (preserve_best + preserve_worst > population_size) {
        throw std::invalid_argument("Wrong preserve_best & preserve_worst ratio");
    }
    if (cross_percent < 0) {
        throw std::invalid_argument("Wrong cross percent");
    }
    if (mutate_percent < 0) {
        throw std::invalid_argument("Wrong mutate percent");
    }

    Population population(population_size, data);
    population.fill();

    double last_fitness_value = 0;
    size_t valueless_epochs = 0;
    for (size_t i = 0; i < epoch_number; ++i) {
        if (report) std::cout << "==================== Iteration " << i + 1 << " ====================\n";
        
        if (report) std::cout << "Selecting...\n";
        population.update_chance();
        population.select(preserve_best, preserve_worst);
        if (report) std::cout << "Population: " << population.size() << std::endl;

        if ((i + 1) % remove_duplicates == 0) {
            if (report) std::cout << "Removing duplicates...\n";
            population.remove_duplicates();
            if (report) std::cout << "Population: " << population.size() << std::endl;
        }

        if ((i + 1) % remove_duplicates == 0) {
            if (report) std::cout << "Filling...\n";
            population.fill();
        }

        if (report) std::cout << "Crossing...\n";
        population.update_chance();
        population.cross(cross_percent);
        if (report) std::cout << "Population: " << population.size() << std::endl;

        if (report) std::cout << "Mutating...\n";
        population.update_chance();
        population.mutate(mutate_percent);
        if (report) std::cout << "Population: " << population.size() << std::endl;

        double curr_fitness_value = population.best_value();
        if (report) std::cout << "Current best value: " << curr_fitness_value << "\n\n";
        if (valueless_epoch_number == 0) {
            continue;
        }
        if (std::fabs(last_fitness_value - curr_fitness_value) < 1e-8) {
            ++valueless_epochs;
            if (valueless_epochs == valueless_epoch_number) {
                if (report) {
                    std::cout << "Max valueless epoch number reached\n\n";
                }
                break;
            }
        } else {
            last_fitness_value = curr_fitness_value;
            valueless_epochs = 0;
        }
    }

    if ((report && valueless_epoch_number == 0) || (valueless_epochs != valueless_epoch_number)) {
        std::cout << "Max epoch number reached\n\n";
    }

    return population.best_gene();
}
