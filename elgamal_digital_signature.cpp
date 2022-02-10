#include <iostream>

#include "modMath.h"
using namespace std;
class Sender {
   private:
    int Xa;

   public:
    long long q, alpha, m, k, S1, S2, Ya;

    Sender(int q, int alpha, int Xa, int m, int k) {
        this->q = q;
        this->alpha = alpha;
        this->Xa = Xa;
        this->m = m;
        this->k = k;
        Ya = modPower(alpha, Xa, q);
        calS1();
        calS2();
        cout << "Public key set {q, alpha, Ya} is {" << q << ',' << alpha << ',' << Ya << "}" << endl;
        cout << "Message : " << m << "\nS1 : " << S1 << "\nS2 : " << S2 << endl;
    }
    void calS1() {
        S1 = modPower(alpha, k, q);
    }
    void calS2() {
        S2 = modMultiplication(modInverse(k, q - 1), (m - modMultiplication(Xa, S1, q - 1)) % (q - 1), (q - 1)) % (q - 1);
    }
};

class Receiver {
   private:
    int v1, v2;

   public:
    int m, q, alpha, Ya, S1, S2;
    Receiver(int m, int q, int alpha, int Ya, int S1, int S2) {
        this->m = m;
        this->q = q;
        this->alpha = alpha;
        this->Ya = Ya;
        this->S1 = S1;
        this->S2 = S2;
    }
    void cal_v1() {
        v1 = modPower(alpha, m, q);
    }
    void cal_v2() {
        v2 = modMultiplication(modPower(Ya, S1, q), modPower(S1, S2, q), q);
    }
    void verify() {
        cal_v1();
        cal_v2();
        // TODO 1 <= s1 <= q
        if (v1 == v2) {
            cout << "Signatures matching!" << endl;
        } else {
            cout << "Signatures invalid for the document!" << endl;
        }
        cout << "Value pf V1: " << v1 << endl;
        cout << "Value of V2: " << v2 << endl;
    }
};

int main() {
    int q, alpha, m, k, Xa;
    cout << "q (prime number): ";
    cin >> q;
    cout << "alpha (primitive root of q) : ";
    cin >> alpha;
    while (!modCheckPrimitivity(alpha, q)) {
        cout << alpha << " is not a primitive root of " << q << endl;
        cout << "alpha (primitive root of q) : ";
        cin >> alpha;
    }

    cout << "m (hash of message) [0 <= m <= q-1]: ";
    cin >> m;
    cout << "k [(1 <= k <= q-1) and gcd(k, q-1)=1] : ";
    cin >> k;
    cout << "Xa (1 <= Xa < q-1): ";
    cin >> Xa;

    Sender alice(q, alpha, Xa, m, k);
    cout << "Verification of Elgamal Digital Signature" << endl;

    int S1, S2;
    cout << "m : ";
    cin >> m;
    cout << "S1 : ";
    cin >> S1;
    cout << "S2 : ";
    cin >> S2;

    Receiver bob(m, q, alpha, alice.Ya, S1, S2);
    bob.verify();
    return 0;
}