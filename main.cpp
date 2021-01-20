#include <iostream>

#include "graph.cpp"


// in case of double roots are added

template <typename T>
void simpleCycle(Graph<T> &g) {
    g = Graph<T>(3, 6, 0);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 0, 2);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 1, 3);
    g.addEdge(2, 0, 5);
    g.addEdge(0, 2, 5);
    g.precalc(100);
}



int main() {
    Graph<double> gd;
    simpleCycle(gd);

    Graph<int> gi;
    simpleCycle(gi);
    for (int i = 1; i <= 100; ++i) {
        std::cout << "Double: " << i << " " << gd.getN(i) << " " << (gd.getN(i) / (double) (i * i)) << "\n";
    }
    std::cout << "\n\n\n";
    for (int i = 1; i <= 100; ++i) {
        std::cout << "Int: " << i << " " << gi.getN(i) << "\n";
    }
}