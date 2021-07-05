#include "gene.hpp"
#include <random>
#include <algorithm>
#include <exception>
#include <unordered_set>
using std::random_device;
using std::uniform_real_distribution;
using std::generate;
using std::unordered_set;
using std::invalid_argument;
using std::logic_error;

double Gene::size() const {
    return len;
}
double Gene::get_value() const {
    return value;
}

void Gene::init(size_t point_number) {
    random_device r;
    len = r() % point_number;
    gene = vector<size_t>(len);
    generate(gene.begin(), gene.end(), [&] {return r() % point_number; });
    remove_duplicates();
}

void Gene::remove_duplicates() {
    unordered_set<size_t> s(gene.begin(), gene.end());
    gene.assign(s.begin(), s.end());
    len = gene.size();
}

void Gene::update_value(const vector<Point>& pts,
        const vector<pair<Polygon, int>>& obstacles, const Point& start, const Point& end) {
    double path_length = 0;
    Segment segment({ start, end });
    for (size_t i = 0; i < len + 1; i++) {
        if (len > 0 && i == 0) {
            segment = { start, pts[gene[0]] };
        } else if (len > 0 && i == len) {
            segment = { pts[gene[len - 1]], end };
        } else if (len > 0) {
            segment = { pts[gene[i - 1]], pts[gene[i]] };
        }
        double cross_value = segment.len();
        for (const auto& polygon_info : obstacles) {
            if (segment.crosses(polygon_info.first)) {
                cross_value += segment.len() * polygon_info.second;
            }
        }
        path_length += cross_value;
    }
    value = path_length;
}

void Gene::update_chance(double average) {
    if (value <= 0) {
        throw logic_error("Update values first");
    }
    if (average <= 0) {
        throw invalid_argument("Incorrect average value");
    }
    chance = average / value;
}

#include <iostream>
using std::cout;

bool Gene::selected() {
    random_device r;
    uniform_real_distribution<> uniform_zero_to_one(0.0, 1.0);
    if (chance >= 1) {
        chance--;
        return true;
    }
    return uniform_zero_to_one(r) <= chance;
}

bool Gene::survived() const {
    random_device r;
    uniform_real_distribution<> uniform_zero_to_one(0.0, 1.0);
    double survive_chance = chance / (chance + 1);
    return uniform_zero_to_one(r) <= survive_chance;
}

pair<Gene, Gene> one_point_cross(const Gene& parent1, const Gene& parent2) {
    if (parent1.gene.size() <= 1 && parent2.gene.size() <= 1) {
        throw invalid_argument("At least one of the parents should have 2 or more points");
    }
    random_device r;
    size_t parent1_cross = parent1.len > 1 ? r() % (parent1.len - 1) + 1 : 0;
    size_t parent2_cross = parent2.len > 1 ? r() % (parent2.len - 1) + 1 : 0;
    Gene child1, child2;
    child1.gene = { parent1.gene.begin(), parent1.gene.begin() + parent1_cross };
    child2.gene = { parent2.gene.begin(), parent2.gene.begin() + parent2_cross };
    child1.gene.insert(child1.gene.end(), parent2.gene.begin() + parent2_cross, parent2.gene.end());
    child2.gene.insert(child2.gene.end(), parent1.gene.begin() + parent1_cross, parent1.gene.end());
    child1.remove_duplicates();
    child2.remove_duplicates();
    return { child1, child2 };
}

Gene one_point_mutate(const Gene& src, size_t point_number) {
    if (src.gene.size() == 0) {
        throw invalid_argument("Gene cannot be empty");
    }
    random_device r;
    size_t point_mutate = r() % src.len;
    Gene mutant;
    mutant.gene = src.gene;
    mutant.gene[point_mutate] = r() % point_number;
    mutant.remove_duplicates();
    return mutant;
}

vector<Point> Gene::path(const vector<Point>& pts) {
    vector<Point> path;
    for (size_t i : gene) {
        path.push_back(pts[i]);
    }
    return path;
}