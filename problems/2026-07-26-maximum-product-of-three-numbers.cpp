// Date: 2026-07-26
// Problem: Maximum Product of Three Numbers
// Difficulty: Easy
// URL: https://leetcode.com/problems/maximum-product-of-three-numbers/

/*
 * Description:
 * Given an integer array `nums`, *find three numbers whose product is maximum and return the maximum product*.
 * 
 * Example 1:**
 * 
 * **Input:** nums = [1,2,3]
 * **Output:** 6
 * 
 * Example 2:**
 * 
 * **Input:** nums = [1,2,3,4]
 * **Output:** 24
 * 
 * Example 3:**
 * 
 * **Input:** nums = [-1,-2,-3]
 * **Output:** -6
 * 
 * **Constraints:**
 * 
 * 	- `3 <= nums.length <= 104`
 * 
 * 	- `-1000 <= nums[i] <= 1000`
 */

// Time:  O(n)
// Space: O(1)

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        auto min1 = numeric_limits<int>::max();
        auto min2 = numeric_limits<int>::max();
        auto max1 = numeric_limits<int>::min();
        auto max2 = numeric_limits<int>::min();
        auto max3 = numeric_limits<int>::min();
        for (const auto& n: nums) {
            if (n <= min1) {
                min2 = min1;
                min1 = n;
            } else if (n <= min2) {
                min2 = n;
            }
            if (n >= max1) {
                max3 = max2;
                max2 = max1;
                max1 = n;
            } else if (n >= max2) {
                max3 = max2;
                max2 = n;
            } else if (n >= max3) {
                max3 = n;
            }
        }
        return max(min1 * min2 * max1, max1 * max2 * max3);
    }
};

