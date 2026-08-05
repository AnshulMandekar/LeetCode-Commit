// Date: 2026-08-05
// Problem: Remove Methods From Project
// Difficulty: Medium
// URL: https://leetcode.com/problems/remove-methods-from-project/

/*
 * Description:
 * You are maintaining a project that has `n` methods numbered from `0` to `n - 1`.
 * 
 * You are given two integers `n` and `k`, and a 2D integer array `invocations`, where `invocations[i] = [ai, bi]` indicates that method `ai` invokes method `bi`.
 * 
 * There is a known bug in method `k`. Method `k`, along with any method invoked by it, either **directly** or **indirectly**, are considered **suspicious** and we aim to remove them.
 * 
 * A group of methods can only be removed if no method **outside** the group invokes any methods **within** it.
 * 
 * Return an array containing all the remaining methods after removing all the **suspicious** methods. You may return the answer in *any order*. If it is not possible to remove **all** the suspicious methods, **none** should be removed.
 * 
 * Example 1:**
 * 
 * **Input:** n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
 * 
 * **Output:** [0,1,2,3]
 * 
 * **Explanation:**
 * 
 * Method 2 and method 1 are suspicious, but they are directly invoked by methods 3 and 0, which are not suspicious. We return all elements without removing anything.
 * 
 * Example 2:**
 * 
 * **Input:** n = 5, k = 0, invocations = [[1,2],[0,2],[0,1],[3,4]]
 * 
 * **Output:** [3,4]
 * 
 * **Explanation:**
 * 
 * Methods 0, 1, and 2 are suspicious and they are not directly invoked by any other method. We can remove them.
 * 
 * Example 3:**
 * 
 * **Input:** n = 3, k = 2, invocations = [[1,2],[0,1],[2,0]]
 * 
 * **Output:** []
 * 
 * **Explanation:**
 * 
 * All methods are suspicious. We can remove them.
 * 
 * **Constraints:**
 * 
 * 	- `1 <= n <= 105`
 * 
 * 	- `0 <= k <= n - 1`
 * 
 * 	- `0 <= invocations.length <= 2 * 105`
 * 
 * 	- `invocations[i] == [ai, bi]`
 * 
 * 	- `0 <= ai, bi <= n - 1`
 * 
 * 	- `ai != bi`
 * 
 * 	- `invocations[i] != invocations[j]`
 */

// Time:  O(n + e)
// Space: O(n + e)

// bfs
class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        const auto& bfs = [&]() {
            vector<bool> lookup(n);
            lookup[k] = true;
            vector<int> q = {k};
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    for (const auto& v : adj[u]) {
                        if (lookup[v]) {
                            continue;
                        }
                        lookup[v] = true;
                        new_q.emplace_back(v);
                    }
                }
                q = move(new_q);
            }
            return lookup;
        };
       
        for (const auto& e : invocations) {
            adj[e[0]].emplace_back(e[1]);
        }
        const auto& lookup = bfs();
        for (const auto& e : invocations) {
            if (lookup[e[0]] != lookup[e[1]]) {
                vector<int> result(n);
                iota(begin(result), end(result), 0);
                return result;
            }
        }
        vector<int> result;
        for (int u = 0; u < n; ++u) {
            if (!lookup[u]) {
                result.emplace_back(u);
            }
        }
        return result;
    }
};
