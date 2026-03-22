#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double dist(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1, dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}

double route_length(const vector<int>& route, const vector<double>& x, const vector<double>& y) {
    double length = 0;
    int n = route.size();
    for (int i = 0; i < n; ++i) {
        length += edge_dist(route, i, i + 1, x, y);
    }
    return length;
}

double edge_dist(const vector<int>& route, int i, int j, const vector<double>& x, const vector<double>& y) {
    int n = route.size();
    int a = route[(i + n) % n];
    int b = route[(j + n) % n];
    return dist(x[a], y[a], x[b], y[b]);
}

void reverse_part(vector<int>& route, int start, int end) {
    int n = route.size();
    while (start != end && (start + n - 1) % n != end) {
        swap(route[start], route[end]);
        start = (start + 1) % n;
        end = (end - 1 + n) % n;
    }
}

void three_opt(vector<int>& route, const vector<double>& x, const vector<double>& y) {
    int n = route.size();
    bool improved = true;

    while (improved) {
        improved = false;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 2; j < n; ++j) {
                for (int k = j + 2; k < n + (i > 0 ? 1 : 0); ++k) {
                    int a = i % n;
                    int b = (i + 1) % n;
                    int c = j % n;
                    int d = (j + 1) % n;
                    int e = k % n;
                    int f = (k + 1) % n;

                    double old_dist = edge_dist(route, a, b, x, y) + edge_dist(route, c, d, x, y) + edge_dist(route, e, f, x, y);

                    double new_dist;
                    vector<int> tmp = route;
                    reverse_part(tmp, b, c);
                    new_dist = edge_dist(tmp, a, b, x, y) + edge_dist(tmp, c, d, x, y) + edge_dist(tmp, e, f, x, y);
                    if (new_dist < old_dist) {
                        route = tmp;
                        improved = true;
                        break;
                    }

                    tmp = route;
                    reverse_part(tmp, d, e);
                    new_dist = edge_dist(tmp, a, b, x, y) + edge_dist(tmp, c, d, x, y) + edge_dist(tmp, e, f, x, y);
                    if (new_dist < old_dist) {
                        route = tmp;
                        improved = true;
                        break;
                    }

                    tmp = route;
                    reverse_part(tmp, b, c);
                    reverse_part(tmp, d, e);
                    new_dist = edge_dist(tmp, a, b, x, y) + edge_dist(tmp, c, d, x, y) + edge_dist(tmp, e, f, x, y);
                    if (new_dist < old_dist) {
                        route = tmp;
                        improved = true;
                        break;
                    }
                }
                if (improved) break;
            }
            if (improved) break;
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
