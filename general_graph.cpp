#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <deque>
#include <set>

typedef long double ld;
typedef long long ll;

using namespace std;

const int max_edge_p = 10;

struct edge {
    int to;
    ld w;
    int id; 
    edge(){}
};

struct path {
    int v;
    ld time;
    vector < int > took;
};



// v -> {u, sqrt(p)}
vector < vector < edge > > g;

int n, m;

int solve(ld t) {
    int ans = 0;
    set < vector < int > > used;
    deque < path > q;
    path first;
    first.v = 0;
    first.time = 0;
    first.took = vector < int > (max_edge_p);
    q.push_back(first);
    while(!q.empty()) {
        path cur = q.front();
        q.pop_front();
        if (used.find(cur.took) != used.end()) {
            continue;
        }
        used.insert(cur.took); 
        for (auto u: g[cur.v]) {
            if (cur.time + u.w > t) {
                ans++;
            } else {
                path nw;
                nw.v = u.to;
                nw.time = cur.time + u.w;
                nw.took = cur.took;
                nw.took[u.id]++;
                q.push_back(nw);      
            }
        }
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        ll v, u, p;
        cin >> v >> u >> p;
        --v, --u;
        edge tou = edge();
        edge tov = edge();
        tou.to = u, tov.to = v;
        tov.w = tou.w = sqrt(p);
        tov.id = tou.id = p; 
        g[v].push_back(tou);
        g[u].push_back(tov);
        cerr << "HERE\n";
    }
    cout << "t" << "\t" << "N(t)" << "\t" << "N(t) / t^2\n";
    for (int i = 2; i <= 100; ++i) {
        int t = i;
        int ans = solve(t);
        cout << t << "\t" << ans << "\t" << ans / ((ld)t * t) << "\n";
    }
}
