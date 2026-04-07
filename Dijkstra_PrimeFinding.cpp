#include <iostream>
#include <vector>

using namespace std;

void runDijkstraPrimes(int limit) {
    if (limit < 1) return;

    vector<long long> P; 
    vector<long long> V; 
    
    P.push_back(2);
    cout << "1: 2" << endl;

    long long X = 1;
    long long SQUARE = 4;
    int LIM = 0; 

    for (int i = 2; i <= limit; ++i) {
        bool is_prime;
        do {
            X += 2;

            if (SQUARE <= X) {
                V.push_back(SQUARE);
                LIM++;
                if (LIM < (int)P.size()) {
                    SQUARE = P[LIM] * P[LIM];
                }
            }

            is_prime = true;
            for (int k = 1; k < LIM; ++k) {
                while (V[k] < X) {
                    V[k] += P[k];
                }
                if (X == V[k]) {
                    is_prime = false;
                    break;
                }
            }
        } while (!is_prime);

        P.push_back(X);
        cout << i << ": " << X << endl;
    }
}

int main() {
    int n;
    cin >> n;
    
    runDijkstraPrimes(n);
    
    return 0;
}