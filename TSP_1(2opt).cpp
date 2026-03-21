#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

double route_length(const std::vector<int>& route, const std::vector<double>& x, const std::vector<double>& y) {
    double lenght = 0.0;
    int n = route.size();
    for (int i=0; i < n-1; ++i) {
        lenght += dist(x[route[i]], y[route[i]], x[route[i+1]], y[route[i+1]]);
    }
    lenght += dist(x[route[n-1]], y[route[n-1]], x[route[0]], y[route[0]]);
    return lenght;
}

void two_opt(std::vector<int>& route, const std::vector<double>& x, const std::vector<double>& y) {
    bool improved = true;
    int n = route.size();

    while (improved) {
        improved = false;
        for (int i=1; i<n-1; ++i) {           
            for (int k=i+1; k<n; ++k) {
                std::vector<int> tmp_r = route;
                std::reverse(tmp_r.begin() + i, tmp_r.begin() + k + 1);

                if (route_length(tmp_r, x, y) < route_length(route, x, y)) {
                    route = tmp_r;
                    improved = true;
                }
            }
        }
    }
}

int main() {
    int N; 
    std::cin >> N;

    std::vector<double> x(N);
    std::vector<double> y(N);

    for (int i=0; i<N; ++i) {
        std::cin >> x[i] >> y[i];
    }

    std::vector<int> route(N);
    for (int i=0; i<N; ++i) {
        route[i] = i;
    }

    double init_length = route_length(route, x, y);

    two_opt(route, x, y);

    double fin = route_length(route, x, y);
    std::cout << fin << std::endl;

    for (int v : route) {
        std::cout << v << " ";
    }
    std::cout << route[0] << std::endl;

    return 0;
}