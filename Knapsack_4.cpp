#include <iostream>
#include <vector>
#include <algorithm>

struct Item {
    int v; 
    int w; 
    int id; 
};

int main() {
    int N, W;
    if (!(std::cin >> N >> W)) return 0;

    std::vector<Item> items(N);
    for (int i = 0; i < N; i++) {
        std::cin >> items[i].v >> items[i].w;
        items[i].id = i;
    }

    
    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return (double)a.v / a.w > (double)b.v / b.w;
    });

    std::vector<bool> sol(N, false);
    int total_w = 0;
    int total_v = 0;

    for (int i = 0; i < N; i++) {
        if (total_w + items[i].w <= W) {
            total_w += items[i].w;
            total_v += items[i].v;
            sol[items[i].id] = true; 
        }
    }

    std::cout << total_w << '\n';
    for (int i = 0; i < N; i++) {
        std::cout << sol[i] <<  " ";
    }
    std::cout << std::endl;

    return 0;
}
