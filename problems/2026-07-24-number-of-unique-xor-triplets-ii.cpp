// Date: 2026-07-24
// Problem: Number of Unique XOR Triplets II
// Difficulty: Medium
// URL: https://leetcode.com/problems/number-of-unique-xor-triplets-ii/

/*
 * Description:
 * You are given an integer array `nums`.
 * 
 * A **XOR triplet** is defined as the XOR of three elements `nums[i] XOR nums[j] XOR nums[k]` where `i <= j <= k`.
 * 
 * Return the number of **unique** XOR triplet values from all possible triplets `(i, j, k)`.
 * 
 * Example 1:**
 * 
 * **Input:** nums = [1,3]
 * 
 * **Output:** 2
 * 
 * **Explanation:**
 * 
 * The possible XOR triplet values are:
 * 
 * 	`(0, 0, 0) → 1 XOR 1 XOR 1 = 1`
 * 
 * 	`(0, 0, 1) → 1 XOR 1 XOR 3 = 3`
 * 
 * 	`(0, 1, 1) → 1 XOR 3 XOR 3 = 1`
 * 
 * 	`(1, 1, 1) → 3 XOR 3 XOR 3 = 3`
 * 
 * The unique XOR values are {1, 3}`. Thus, the output is 2.
 * 
 * Example 2:**
 * 
 * **Input:** nums = [6,7,8,9]
 * 
 * **Output:** 4
 * 
 * **Explanation:**
 * 
 * The possible XOR triplet values are {6, 7, 8, 9}`. Thus, the output is 4.
 * 
 * **Constraints:**
 * 
 * 	- `1 <= nums.length <= 1500`
 * 
 * 	- `1 <= nums[i] <= 1500`
 */

// Time:  O(nlogn)
// Space: O(n)

// FWHT, fst
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const auto& bit_length = [](int64_t x) {
            return (x ? std::__lg(x) : -1) + 1;
        };

        vector<int64_t> a(1 << bit_length(ranges::max(nums)));
        for (const auto& x: nums) {
            ++a[x];
        }
        FST(a, false);
        for (int i = 0; i < size(a); i++) {
           a[i] = a[i] * a[i] * a[i];
        }
        FST(a, true);
        int result = 0;
        for (const auto& x: a) {
            if (x) {
                ++result;
            }
        }
        return result;
    }

private:
    // Template: https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastSubsetTransform.h
    void FST(auto& a, bool inv) {
        for (int n = size(a), step = 1; step < n; step <<= 1) {
            for (int i = 0; i < n; i += step << 1) {
                for (int j = i; j < i + step; ++j) {
                    auto &u = a[j], &v = a[j + step];
                    tie(u, v) = pair(u + v, u - v);  // XOR
                }
            }
        }
        if (inv) {
            for (auto& x : a) {
                x /= size(a);  // XOR only /// include-line
            }
        }
    }
};

// Time:  O(n^2)
// Space: O(n)
// hash table
class Solution2 {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const auto& bit_length = [](int64_t x) {
            return (x ? std::__lg(x) : -1) + 1;
        };

        unordered_set<int> cnt2 = {0};
        unordered_set<int> cnt3;
        const int max_cnt = 1 << bit_length(ranges::max(nums));
        for (const auto& x : nums) {
            for (const auto& y : cnt2) {
                cnt3.emplace(x ^ y);
            }
            for (const auto& y : nums) {
                cnt2.emplace(x ^ y);
            }
            if (size(cnt3) == max_cnt) {
                break;
            }
        }
        return size(cnt3);
    }
};
