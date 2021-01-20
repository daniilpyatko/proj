#include <vector>
#include <map>
#include <utility>
#include <set>
#include <string>
#include <deque>
#include <iostream>
#include <math.h>

template <typename T>
struct Edge {
    int v, u, id;
    T w;
    Edge(){}
    Edge(int v, int u, T w, int id) : v(v), u(u), w(w), id(id) {}
};

template<typename T>
class Graph {
public:
    Graph() {}
    Graph(int n, int m, int start);
    // Graph(const Graph<T>&){}
    void addEdge(int v, int u, int w);
    int getN(int time);
    void precalc(int time);
private:
    int n, m, start;
    int lastEdgeId = 0;
    std::vector<std::vector<Edge<T>>> g;
    std::map<int, int> memo;
};