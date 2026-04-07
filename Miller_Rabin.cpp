#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Big_Int {
public:
    string val;

    Big_Int(string s = "0") {
        if (s.empty()) { val = "0"; return; }
        size_t first = s.find_first_not_of('0');
        val = (first == string::npos) ? "0" : s.substr(first);
    }

    Big_Int(long long n) : Big_Int(to_string(n)) {}

    bool isAtLeast(const Big_Int& other) const {
        if (val.size() != other.val.size()) 
            return val.size() > other.val.size();
        return val >= other.val;
    }

    bool operator==(const Big_Int& other) const { return val == other.val; }
    bool operator!=(const Big_Int& other) const { return val != other.val; }

    Big_Int operator+(const Big_Int& other) const {
        string res = "";
        int i = val.size() - 1, j = other.val.size() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int d1 = (i >= 0) ? val[i--] - '0' : 0;
            int d2 = (j >= 0) ? other.val[j--] - '0' : 0;
            int sum = d1 + d2 + carry;
            res += (sum % 10) + '0';
            carry = sum / 10;
        }
        reverse(res.begin(), res.end());
        return Big_Int(res);
    }

    Big_Int operator-(const Big_Int& other) const {
        if (!this->isAtLeast(other)) return Big_Int("0");
        string res = "";
        int i = val.size() - 1, j = other.val.size() - 1, borrow = 0;
        while (i >= 0) {
            int top = val[i--] - '0' - borrow;
            int bottom = (j >= 0) ? other.val[j--] - '0' : 0;
            if (top < bottom) { top += 10; borrow = 1; }
            else { borrow = 0; }
            res += (top - bottom) + '0';
        }
        reverse(res.begin(), res.end());
        return Big_Int(res);
    }

    Big_Int operator*(const Big_Int& other) const {
        if (val == "0" || other.val == "0") return Big_Int("0");
        vector<int> digits(val.size() + other.val.size(), 0);
        for (int i = val.size() - 1; i >= 0; i--) {
            for (int j = other.val.size() - 1; j >= 0; j--) {
                int product = (val[i] - '0') * (other.val[j] - '0');
                int p1 = i + j, p2 = i + j + 1;
                int sum = product + digits[p2];
                digits[p2] = sum % 10;
                digits[p1] += sum / 10;
            }
        }
        string res = "";
        for (int d : digits) if (!(res.empty() && d == 0)) res += (d + '0');
        return res.empty() ? Big_Int("0") : Big_Int(res);
    }

    
    pair<Big_Int, Big_Int> divmod(const Big_Int& other) const {
        if (other.val == "0") return {Big_Int("0"), Big_Int("0")};
        string quotient = "";
        Big_Int remainder("0");
        for (char c : val) {
            remainder = Big_Int(remainder.val == "0" ? string(1, c) : remainder.val + c);
            int count = 0;
            while (remainder.isAtLeast(other)) {
                remainder = remainder - other;
                count++;
            }
            quotient += (count + '0');
        }
        return {Big_Int(quotient), remainder};
    }

    Big_Int operator/(const Big_Int& other) const { return divmod(other).first; }
    Big_Int operator%(const Big_Int& other) const { return divmod(other).second; }
    
    bool isEven() const { return (val.back() - '0') % 2 == 0; }
};


Big_Int power(Big_Int base, Big_Int exp, Big_Int mod) {
    Big_Int res("1");
    base = base % mod;
    while (exp.val != "0") {
        if (!exp.isEven()) res = (res * base) % mod;
        base = (base * base) % mod;
        exp = exp / Big_Int("2");
    }
    return res;
}


bool miller_rabin(Big_Int n, int k = 5) {
    if (n.val == "1") return false;
    if (n.val == "2" || n.val == "3") return true;
    if (n.isEven()) return false;

    
    Big_Int d = n - Big_Int("1");
    int s = 0;
    while (d.isEven()) {
        d = d / Big_Int("2");
        s++;
    }

    for (int i = 0; i < k; i++) {
        int bases[] = {2, 3, 5, 7, 11, 13, 17};
        Big_Int a(to_string(bases[i % 7]));
        if (a.isAtLeast(n)) break; 

        Big_Int x = power(a, d, n);
        if (x == Big_Int("1") || x == (n - Big_Int("1"))) continue;

        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = (x * x) % n;
            if (x == (n - Big_Int("1"))) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

int main() {
    Big_Int p1("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000039"); 

    cout << p1.val << (miller_rabin(p1) ? " e" : " ne e")<<" prost" << endl;

    return 0;
}