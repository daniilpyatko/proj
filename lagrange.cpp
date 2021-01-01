#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

typedef long double ld;
typedef long long ll;

using namespace std;


struct poly{
    int n;
    vector<ld> a;
    poly(){}

    poly(const poly &other) {
        n = other.n;
        a = other.a;
    }

    poly(poly &other) {
        n = other.n;
        a = other.a;
    }

    poly operator+(const poly &other) {
        poly res;
        res.n = max(n, other.n);
        res.a.resize(res.n);
        for (int i = 0; i < res.n; ++i) {
            if (i < n) {
                res.a[i] += a[i];
            }
            if (i < other.n) {
                res.a[i] += other.a[i];
            }
        }
        return res;
    }

    poly operator*(ld k) {
        poly res;
        res.n = n;
        res.a = a;
        for (int i = 0; i < res.n; ++i) {
            res.a[i] *= k;
        }
        return res;
    }

};

void shift(poly &p) {
    p.n++;
    p.a.push_back(0);
    for (int i = p.n - 2; i >= 0; --i) {
        p.a[i + 1] = p.a[i];
    }
    p.a[0] = 0;
}

// p *= (x - a)
void mul_by(poly &p, ld a) {
    poly p1 = poly(p);
    p1 = p1 * (-a);
    shift(p);
    p = p + p1;
}




int n;
vector < ld > T;
vector < ld > N;

int main() {
	freopen("poly.txt", "r", stdin);
    cout << fixed;
    cout << setprecision(5);
    cin >> n;
    T.resize(n);
    N.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> T[i] >> N[i];
    }
    poly res;
    res.n = 1;
    res.a = {0};
    for (int i = 0; i < n; ++i) {
        poly cur;
        cur.n = 1;
        cur.a = {1};
        ld coeff = N[i];
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            mul_by(cur, T[j]);
            coeff /= (T[i] - T[j]);
        }
        res = res + cur * coeff;
    }
    for (int i = 0; i < n; ++i) {
        cout << N[i] / (ld)((ld)T[i] * T[i]) << " ";
    }
    cout << "\n";
    for (int i = res.n - 1; i >= 0; --i) {
        cout << res.a[i];
        if (i != 0) {
            cout << "x^" << i << " ";
        } 
    }
    cout << "\n";
}
