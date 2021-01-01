#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

typedef long double ld;
typedef long long ll;

using namespace std;


// v -> {u, sqrt(p)}
vector < vector < pair < int, ld > > > g;

int n, m;

ld t;
int ans = 0;


void rec(int v, ld cur_t) {
	for (auto u: g[v]) {
		if (cur_t + u.second > t) {
			ans++;
		} else {
			rec(u.first, cur_t + u.second);
		}
	}
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
    	g[v].push_back({u, sqrt(p)});
    	// Extra edge for undirected graph
    	g[u].push_back({v, sqrt(p)});
    }
    cout << "t" << "\t" << "N(t)" << "\t" << "N(t) / t^2\n";
    for (int i = 2; i <= 35; ++i) {
    	ans = 0;
    	t = i;
    	rec(0, 0);
    	cout << t << "\t" << ans << "\t" << ans / ((ld)t * t) << "\n";
    }
}
