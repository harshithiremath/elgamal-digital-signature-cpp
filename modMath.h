
#include <unordered_set>
using namespace std;

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if (((a % m) * (x % m)) % m == 1)
            return x;
};
int modPower(long long x, unsigned int y, int p) {
    int res = 1;
    x = x % p;
    if (x == 0) return 0;

    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;

        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
};

long long modMultiplication(long long a, long long b, long long mod) {
    long long res = 0;
    a %= mod;
    while (b) {
        if (b & 1)
            res = (res + a) % mod;
        a = (2 * a) % mod;
        b >>= 1;
    }

    return res;
}

bool modCheckPrimitivity(long long a, long long p) {
    std::unordered_set<long long> cont;
    if (!(a > 0 && a < p)) return false;
    for (long long i = 0; i < p - 1; i++) {
        long long res = modPower(a, i, p);

        if (cont.find(res) != cont.end()) {
            return false;
        } else {
            cont.insert(res);
        }
    }

    if (cont.size() != p - 1) return false;

    return true;
}