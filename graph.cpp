#include "graph.hpp"


template <typename T>
Graph<T>::Graph(int n, int m, int start): n(n), m(m), start(start) {
    g.resize(n);
}

template <>
void Graph<int>::addEdge(int v, int u, int w) {
    g[v].push_back(Edge<int>(v, u, w, w));
}


template <>
void Graph<double>::addEdge(int v, int u, int w) {
    g[v].push_back(Edge<double>(v, u, sqrt(w), w));
}

template <typename T>
int Graph<T>::getN(int time) {
    if (memo.count(time)) {
        return memo[time];
    } else {
        throw std::string("The value at the given moment of time is not precalculated");
    }
}

template <>
void Graph<int>::precalc(int time) {
    std::set<std::pair<int, int>> q;
    std::vector<int> cnt(time + 1);
    memo[0] = 1;
    q.insert({0, start});
    while (!q.empty()) {
        auto cur = *q.begin();
        q.erase(q.begin());
        // (cur.first; cur.first + u.w]
        for (int i = 0; i < g[cur.second].size(); ++i) {
            auto u = g[cur.second][i];
            if (cur.first + 1 <= time) {
                cnt[cur.first + 1]++;
            }
            if (cur.first + u.w + 1 <= time) {
                cnt[cur.first + u.w + 1]--;
            }
            int u_time = cur.first + u.w;
            if (u_time < time) {
                q.insert({u_time, u.u});
            }
        }
    }
    int sv = 0;
    for (int i = 0; i <= time; ++i) {
        sv += cnt[i];
        memo[i] = sv;
    }
}

struct Path {
    int v;
    double time;
    std::vector<int> took;
};

template <>
void Graph<double>::precalc(int time) {
    std::vector<int> cnt(time + 1);
    std::set <std::vector<int>> used;
    std::deque<Path> q;
    Path first;
    first.v = start;
    first.time = 0;
    first.took = std::vector <int> (m);
    q.push_back(first);
    memo[0] = 1;
    while(!q.empty()) {
        Path cur = q.front();
        q.pop_front();
        if (used.find(cur.took) != used.end()) {
            continue;
        }
        used.insert(cur.took); 
        for (auto u: g[cur.v]) {
            int l = ceil(cur.time);
            int r = floor(cur.time + u.w) + 1;
            if (l <= time) {
                cnt[l]++;
            }
            if (r <= time) {
                cnt[r]--;
            }
            if (cur.time + u.w < time) {
                Path nw;
                nw.v = u.u;
                nw.time = cur.time + u.w;
                nw.took = cur.took;
                nw.took[u.id]++;
                q.push_back(nw);      
            } 
        }
    }
    int sv = 0;
    for (int i = 0; i <= time; ++i) {
        sv += cnt[i];
        memo[i] = sv;
    }
}


template class Graph<int>;
template class Graph<double>;

