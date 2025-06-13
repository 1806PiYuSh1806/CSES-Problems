#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<long long>> nums(n, vector<long long>(3));
    for (int i = 0; i < n; i++) {
        cin >> nums[i][0] >> nums[i][1] >> nums[i][2];
    }

    sort(nums.begin(), nums.end());

    vector<long long> startTimes;
    for (auto &v : nums) startTimes.push_back(v[0]);

    vector<long long> dp(n + 1, 0);

    for (int i = n - 1; i >= 0; i--) {
        int next = upper_bound(startTimes.begin(), startTimes.end(), nums[i][1]) - startTimes.begin();

        long long take = nums[i][2] + dp[next];
        long long skip = dp[i + 1];

        dp[i] = max(take, skip);
    }

    cout << dp[0] << "\n";
    return 0;
}
