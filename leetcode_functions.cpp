#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>
#include <sstream>

using namespace std;
struct Event {
  int id, timestamp;
    bool isStart;
    int switchedAt;
    Event(string str) {
        string buffer;
        std::stringstream iss(str);
        getline(iss, buffer, ':');
        id = stoi(buffer);
        getline(iss, buffer,':');
        isStart = buffer == "start";
        getline(iss, buffer, ':');
        timestamp = stoi(buffer);
    }
};
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> result(n, 0);
        stack<Event> calls;
        int timestamp = -1;
        for (int e = 0; e < logs.size(); ++e) {
            Event current(logs[e]);
            if (current.isStart) {
                if (!calls.empty()) {
                    result[calls.top().id] += current.timestamp - timestamp - 1;
                }
                calls.push(current);
            } else {
                Event start = calls.top(); calls.pop();
                result[start.id] += current.timestamp - timestamp + 1;
            }
            timestamp = current.timestamp;
        }
        return result;
    }
};

int main() {
    vector<string> logs = {"0:start:0","0:start:2","0:end:5","1:start:7","1:end:7","0:end:8"};
    vector<int> res = Solution().exclusiveTime(2, logs);
    cout << res[0] << endl;
    cout << res[1] << endl;
}