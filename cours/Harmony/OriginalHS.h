//
// Created by kelvin on 09/01/24.
//

#ifndef HARMONY_ORIGINALHS_H
#define HARMONY_ORIGINALHS_H
#include <vector>
#include <random>

class Agent {
public:
    std::vector<double> solution;
    double target;
    double fitness;
};

class Problem {
public:
    int n_dims;
    std::vector<double> lb;
    std::vector<double> ub;
};

class OriginalHS {
    public:
        OriginalHS(): epoch{10000}, pop_size{100}, c_r{0.15}, pa_r{0.5} {};
        OriginalHS( int epoch, int pop_size, float c_r, float pa_r): epoch{epoch}, pop_size{pop_size}, c_r{c_r}, pa_r{pa_r} {};
        void evolve(int epoch);

    private:
        std::vector<Agent> pop;
        Problem problem;
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution;
        int epoch, pop_size;
        float c_r, pa_r;
        double dyn_fw;
        double fw_damp;

        void update_target_for_population(std::vector<Agent> pop_new);
        std::vector<Agent>  get_sorted_and_trimmed_population(std::vector<Agent> pop, std::vector<Agent> pop_new, int pop_size);
        std::vector<Agent>  get_sorted_population(const std::vector<Agent>& pop, const std::string& minmax);
        bool compare_agents(const Agent& a, const Agent& b, const std::string& minmax);
};




#endif //HARMONY_ORIGINALHS_H
