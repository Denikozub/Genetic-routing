#include "gene.hpp"
#include <random>
#include <algorithm>
#include <stdexcept>
#include <unordered_set>


void Gene::remove_duplicates() {
    std::unordered_set<size_t> s(gene.begin(), gene.end());
    gene.assign(s.begin(), s.end());
}


void Gene::inverse(size_t i, size_t j) {
    if (i >= j) {
        throw std::invalid_argument("Wrong index order");
    }
    for (size_t k = 0; k < (j - i + 1) / 2; ++k)
        std::swap(gene[i + k], gene[j - k]);
    fitness_value = evaluator.eval(*this);
}


void Gene::insert(size_t i, size_t j) {
    if (i >= j) {
        throw std::invalid_argument("Wrong index order");
    }
    gene.insert(gene.begin() + i, gene.begin() + j, gene.begin() + j + 1);
    gene.erase(gene.begin() + j + 1);
    fitness_value = evaluator.eval(*this);
}


void Gene::swap(size_t i, size_t j) {
    if (i >= j) {
        throw std::invalid_argument("Wrong index order");
    }
    ::std::swap(gene[i], gene[j]);
    fitness_value = evaluator.eval(*this);
}


Gene::Gene(const Fitness& src) : evaluator(src), len(0), fitness_value(0), chance(0) {}


double Gene::size() const {
    return len;
}


void Gene::init(size_t range) {
    std::random_device r;
    len = r() % range;
    gene = std::vector<size_t>(len);
    std::generate(gene.begin(), gene.end(), [&] {return r() % range; });
    remove_duplicates();
    len = gene.size();
    fitness_value = evaluator.eval(*this);
}


double Gene::get_fitness_value() const {
    return fitness_value;
}


void Gene::update_chance(double average) {
    if (fitness_value <= 0) {
        throw std::logic_error("Update values first");
    }
    if (average <= 0) {
        throw std::invalid_argument("Incorrect average fitness_value");
    }
    chance = average / fitness_value;
}


bool Gene::selected() {
    std::random_device r;
    std::uniform_real_distribution<> uniform_zero_to_one(0.0, 1.0);
    if (chance >= 1) {
        chance--;
        return true;
    }
    return uniform_zero_to_one(r) <= chance;
}


bool Gene::survived() const {
    std::random_device r;
    std::uniform_real_distribution<> uniform_zero_to_one(0.0, 1.0);
    double survive_chance = chance / (chance + 1);
    return uniform_zero_to_one(r) <= survive_chance;
}


std::pair<Gene, Gene> cross(const Gene& parent1, const Gene& parent2) {
    if (parent1.gene.size() <= 1 && parent2.gene.size() <= 1) {
        throw std::invalid_argument("At least one of the parents should have 2 or more points");
    }
    std::random_device r;
    size_t parent1_cross = parent1.len > 1 ? r() % (parent1.len - 1) + 1 : 0;
    size_t parent2_cross = parent2.len > 1 ? r() % (parent2.len - 1) + 1 : 0;
    Gene child1(parent1.evaluator), child2(parent2.evaluator);
    child1.gene = { parent1.gene.begin(), parent1.gene.begin() + parent1_cross };
    child2.gene = { parent2.gene.begin(), parent2.gene.begin() + parent2_cross };
    child1.gene.insert(child1.gene.end(), parent2.gene.begin() + parent2_cross, parent2.gene.end());
    child2.gene.insert(child2.gene.end(), parent1.gene.begin() + parent1_cross, parent1.gene.end());
    child1.remove_duplicates();
    child1.len = child1.gene.size();
    child1.evaluator.eval(child1);
    child2.remove_duplicates();
    child2.len = child2.gene.size();
    child2.evaluator.eval(child2);
    return { child1, child2 };
}


std::vector<Gene> mutate(const Gene& src) {
    if (src.gene.size() == 0) {
        throw std::invalid_argument("Gene cannot be empty");
    }
    Gene mutant1(src), mutant2(src), mutant3(src);
    std::random_device r;
    size_t i = r() % src.len, j = r() % src.len;
    while (i == j) {
        j = r() % src.len;
    }
    if (i > j) {
        ::std::swap(i, j);
    }
    mutant1.inverse(i, j);
    mutant2.insert(i, j);
    mutant3.swap(i, j);
    return { mutant1, mutant2, mutant3 };
}


bool operator>= (const Gene& gene1, const Gene& gene2) {
    return gene1.fitness_value >= gene2.fitness_value;
}


bool operator<= (const Gene& gene1, const Gene& gene2) {
    return gene1.fitness_value <= gene2.fitness_value;
}


bool operator> (const Gene& gene1, const Gene& gene2) {
    return gene1.fitness_value > gene2.fitness_value;
}


bool operator< (const Gene& gene1, const Gene& gene2) {
    return gene1.fitness_value < gene2.fitness_value;
}


const std::vector<size_t>& Gene::get_gene() {
    return gene;
}