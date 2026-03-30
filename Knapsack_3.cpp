#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct Item {
    int w, v;
};

struct Ind {
    std::vector<bool> genes; 
    int fit;             
    int weight;             
};

int calc_fit(const Ind &ind, const std::vector<Item> &items, int W) {
    int total_w = 0;
    int total_v = 0;
    for (int i = 0; i < items.size(); i++) {
        if (ind.genes[i]) {
            total_w += items[i].w;
            if (total_w > W) {
                return 0; 
            }
            total_v += items[i].v;
        }
    }
    return total_v;
}

Ind random_Ind(int N) {
    Ind ind;
    ind.genes.resize(N);
    for (int i = 0; i < N; i++){
        ind.genes[i] = rand() % 2;
    }
    return ind;
}

Ind cross(const Ind &a, const Ind &b) {
    Ind child;
    int N = a.genes.size();
    child.genes.resize(N);
    int point = rand() % N;
    for (int i = 0; i < N; i++) {
        if (i < point){
            child.genes[i] = a.genes[i];
        }else{
            child.genes[i] = b.genes[i];
        }
    }
    return child;
}

void mutate(Ind &ind, double mutation_rate) {
    for (size_t i = 0; i < ind.genes.size(); i++) {
        if ((rand() / double(RAND_MAX)) < mutation_rate) {
            ind.genes[i] = !ind.genes[i];
        }
    }
}

int main() {
    int N, W;
    std::cin >> N >> W;

    std::vector<Item> items(N);
    for (int i = 0; i < N; i++) {
        std::cin >> items[i].v >> items[i].w;
    }

    const int population_size = 50;
    const int generations = 1000;
    const double mutation_rate = 0.05;

    std::vector<Ind> pplt;
    for (int i = 0; i < population_size; i++) {
        Ind ind = random_Ind(N);
        ind.fit = calc_fit(ind, items, W);
        pplt.push_back(ind);
    }

    int best_val = 0;
    std::vector<bool> best_sol;

    for (int gen = 0; gen < generations; gen++) {
    
        std::sort(pplt.begin(), pplt.end(), [](const Ind &a, const Ind &b) {return a.fit > b.fit;});

        if (pplt[0].fit > best_val) {
            best_val = pplt[0].fit;
            best_sol = pplt[0].genes;
        }

        std::vector<Ind> new_pplt;

        int elite_count = population_size / 5;
        for (int i = 0; i < elite_count; i++){
            new_pplt.push_back(pplt[i]);
        }

        while (new_pplt.size() < population_size) {
            int idx1 = rand() % (population_size / 2);
            int idx2 = rand() % (population_size / 2);
            Ind parent1 = pplt[idx1];
            Ind parent2 = pplt[idx2];

            Ind child = cross(parent1, parent2);
            mutate(child, mutation_rate);
            child.fit = calc_fit(child, items, W);
            new_pplt.push_back(child);
        }

        pplt = new_pplt;
    }

    int total_w = 0;
    for (int i = 0; i < N; i++) {
        if (best_sol[i]) {
            total_w += items[i].w;
        }
    }
    std::cout << total_w << "\n";

    for (int i = 0; i < N; i++){
        std::cout << best_sol[i] << ' ';
    }
    std::cout << "\n";

    return 0;
}