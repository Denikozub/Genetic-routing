#include "genetic_algo.hpp"
#include <iostream>
#include <stdexcept>
#include "population.hpp"


// template <typename T>
std::vector<T> GeneticAlgo::find_path(const Fitness& fitness, size_t population_size,
        size_t range, size_t epoch_number, size_t valueless_epoch_number, size_t preserve_best,
        size_t preserve_worst, int cross_mode, int mutate_mode, int select_mode,
        double cross_percent, double mutate_percent, bool report) const {

    if (population_size <= 0) {
        throw std::invalid_argument("Wrong population size");
    }
    if (epoch_number <= 0) {
        throw std::invalid_argument("Wrong epoch number");
    }
    if (valueless_epoch_number < 0) {
        throw std::invalid_argument("Wrong valueless epoch number");
    }
    if (preserve_best <= 0 || preserve_best > population_size) {
        throw std::invalid_argument("Wrong preserve_best number");
    }
    if (preserve_worst < 0 || preserve_worst > population_size) {
        throw std::invalid_argument("Wrong preserve_worst number");
    }
    if (preserve_best + preserve_worst > population_size) {
        throw std::invalid_argument("Wrong preserve_best & preserve_worst ratio");
    }
    if (cross_percent < 0) {
        throw std::invalid_argument("Wrong cross percent");
    }
    if (mutate_percent <= 0) {
        throw std::invalid_argument("Wrong mutate percent");
    }
    if (cross_mode < 0 || cross_mode > 1) {
        throw std::invalid_argument("Wrong cross mode percent");
    }
    if (mutate_mode < 0 || mutate_mode > 1) {
        throw std::invalid_argument("Wrong mutate mode percent");
    }
    if (select_mode < 0 || select_mode > 1) {
        throw std::invalid_argument("Wrong select mode percent");
    }

    Population population(population_size, range, fitness);
    population.init_population();

    double last_value = 0;
    size_t valueless_epochs = 0;
    for (size_t i = 0; i < epoch_number; ++i) {
        if (report) std::cout << "==================== Iteration " << i + 1 << " ====================\n";
        
        if (report) std::cout << "Crossing...\n";
        if (cross_mode == 0) {
            population.update_population_chance();
            population.cross_population_chance();
        }
        else {
            population.cross_population_random(cross_percent);
        }
        if (report) std::cout << "Population: " << population.size() << std::endl;

        if (report) std::cout << "Crossing...\n";
        if (mutate_mode == 0) {
            population.update_population_chance();
            population.mutate_population_chance();
        }
        else {
            population.mutate_population_random(mutate_percent);
        }
        if (report) std::cout << "Population: " << population.size() << std::endl;

        if (report) std::cout << "Selecting...\n";
        if (mutate_mode == 0) {
            population.update_population_chance();
            population.select_population_chance(preserve_best, preserve_worst);
        }
        else {
            population.select_population_best(preserve_best, preserve_worst);
        }
        if (report) std::cout << "Population: " << population.size() << std::endl;

        double curr_value = population[0].get_value();
        if (report) std::cout << "Current best value: " << curr_value << "\n\n";
        if (valueless_epoch_number == 0) {
            continue;
        }
        if (last_value == curr_value) {
            ++valueless_epochs;
            if (valueless_epochs == valueless_epoch_number) {
                if (report) {
                    std::cout << "Max valueless epoch number reached\n\n";
                }
                break;
            }
        } else {
            last_value = curr_value;
            valueless_epochs = 0;
        }
    }

    if (report && valueless_epoch_number == 0 || valueless_epochs != valueless_epoch_number) {
        std::cout << "Max epoch number reached\n\n";
    }

    return population[0].path(pts);
}