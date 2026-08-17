// Date: 2026-08-17
// Problem: Stone Game V
// Difficulty: Hard
// URL: https://leetcode.com/problems/stone-game-v/

/*
 * Description:
 * There are several stones **arranged in a row**, and each stone has an associated value which is an integer given in the array `stoneValue`.
 * 
 * In each round of the game, Alice divides the row into **two non-empty rows** (i.e. left row and right row), then Bob calculates the value of each row which is the sum of the values of all the stones in this row. Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row. If the value of the two rows are equal, Bob lets Alice decide which row will be thrown away. The next round starts with the remaining row.
 * 
 * The game ends when there is only **one stone remaining**. Alice's score is initially **zero**.
 * 
 * Return the maximum score that Alice can obtain.
 * 
 * Example 1:**
 * 
 * **Input:** stoneValue = [6,2,3,4,5,5]
 * **Output:** 18
 * **Explanation:** In the first round, Alice divides the row to [6,2,3], [4,5,5]. The left row has the value 11 and the right row has value 14. Bob throws away the right row and Alice's score is now 11.
 * In the second round Alice divides the row to [6], [2,3]. This time Bob throws away the left row and Alice's score becomes 16 (11 + 5).
 * The last round Alice has only one choice to divide the row which is [2], [3]. Bob throws away the right row and Alice's score is now 18 (16 + 2). The game ends because only one stone is remaining in the row.
 * 
 * Example 2:**
 * 
 * **Input:** stoneValue = [7,7,7,7,7,7,7]
 * **Output:** 28
 * 
 * Example 3:**
 * 
 * **Input:** stoneValue = [4]
 * **Output:** 0
 * 
 * **Constraints:**
 * 
 * 	- `1 <= stoneValue.length <= 500`
 * 
 * 	- `1 <= stoneValue[i] <= 106`
 */

// Time:  O(n^2)
// Space: O(n^2)

class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        const int n = stoneValue.size();
        vector<int> prefix(n + 1);
        partial_sum(cbegin(stoneValue), cend(stoneValue), begin(prefix) + 1);
        
        vector<int> mid(n);
        iota(begin(mid), end(mid), 0);

        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = stoneValue[i];
        }

        int max_score = 0;
        for (int l = 2; l <= n; ++l) {
            for (int i = 0; i <= n - l; ++i) {
                const int j = i + l - 1;
                while (prefix[mid[i]] - prefix[i] < prefix[j + 1] - prefix[mid[i]]) {
                    ++mid[i];  // Time: O(n^2) in total
                }
                const int p = mid[i];
                max_score = 0;
                if (prefix[p] - prefix[i] == prefix[j + 1] - prefix[p]) {
                    max_score = max(dp[i][p - 1], dp[j][p]);
                } else {
                    if (i <= p - 2) {
                        max_score = max(max_score, dp[i][p - 2]);
                    }
                    if (p <= j) {
                        max_score = max(max_score, dp[j][p]);
                    }
                }
                dp[i][j] = max(dp[i][j - 1], (prefix[j + 1] - prefix[i]) + max_score);
                dp[j][i] = max(dp[j][i + 1], (prefix[j + 1] - prefix[i]) + max_score);
            }
        }
        return max_score;
    }
};


// Time:  O(n^2)
// Space: O(n^2)
class Solution2 {
public:
    int stoneGameV(vector<int>& stoneValue) {
        const int n = stoneValue.size();
        vector<int> prefix(n + 1);
        partial_sum(cbegin(stoneValue), cend(stoneValue), begin(prefix) + 1);

        vector<vector<int>> mid(n, vector<int>(n));
        for (int l = 1; l <= n; ++l) {
            for (int i = 0; i <= n - l; ++i) {
                const int j = i + l - 1;
                int p = (l == 1) ? i : mid[i][j - 1];
                while (prefix[p] - prefix[i] < prefix[j + 1] - prefix[p]) {
                    ++p;  // Time: O(n^2) in total
                }
                mid[i][j] = p;
            }
        }
        
        vector<vector<int>> rmq(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            rmq[i][i] = stoneValue[i];
        }

        vector<vector<int>> dp(n, vector<int>(n));
        for (int l = 2; l <= n; ++l) {
            for (int i = 0; i <= n - l; ++i) {
                const int j = i + l - 1;
                const int p = mid[i][j];
                int max_score = 0;
                if (prefix[p] - prefix[i] == prefix[j + 1] - prefix[p]) {
                    max_score = max(rmq[i][p - 1], rmq[j][p]);
                } else {
                    if (i <= p - 2) {
                        max_score = max(max_score, rmq[i][p - 2]);
                    }
                    if (p <= j) {
                        max_score = max(max_score, rmq[j][p]);
                    }
                }
                dp[i][j] = max_score;
                rmq[i][j] = max(rmq[i][j - 1], (prefix[j + 1] - prefix[i]) + max_score);
                rmq[j][i] = max(rmq[j][i + 1], (prefix[j + 1] - prefix[i]) + max_score);
            }
        }
        return dp[0][n - 1];
    }
};
