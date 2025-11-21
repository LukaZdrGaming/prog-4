#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    int n = 6;         
    int m = 10;        
    int maxCapacity = 20; 

    cout << n << " " << m << "\n";

    for (int i = 0; i < m; ++i) {
        int u = rand() % n;
        int v = rand() % n;
        while (v == u) v = rand() % n; 
        int c = 1 + rand() % maxCapacity; 
        cout << u << " " << v << " " << c << "\n";
    }

    int s = rand() % n;
    int t = rand() % n;
    while (t == s) t = rand() % n; 
    cout << s << " " << t << "\n";

    return 0;
}
