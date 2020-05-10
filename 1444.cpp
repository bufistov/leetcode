#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
// Number of Ways of Cutting a Pizza
class Solution {
public:
    int R, C;
    int MOD = 1e9 +7;
    int ways(vector<string>& pizza, int K) {
        R = pizza.size();
        if (R == 0) {
            return 0;
        }
        C = pizza.front().size();
        if (C == 0) {
            return 0;
        }
        vector<vector<int>> sums(R, vector<int>(C, 0));
        sums[0][0] = pizza[0][0] == 'A';
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                int sum = pizza[r][c] == 'A';
                if (r > 0) {
                    sum += sums[r - 1][c];
                }
                if (c > 0) {
                    sum += sums[r][c-1];
                }
                if (r > 0 && c > 0) {
                    sum -=sums[r-1][c-1];
                }
                sums[r][c] = sum;
            }
        }
        vector<vector<vector<vector<int> > > > dp(R, vector<vector<vector<int>>>(C,
                                                    vector<vector<int>>(K, vector<int>(1 << K,0))));
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (hasApple(r, c, R-1, C-1, sums)) {
                    dp[r][c][0][0] = 1;
                }
            }
        }
        
        for (int k = 1; k < K; ++k) {
            for (int mask = 0; mask < (1 << k); ++mask) {
                for (int r = 0; r < R; ++r) {
                    for (int c = 0; c < C; ++c) {
                        int firstBit = 1 << (k-1);
                        bool isHorizontal = (mask & firstBit) != 0;
                        int result = 0;
                        if (isHorizontal) {
                            for (int r1 = r + 1; r1 < R; ++r1) {
                                if (hasApple(r, c, r1-1, C-1, sums)) {
                                    result = (result + dp[r1][c][k-1][mask & ~firstBit]) % MOD;
                                }
                            }
                        } else {
                            for (int c1 = c + 1; c1 < C; ++c1) {
                                if (hasApple(r, c, R-1, c1-1, sums)) {
                                    result = (result + dp[r][c1][k-1][mask]) % MOD;
                                }
                            }
                        }
                        dp[r][c][k][mask] = result;
                    }
                }
            }
        }
        int result = 0;
        for (int i = 0; i < (1 << K); ++i) {
            result = (result + dp[0][0][K-1][i]) % MOD;
        }
        return result;
    }
    
    int hasApple(int topLeftRow, int topLeftColumn, int bottomRightRow, int bottomRightColumn, vector<vector<int>> &sums) {
        int res = sums[bottomRightRow][bottomRightColumn];
        if (topLeftRow > 0) {
            res -= sums[topLeftRow-1][bottomRightColumn];
        }
        if (topLeftColumn > 0) {
            res -= sums[bottomRightRow][topLeftColumn - 1];
        }
        if (topLeftRow > 0 && topLeftColumn > 0) {
            res += sums[topLeftRow-1][topLeftColumn-1];
        }
        return res > 0;
    } 
};

int main() {
    vector<string> input = {"A..","AAA","..."};
    cout<< Solution().ways(input, 3) << endl;
}