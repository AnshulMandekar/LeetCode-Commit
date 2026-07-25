// Date: 2026-07-25
// Problem: Maximum Product of Two Digits
// Difficulty: Easy
// URL: https://leetcode.com/problems/maximum-product-of-two-digits/

/*
 * Description:
 * You are given a positive integer `n`.
 * 
 * Return the **maximum** product of any two digits in `n`.
 * 
 * **Note:** You may use the **same** digit twice if it appears more than once in `n`.
 * 
 * Example 1:**
 * 
 * **Input:** n = 31
 * 
 * **Output:** 3
 * 
 * **Explanation:**
 * 
 * 	- The digits of `n` are `[3, 1]`.
 * 
 * 	- The possible products of any two digits are: `3 * 1 = 3`.
 * 
 * 	- The maximum product is 3.
 * 
 * Example 2:**
 * 
 * **Input:** n = 22
 * 
 * **Output:** 4
 * 
 * **Explanation:**
 * 
 * 	- The digits of `n` are `[2, 2]`.
 * 
 * 	- The possible products of any two digits are: `2 * 2 = 4`.
 * 
 * 	- The maximum product is 4.
 * 
 * Example 3:**
 * 
 * **Input:** n = 124
 * 
 * **Output:** 8
 * 
 * **Explanation:**
 * 
 * 	- The digits of `n` are `[1, 2, 4]`.
 * 
 * 	- The possible products of any two digits are: `1 * 2 = 2`, `1 * 4 = 4`, `2 * 4 = 8`.
 * 
 * 	- The maximum product is 8.
 * 
 * **Constraints:**
 * 
 * 	- `10 <= n <= 109`
 */

// Time:  O(d + 10)
// Space: O(10)

// freq table, greedy
class Solution {
public:
    int maxProduct(int n) {
        static const int MAX_COUNT = 2;
        const auto& count = [](int n) {
            vector<int> cnt(10);
            for (; n; n /= 10) {
                ++cnt[n % 10];
            }
            return cnt;
        };

        auto cnt = count(n);
        int result = 1;
        for (int d = 9, c = MAX_COUNT; d >= 0; --d) {
            if (c == 0) {
                break;
            }
            for (; cnt[d]; --cnt[d]) {
                if (c == 0) {
                    break;
                }
                --c;
                result *= d;
            }
        }
        return result;
    }
};
