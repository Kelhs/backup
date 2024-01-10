//
// Created by kelvin on 09/01/24.
//

#include "OriginalHS.h"
#include <vector>
#include <algorithm>
#include <utility>

//pop_new = []
//for idx in range(0, self.pop_size):
//pos_new = self.generator.uniform(self.problem.lb, self.problem.ub)
//for jdx in range(self.problem.n_dims):
//# Use Harmony Memory
//if self.generator.uniform() <= self.c_r:
//random_index = self.generator.integers(0, self.pop_size)
//pos_new[jdx] = self.pop[random_index].solution[jdx]
//# Pitch Adjustment
//if self.generator.uniform() <= self.pa_r:
//delta = self.dyn_fw * self.generator.normal(self.problem.lb, self.problem.ub)  # Gaussian(Normal)
//pos_new[jdx] = pos_new[jdx] + delta[jdx]
//pos_new = self.correct_solution(pos_new)
//agent = self.generate_empty_agent(pos_new)
//pop_new.append(agent)
//if self.mode not in self.AVAILABLE_MODES:
//pop_new[-1].target = self.get_target(pos_new)
//pop_new = self.update_target_for_population(pop_new)
//# Update Damp Fret Width
//self.dyn_fw = self.dyn_fw * self.fw_damp
//# Merge Harmony Memory and New Harmonies, Then sort them, Then truncate extra harmonies
//self.pop = self.get_sorted_and_trimmed_population(self.pop + pop_new, self.pop_size, minmax=self.problem.minmax)
bool OriginalHS::compare_agents(const Agent& a, const Agent& b, const std::string& minmax) {
    if (minmax == "max") {
        return a.fitness > b.fitness;  // Pour un tri décroissant
    } else {
        return a.fitness < b.fitness;  // Pour un tri croissant
    }
}

std::vector<Agent> OriginalHS::get_sorted_population(const std::vector<Agent>& pop, const std::string& minmax){
    std::vector<int> indices(pop.size());
    std::iota(indices.begin(), indices.end(), 0);  // Remplir indices avec 0, 1, 2, ...

    // Trier les indices en fonction de la fitness des agents
    std::sort(indices.begin(), indices.end(), [&](int i, int j) {
        return compare_agents(pop[i], pop[j], minmax);
    });

    // Créer une nouvelle population triée
    std::vector<Agent> sortedPop;
    for (int idx : indices) {
        sortedPop.push_back(pop[idx]);
    }
    return sortedPop;  // Retourne la population triée
}

std::vector<Agent> OriginalHS::get_sorted_and_trimmed_population(std::vector<Agent> pop, std::vector<Agent> pop_new, int pop_size){
    pop.insert(pop.end(), pop_new.begin(), pop_new.end());
    get_sorted_population(pop, "min");
    return get_sorted_population(pop, "min");

}

void OriginalHS::evolve(int epoch) {
    std::vector<Agent> pop_new;
    for (int idx = 0; idx < pop_size; ++idx) {
        Agent agent;
        for (int jdx = 0; jdx < problem.n_dims; ++jdx) {
            double random_value = distribution(generator);
            //Use Harmony Memory
            if (random_value <= c_r) {
                int random_index = generator() % pop_size;
                agent.solution[jdx] = pop[random_index].solution[jdx];
            }
            // Pitch Adjustment
            if (random_value <= pa_r) {
                double delta = dyn_fw * distribution(generator); // Gaussian(Normal)
                agent.solution[jdx] += delta;
            }
        }
        pop_new.push_back(agent);
    }
    //pop_new = update_target_for_population(pop_new);
    //Update Damp Fret Width
    dyn_fw *= fw_damp;
    //Merge Harmony Memory and New Harmonies, Then sort them, Then truncate extra harmonies
    pop = get_sorted_and_trimmed_population(pop, pop_new, pop_size);
}

