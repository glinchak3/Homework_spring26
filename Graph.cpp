#include <iostream>
#include <vector>
#include <fstream>
#include "minisat/core/Solver.h"

struct Edge {
    int u;
    int v;
};

int main() {

    std::string filename = "graph.txt";
    std::ifstream inFile(filename);

    int numVertices = 0;
    int numEdges = 0;

    inFile >> numVertices >> numEdges;

    std::vector<Edge> edges;
    for (int i = 0; i < numEdges; i++) {
        Edge e;
        inFile >> e.u >> e.v;
        edges.push_back(e);
    }
    inFile.close();

    int numColors = 3; 

    Minisat::Solver solver;

    int totalVars = numVertices * numColors;
    for (int i = 0; i < totalVars; i++) {
        solver.newVar();
    }

    auto getLit = [&](int vertex, int color, bool positive) {
        int varId = vertex * numColors + color;
        return positive ? Minisat::mkLit(varId) : ~Minisat::mkLit(varId);
    };

    for (int v = 0; v < numVertices; v++) {
        Minisat::vec<Minisat::Lit> clause;
        for (int c = 0; c < numColors; c++) {
            clause.push(getLit(v, c, true));
        }
        solver.addClause(clause);
    }

    for (int v = 0; v < numVertices; v++) {
        for (int c1 = 0; c1 < numColors; c1++) {
            for (int c2 = c1 + 1; c2 < numColors; c2++) {
                solver.addClause(getLit(v, c1, false), getLit(v, c2, false));
            }
        }
    }

    for (const auto& edge : edges) {
        for (int c = 0; c < numColors; c++) {
            solver.addClause(getLit(edge.u, c, false), getLit(edge.v, c, false));
        }
    }

    bool result = solver.solve();

    if (result) {
        for (int v = 0; v < numVertices; v++) {
            for (int c = 0; c < numColors; c++) {
                int varId = v * numColors + c;
                if (solver.modelValue(varId) == Minisat::l_True) {
                    std::cout << v << " ->  " << c << std::endl;
                }
            }
        }
    } 
    return 0;
}
