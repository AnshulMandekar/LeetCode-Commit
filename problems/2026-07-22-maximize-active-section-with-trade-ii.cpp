// Date: 2026-07-22
// Problem: Maximize Active Section with Trade II
// Difficulty: Hard
// URL: https://leetcode.com/problems/maximize-active-section-with-trade-ii/

/*
 * Description:
 * You are given a binary string `s` of length `n`, where:
 * 
 * 	- `'1'` represents an **active** section.
 * 
 * 	- `'0'` represents an **inactive** section.
 * 
 * You can perform **at most one trade** to maximize the number of active sections in `s`. In a trade, you:
 * 
 * 	- Convert a contiguous block of `'1'`s that is surrounded by `'0'`s to all `'0'`s.
 * 
 * 	- Afterward, convert a contiguous block of `'0'`s that is surrounded by `'1'`s to all `'1'`s.
 * 
 * Additionally, you are given a **2D array** `queries`, where `queries[i] = [li, ri]` represents a substring `s[li...ri]`.
 * 
 * For each query, determine the **maximum** possible number of active sections in `s` after making the optimal trade on the substring `s[li...ri]`.
 * 
 * Return an array `answer`, where `answer[i]` is the result for `queries[i]`.
 * 
 * **Note**
 * 
 * 	- For each query, treat `s[li...ri]` as if it is **augmented** with a `'1'` at both ends, forming `t = '1' + s[li...ri] + '1'`. The augmented `'1'`s **do not** contribute to the final count.
 * 
 * 	- The queries are independent of each other.
 * 
 * Example 1:**
 * 
 * **Input:** s = "01", queries = [[0,1]]
 * 
 * **Output:** [1]
 * 
 * **Explanation:**
 * 
 * Because there is no block of `'1'`s surrounded by `'0'`s, no valid trade is possible. The maximum number of active sections is 1.
 * 
 * Example 2:**
 * 
 * **Input:** s = "0100", queries = [[0,3],[0,2],[1,3],[2,3]]
 * 
 * **Output:** [4,3,1,1]
 * 
 * **Explanation:**
 * 
 * 	- 
 * 
 * Query `[0, 3]` → Substring `"0100"` → Augmented to `"101001"`
 * 
 * 	Choose `"0100"`, convert `"0100"` → `"0000"` → `"1111"`.
 * 
 * 	The final string without augmentation is `"1111"`. The maximum number of active sections is 4.
 * 
 * 	- 
 * 
 * Query `[0, 2]` → Substring `"010"` → Augmented to `"10101"`
 * 
 * 	Choose `"010"`, convert `"010"` → `"000"` → `"111"`.
 * 
 * 	The final string without augmentation is `"1110"`. The maximum number of active sections is 3.
 * 
 * 	- 
 * 
 * Query `[1, 3]` → Substring `"100"` → Augmented to `"11001"`
 * 
 * 	Because there is no block of `'1'`s surrounded by `'0'`s, no valid trade is possible. The maximum number of active sections is 1.
 * 
 * 	- 
 * 
 * Query `[2, 3]` → Substring `"00"` → Augmented to `"1001"`
 * 
 * 	Because there is no block of `'1'`s surrounded by `'0'`s, no valid trade is possible. The maximum number of active sections is 1.
 * 
 * Example 3:**
 * 
 * **Input:** s = "1000100", queries = [[1,5],[0,6],[0,4]]
 * 
 * **Output:** [6,7,2]
 * 
 * **Explanation:**
 * 
 * 	Query `[1, 5]` → Substring "00010"` → Augmented to "1000101"`
 * 	Choose "00010"`, convert "00010"` → "00000"` → "11111"`.
 * 
 * 	The final string without augmentation is "1111110"`. The maximum number of active sections is 6.
 * 
 * 	Query `[0, 6]` → Substring "1000100"` → Augmented to "110001001"`
 * 	Choose "000100"`, convert "000100"` → "000000"` → "111111"`.
 * 
 * 	The final string without augmentation is "1111111"`. The maximum number of active sections is 7.
 * 
 * 	Query `[0, 4]` → Substring "10001"` → Augmented to "1100011"`
 * 	Because there is no block of `'1'`s surrounded by `'0'`s, no valid trade is possible. The maximum number of active sections is 2.
 * 
 * Example 4:**
 * 
 * **Input:** s = "01010", queries = [[0,3],[1,4],[1,3]]
 * 
 * **Output:** [4,4,2]
 * 
 * **Explanation:**
 * 
 * 	- 
 * 
 * Query `[0, 3]` → Substring `"0101"` → Augmented to `"101011"`
 * 
 * 	Choose `"010"`, convert `"010"` → `"000"` → `"111"`.
 * 
 * 	The final string without augmentation is `"11110"`. The maximum number of active sections is 4.
 * 
 * 	- 
 * 
 * Query `[1, 4]` → Substring `"1010"` → Augmented to `"110101"`
 * 
 * 	Choose `"010"`, convert `"010"` → `"000"` → `"111"`.
 * 
 * 	The final string without augmentation is `"01111"`. The maximum number of active sections is 4.
 * 
 * 	- 
 * 
 * Query `[1, 3]` → Substring `"101"` → Augmented to `"11011"`
 * 
 * 	Because there is no block of `'1'`s surrounded by `'0'`s, no valid trade is possible. The maximum number of active sections is 2.
 * 
 * **Constraints:**
 * 
 * 	- `1 <= n == s.length <= 105`
 * 
 * 	- `1 <= queries.length <= 105`
 * 
 * 	- `s[i]` is either `'0'` or `'1'`.
 * 
 * 	- `queries[i] = [li, ri]`
 * 
 * 	- `0 <= li <= ri < n`
 */

// Time:  O(nlogn + q)
// Space: O(nlogn)

// sparse table
class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(const string& s, vector<vector<int>>& queries) {
        int cnt1 = 0;
        vector<pair<int, int>> idxs;
        vector<int> lookup(size(s));
        for (int i = 0; i < size(s); ++i) {
            if (s[i] == '0') {
                if (i - 1 >= 0 && s[i - 1] == '0') {
                    ++idxs.back().second;
                } else {
                    idxs.emplace_back(i, 1);
                }
            } else {
                ++cnt1;
            }
            lookup[i] = size(idxs) - 1;
        }
        if (empty(idxs)) {
            return vector<int>(size(queries), cnt1);
        }        
        vector<int> arr(idxs.size() - 1);
        for (int i = 0; i + 1 < idxs.size();  ++i) {
            arr[i] = idxs[i].second + idxs[i + 1].second;
        }
        SparseTable st(arr, [](int a, int b) { return max(a, b); });
        vector<int> result(size(queries), cnt1);
        for (int i = 0; i < size(queries); ++i) {
            const int l = queries[i][0], r = queries[i][1];
            const int left = lookup[l] + 1, right = lookup[r] - (s[r] == '0' ? 1 : 0);
            const int left_cnt = lookup[l] != -1 ? idxs[lookup[l]].second - (l - idxs[lookup[l]].first) : -1;
            const int right_cnt = lookup[r] != -1 ? r - idxs[lookup[r]].first + 1 : -1;
            if (left <= right - 1) {
                result[i] = max(result[i], cnt1 + st.query(left, right - 1));
            }
            if (s[l] == '0' && s[r] == '0' && lookup[l] + 1 == lookup[r]) {
                result[i] = max(result[i], cnt1 + left_cnt + right_cnt);
            }
            if (s[l] == '0' && lookup[l] + 1 <= right) {
                result[i] = max(result[i], cnt1 + left_cnt + idxs[lookup[l] + 1].second);
            }
            if (s[r] == '0' && left <= lookup[r] - 1) {
                result[i] = max(result[i], cnt1 + right_cnt + idxs[lookup[r] - 1].second);
            }
        }
        return result;
    }

private:
    // Reference: https://cp-algorithms.com/data_structures/sparse-table.html
    class SparseTable {
    public:
        SparseTable(const vector<int>& arr, function<int (int, int)> fn)
         :  fn(fn) {  // Time: O(nlogn) * O(fn) = O(nlogn * 1), Space: O(nlogn)
            const int n = size(arr);
            const int k = __lg(n);
            bit_length.assign(1, 0);
            for (int i = 0; i <= k; ++i) {
                const int cnt = min(1 << i, (n + 1) - static_cast<int>(size(bit_length)));
                for (int _ = 0; _ < cnt; ++_) {
                    bit_length.emplace_back(i + 1);
                }
            }
            st.assign(k + 1, vector<int>(n));
            if (empty(st)) {
                return;
            }
            st[0].assign(cbegin(arr), cend(arr));
            for (int i = 1; i <= k; ++i) {
                for (int j = 0; j + (1 << i) <= n; ++j) {
                    st[i][j] = fn(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
                }
            }
         }

        int query(int L, int R) const {
            const int i = bit_length[R - L + 1] - 1;
            return fn(st[i][L], st[i][R - (1 << i) + 1]);  // Time: O(fn) = O(1)
        }

    private:
        vector<vector<int>> st;
        const function<int (int, int)>& fn;
        vector<int> bit_length;
    };
};
