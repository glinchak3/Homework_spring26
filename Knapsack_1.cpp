#include <iostream>
#include <vector>
#include <cstdlib>

typedef struct Item{
    int w;
    int v;
} Item;

int main() {
    int N;
    int W;

    std::cin >> N;
    std::cin >> W;

    std::vector<Item> items(N);

    for(int i=0; i<N; i++) {
        std::cin >> items[i].v;
        std::cin >> items[i].w;
    }

    std::vector<bool> curr(N, false);
    int total_w = 0; 
    int total_v = 0;

    for(int i=0; i<N; i++) {
        if(total_w + items[i].w <= W) {
            curr[i] = true;
            total_w += items[i].w;
            total_v += items[i].v;
        }
    }

    int P = 1000;
    int fin_v = total_v;
    std::vector<bool> sol = curr;

    for(int i=0; i<P; i++) {

        std::vector<bool> tmp = curr;
        int index = rand() % N;
        tmp[index] = !tmp[index]; 

        int tmp_w = 0; 
        int tmp_v = 0;
        for(int j=0; j<N; j++) {
            if(tmp[j]) {
                tmp_w += items[j].w;
                tmp_v += items[j].v;
            }
        }

        if(tmp_w <= W && tmp_v > fin_v) {
            fin_v = tmp_v;
            sol = tmp;
            curr = tmp;
        }
    }

    int fin_w = 0;
    for(int i=0; i<N; i++) {
        if(sol[i]){
            fin_w += items[i].w;
        } 
    }

    std::cout << fin_w << '\n';
    for (int i=0; i<N; i++) {
        std::cout << sol[i] << ' ';
    }

    return 0;
}