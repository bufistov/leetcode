#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
    unordered_map<long long, int> pows;
public:
    int getKth(int lo, int hi, int k) {
        typedef tuple<int, int> ti_t;
        priority_queue<ti_t> kBest;
        for (int i = lo; i <= hi; ++i) {
            int pow = getPow(i);
            if (kBest.size() < k || pow < get<0>(kBest.top())) {
                kBest.push(make_tuple(pow, i));
            }
            if (kBest.size() > k) {
                kBest.pop();
            }
        }
        return get<1>(kBest.top());
    }
    
    int getPow(long long x) {
        auto it = pows.find(x);
        int result = 0;
        if (it == pows.end()) {
            if (x == 1) {
                result = 0;
            } else {
                if (x % 2) {
                    result = 1 + getPow(3*x + 1);
                } else {
                    result = 1 + getPow(x / 2);
                }
            }
            pows.insert(make_pair(x, result));
        } else {
            result = it->second;
        }
        return result;
    }
};

int main() {

    cout << Solution().getKth(12, 15, 3) << endl;
}