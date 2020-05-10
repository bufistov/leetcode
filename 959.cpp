#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
using namespace std;

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        vector<vector<int>> scaled(2 * grid.size(), vector<int>(2 * grid.size(), 0));
        for (int r = 0; r < grid.size(); ++r) {
            for (int c = 0; c < grid.size(); ++c) {
                if (grid[r][c] == '\\') {
                    scaled[2 * r][2 * c] = scaled[2*r+1][2*c + 1] = 1;
                }
                if (grid[r][c] == '/') {
                    scaled[2*r + 1][2*c] = scaled[2*r][2*c + 1] = 1;
                }
            }
        }
        int result = 0;
        const int N = scaled.size();
        vector<vector<bool>> visited(N, vector<bool>(N, false));
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (scaled[r][c] == 0 && !visited[r][c]) {
                    queue<tuple<int, int>> Q;
                    Q.push(make_tuple(r, c));
                    ++result;
                    visited[r][c] = true;
                    while (!Q.empty()) {
                        int rr, cc;
                        tie(rr, cc) = Q.front(); Q.pop();
                        for (int up = -1; up <= 1; up += 1) {
                            for (int left = -1; left <= 1; left += 1) {
                                if (abs(up) + abs(left) == 1) {
                                    int rn = rr + up, cn = cc + left;
                                    if (rn <= N - 1 && rn >= 0 && cn >= 0 && cn <= N - 1 && scaled[rn][cn] == 0 && !visited[rn][cn]) {
                                        visited[rn][cn] = true;
                                        Q.push(make_pair(rn, cn));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return result;
    }
};

int main() {
    vector<string> grid = {"\\/\\ "," /\\/"," \\/ ","/ / "};
    cout << Solution().regionsBySlashes(grid) << endl;
}