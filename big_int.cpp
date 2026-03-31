#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Big_Int {
public:
    string val;

    Big_Int(string s = "0") {
        size_t first = s.find_first_not_of('0');
        val = (first == string::npos) ? "0" : s.substr(first);
    }

    bool isAtLeast(const Big_Int& other) const {
        if (val.size() != other.val.size()) 
            return val.size() > other.val.size();
        return val >= other.val;
    }

    Big_Int operator+(const Big_Int& other) const {
        string res = "";
        int i = val.size() - 1;
        int j = other.val.size() - 1;
        int carry = 0;

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
        int i = val.size() - 1;
        int j = other.val.size() - 1;
        int borrow = 0;

        while (i >= 0) {
            int top = val[i--] - '0' - borrow;
            int bottom = (j >= 0) ? other.val[j--] - '0' : 0;

            if (top < bottom) {
                top += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
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
        for (int d : digits) {
            if (!(res.empty() && d == 0)) res += (d + '0');
        }
        return res.empty() ? Big_Int("0") : Big_Int(res);
    }

    Big_Int operator/(const Big_Int& other) const {
        if (other.val == "0") return Big_Int("0");

        string quotient = "";
        string current_chunk = "";

        for (char c : val) {
            current_chunk += c;
            Big_Int temp(current_chunk);
            int count = 0;
            while (temp.isAtLeast(other)) {
                temp = temp - other;
                count++;
            }
            current_chunk = temp.val;
            quotient += (count + '0');
        }
        return Big_Int(quotient);
    }
};

int main() {
    Big_Int numA("55667788990011223344556677889900");
    Big_Int numB("123456789123456789");

    cout << (numA + numB).val << endl;
    cout << (numA - numB).val << endl;
    cout << (numA * numB).val << endl;
    cout << (numA / numB).val << endl;

    return 0;
}