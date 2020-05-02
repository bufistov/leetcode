#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<short> trailingZeroesCount;
    Solution() {
        trailingZeroesCount = vector<short>(256, 2);
        int num = 1;
        for (int i = 1; i <= 8; ++i, num <<= 1) {
            trailingZeroesCount[num] = i - 1;
        }
        trailingZeroesCount[0] = 8;
    }
    bool isPowerOfFour(unsigned num) {
        if (num == 0) {
            return false;
        }
        bool isPow2 = (num & -num) == num;
        return isPow2 && (countTrailingZeroes(num) & 1) == 0;
    }
    int countTrailingZeroes(unsigned num) {
        int result = 0;
        while (num && !(num & 0xff)) {
            result += 8;
            num >>= 8;
        }
        return result + trailingZeroesCount[num];
    }
};

int main() {
    cout << Solution().isPowerOfFour(
-2147483647) << endl;
}