#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double dist(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1, dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}

double route_length(const vector<int>& route, const vector<double>& x, const vector<double>& y) {
    double length = 0;
    int n = route.size();
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        length += dist(x[route[i]], y[route[i]], x[route[next]], y[route[next]]);
    }
    return length;
}

double part_dist(int a, int b, const vector<int>& route, const vector<double>& x, const vector<double>& y) {
    return dist(x[route[a]], y[route[a]], x[route[b]], y[route[b]]);
}

void three_opt(vector<int>& route, const vector<double>& x, const vector<double>& y) {
    int n = route.size();
    bool improved = true;

    while (improved) {
        improved = false;
        bool loc = false;

        for (int i = 0; i < n - 5 && !loc; ++i) {
            for (int j = i + 2; j < n - 3 && !loc; ++j) {
                for (int k = j + 2; k < n - (i == 0 ? 1 : 0) && !loc; ++k) {
                    int a = i, b = i + 1;
                    int c = j, d = j + 1;
                    int e = k, f = (k + 1) % n;

                    double old_dist = dist(x[route[a]], y[route[a]], x[route[b]], y[route[b]]) + dist(x[route[c]], y[route[c]], x[route[d]], y[route[d]]) + dist(x[route[e]], y[route[e]], x[route[f]], y[route[f]]);
                    vector<int> tmp = route;
                    reverse(tmp.begin() + b, tmp.begin() + c + 1);
                    double new_dist = dist(x[tmp[a]], y[tmp[a]], x[tmp[c]], y[tmp[c]]) + dist(x[tmp[b]], y[tmp[b]], x[tmp[d]], y[tmp[d]]) + dist(x[tmp[e]], y[tmp[e]], x[tmp[f]], y[tmp[f]]);
                    if (new_dist < old_dist) {
                        route = tmp;
                        improved = true;
                        loc = true;
                        continue;
                    }
                    tmp = route;
                    reverse(tmp.begin() + d, tmp.begin() + e + 1);
                    new_dist = dist(x[tmp[a]], y[tmp[a]], x[tmp[b]], y[tmp[b]]) + dist(x[tmp[c]], y[tmp[c]], x[tmp[e]], y[tmp[e]]) + dist(x[tmp[d]], y[tmp[d]], x[tmp[f]], y[tmp[f]]);
                    if (new_dist < old_dist) {
                        route = tmp;
                        improved = true;
                        loc = true;
                        continue;
                    }

                    tmp = route;
                    reverse(tmp.begin() + b, tmp.begin() + c + 1);
                    reverse(tmp.begin() + d, tmp.begin() + e + 1);
                    new_dist = dist(x[tmp[a]], y[tmp[a]], x[tmp[c]], y[tmp[c]]) + dist(x[tmp[b]], y[tmp[b]], x[tmp[e]], y[tmp[e]]) + dist(x[tmp[d]], y[tmp[d]], x[tmp[f]], y[tmp[f]]);
                    if (new_dist < old_dist) {
                        route = tmp;
                        improved = true;
                        loc = true;
                        continue;
                    }

                    tmp = route;
                    vector<int> part1(route.begin() + b, route.begin() + d + 1);
                    vector<int> part2(route.begin() + d + 1, route.begin() + e + 1);

                    tmp.erase(tmp.begin() + b, tmp.begin() + e + 1);
                    tmp.insert(tmp.begin() + b, part2.begin(), part2.end());
                    tmp.insert(tmp.begin() + b + part2.size(), part1.begin(), part1.end());

                    new_dist = dist(x[tmp[a]], y[tmp[a]], x[tmp[b]], y[tmp[b]]) + dist(x[tmp[b + (int)part2.size() - 1]], y[tmp[b + (int)part2.size() - 1]], x[tmp[b + (int)part2.size()]], y[tmp[b + (int)part2.size()]]) + dist(x[tmp[e]], y[tmp[e]], x[tmp[f]], y[tmp[f]]);
                    if (new_dist < old_dist) {
                        route = tmp;
                        improved = true;
                        loc = true;
                        continue;
                    }
                }
            }
        }
    }
}

int main() {
    int N;
    cin >> N;

    vector<double> x(N), y(N);
    for (int i = 0; i < N; ++i){
        cin >> x[i] >> y[i];
    }

    vector<int> route(N);
    for (int i = 0; i < N; ++i){
        route[i] = i;
    }

    three_opt(route, x, y);

    cout << route_length(route, x, y) << "\n";
    for (int v : route){
        cout << v << " ";
    }
    cout << route[0] << "\n";

    return 0;
}