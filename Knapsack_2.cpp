#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Item {
    int w, v;
    double rt;
};

typedef struct Node {
    int level;
    int profit;
    int weight;
    double bound;
    std::vector<bool> taken;

    bool operator<(const Node &other) const {
        return bound < other.bound; 
    }
} node;

double calc_bound(const node &node, int N, int W, const std::vector<Item> &items) {
    if (node.weight >= W){
        return 0;
    }
    double bound = node.profit;
    int tot_w = node.weight;
    int idx = node.level + 1;

    while (idx < N && tot_w + items[idx].w <= W) {
        tot_w += items[idx].w;
        bound += items[idx].v;
        idx++;
    }
    if (idx < N){
        bound += (W - tot_w) * items[idx].rt;
    }
    return bound;
}

int main() {
    int N, W;
    std::cin >> N >> W;

    std::vector<Item> items(N);

    for (int i = 0; i < N; i++) {
        std::cin >> items[i].v >> items[i].w;
        items[i].rt = (double)items[i].v / items[i].w;
    }

    std::sort(items.begin(), items.end(), [](const Item &a, const Item &b) {return a.rt > b.rt;});

    std::priority_queue<node> pq; 

    node root;
    root.level = -1;
    root.profit = 0;
    root.weight = 0;
    root.taken = std::vector<bool>(N, false);
    root.bound = calc_bound(root, N, W, items);
    pq.push(root);

    int max_profit = 0;
    std::vector<bool> best_ver(N, false);

    while (!pq.empty()) {
        Node node = pq.top(); 
        pq.pop();
        if (node.bound <= max_profit) continue;
        if (node.level == N - 1) continue; 

        Node left = node;
        left.level = node.level + 1;
        left.weight += items[left.level].w;
        left.profit += items[left.level].v;
        left.taken[left.level] = true;

        if (left.weight <= W && left.profit > max_profit) {
            max_profit = left.profit;
            best_ver = left.taken;
        }
        left.bound = calc_bound(left, N, W, items);
        if (left.bound > max_profit){
            pq.push(left);
        }

        Node right = node;
        right.level = node.level + 1;
        right.taken[right.level] = false;
        right.bound = calc_bound(right, N, W, items);
        if (right.bound > max_profit){
            pq.push(right);
        }
    }

    int fin_w = 0;
    std::vector<int> res(N);
    for (int i = 0; i < N; ++i) {
        if (best_ver[i]){
            fin_w += items[i].w;
        }
        res[i] = best_ver[i] ? 1 : 0;
    }

    std::cout << fin_w << '\n';
    for (int i = 0; i < N; ++i){ 
        std::cout << res[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}