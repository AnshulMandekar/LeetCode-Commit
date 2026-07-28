// Date: 2026-07-28
// Problem: Smallest Palindromic Rearrangement I
// Difficulty: Medium
// URL: https://leetcode.com/problems/smallest-palindromic-rearrangement-i/

/*
 * Description:
 * You are given a **palindromic** string `s`.
 * 
 * Return the **lexicographically smallest** palindromic permutation of `s`.
 * 
 * Example 1:**
 * 
 * **Input:** s = "z"
 * 
 * **Output:** "z"
 * 
 * **Explanation:**
 * 
 * A string of only one character is already the lexicographically smallest palindrome.
 * 
 * Example 2:**
 * 
 * **Input:** s = "babab"
 * 
 * **Output:** "abbba"
 * 
 * **Explanation:**
 * 
 * Rearranging `"babab"` → `"abbba"` gives the smallest lexicographic palindrome.
 * 
 * Example 3:**
 * 
 * **Input:** s = "daccad"
 * 
 * **Output:** "acddca"
 * 
 * **Explanation:**
 * 
 * Rearranging `"daccad"` → `"acddca"` gives the smallest lexicographic palindrome.
 * 
 * **Constraints:**
 * 
 * 	- `1 <= s.length <= 105`
 * 
 * 	- `s` consists of lowercase English letters.
 * 
 * 	- `s` is guaranteed to be palindromic.
 */

// Time:  O(n + 26)
// Space: O(26)

// freq table, counting sort, greedy
class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> cnt(26);
        for (int i = 0; i < size(s) / 2; ++i) {
            ++cnt[s[i] - 'a'];
        }
        string result(size(s), 0);
        int l = 0;
        for (int i = 0; i < size(cnt); ++i) {
            for (int _ = 0; _ < cnt[i]; ++_) {
                result[l++] = 'a' + i;
            }
        }
        if (size(s) % 2) {
            result[l++] = s[size(s) / 2];
        }
        for (int i = l - 1 - size(s) % 2; i >= 0; --i) {
            result[l++] = result[i];
        }
        return result;
    }
};
