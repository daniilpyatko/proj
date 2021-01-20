#include <vector>
#include <cmath>

typedef long double ld;
typedef long long ll;

class lagrange {

public:
    // pairs (x, f(x))
    static std::vector<ld> get_poly(const std::vector<ll> &N, const std::vector<ll> &T) {
        lagrange::poly res;
        int n = N.size();
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
        return res.a;
    }

    struct poly{
        int n;
        std::vector<ld> a;
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
            res.n = std::max(n, other.n);
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

    static void shift(poly &p) {
        p.n++;
        p.a.push_back(0);
        for (int i = p.n - 2; i >= 0; --i) {
            p.a[i + 1] = p.a[i];
        }
        p.a[0] = 0;
    }

    // p *= (x - a)
    static void mul_by(poly &p, ld a) {
        poly p1 = poly(p);
        p1 = p1 * (-a);
        shift(p);
        p = p + p1;
    }
};

