#include "gene.hpp"
#include <random>
#include <algorithm>
#include <stdexcept>
#include <unordered_set>


void Gene::remove_duplicates() {
    std::unordered_set<size_t> s(gene.begin(), gene.end());
    gene.assign(s.begin(), s.end());
    len = gene.size();
}


void Gene::inverse(size_t i, size_t j) {
    if (i >= j) {
        throw std::invalid_argument("Wrong index order");
    }
    for (size_t k = 0; k < (j - i + 1) / 2; ++k)
        std::swap(gene[i + k], gene[j - k]);
    fitness_value = data->fitness(gene);
}


void Gene::insert(size_t i, size_t j) {
    if (i >= j) {
        throw std::invalid_argument("Wrong index order");
    }
    gene.insert(gene.begin() + i, gene.begin() + j, gene.begin() + j + 1);
    gene.erase(gene.begin() + j + 1);
    fitness_value = data->fitness(gene);
}


void Gene::swap(size_t i, size_t j) {
    if (i >= j) {
        throw std::invalid_argument("Wrong index order");
    }
    ::std::swap(gene[i], gene[j]);
    fitness_value = data->fitness(gene);
}


void Gene::cut_fill(size_t cut1, size_t cut2, const Gene& parent) {
    gene = { gene.begin(), gene.begin() + cut1 };
    gene.insert(gene.end(), parent.gene.begin() + cut2, parent.gene.end());
    remove_duplicates();
    fitness_value = data->fitness(gene);
}


Gene::Gene(const Data* set_data) : data(set_data), len(0), fitness_value(0), chance(0) {}


size_t Gene::size() const {
    return len;
}


void Gene::init(size_t range) {
    std::random_device r;
    len = r() % range;
    gene = std::vector<size_t>(len);
    std::generate(gene.begin(), gene.end(), [&] {return r() % range; });
    remove_duplicates();
    fitness_value = data->fitness(gene);
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


std::pair<Gene, Gene> cross_one_point(const Gene& parent1, const Gene& parent2) {
    if (parent1.len <= 1 && parent2.len <= 1) {
        throw std::invalid_argument("At least one of the parents should have 2 or more points");
    }
    std::random_device r;
    size_t parent1_cross = parent1.len > 1 ? r() % (parent1.len - 1) + 1 : 0;
    size_t parent2_cross = parent2.len > 1 ? r() % (parent2.len - 1) + 1 : 0;
    Gene child1(parent1), child2(parent2);
    child1.cut_fill(parent1_cross, parent2_cross, parent2);
    child2.cut_fill(parent2_cross, parent1_cross, parent1);
    return { child1, child2 };
}


std::vector<Gene> mutate_triple(const Gene& src) {
    if (src.len < 2) {
        throw std::invalid_argument("Gene cannot be mutated");
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


std::vector<Gene> mutate_one_point(const Gene& src, size_t point_number) {
    if (src.len == 0) {
        throw std::invalid_argument("Gene cannot be empty");
    }
    Gene mutant1(src), mutant2(src), mutant3(src);
    std::random_device r;
    size_t i = r() % src.len;
    mutant1.gene[i] = r() % point_number;
    mutant1.remove_duplicates();
    mutant2.gene.insert(mutant2.gene.begin() + i, r() % point_number);
    mutant2.remove_duplicates();
    mutant3.gene.erase(mutant3.gene.begin() + i);
    mutant3.len = mutant3.gene.size();
    return { mutant1, mutant2, mutant3 };
}


bool operator< (const Gene& gene1, const Gene& gene2) {
    return gene1.fitness_value < gene2.fitness_value;
}


bool operator== (const Gene& gene1, const Gene& gene2) {
    return gene1.gene == gene2.gene;
}


const std::vector<size_t>& Gene::get_gene() const {
    return gene;
}


std::ostream& operator<< (std::ostream& out, const Gene& gene) {
    for (size_t point : gene.gene) {
        out << point << " ";
    }
    out << std::endl;
    return out;
}