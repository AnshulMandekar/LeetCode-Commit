// Date: 2026-08-14
// Problem: Maximum Length Substring With Two Occurrences
// Difficulty: Easy
// URL: https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/

/*
 * Description:
 * Given a string `s`, return the **maximum** length of a substring such that it contains *at most two occurrences* of each character.
 * 
 * Example 1:**
 * 
 * **Input:** s = "bcbbbcba"
 * 
 * **Output:** 4
 * 
 * **Explanation:**
 * 
 * The following substring has a length of 4 and contains at most two occurrences of each character: `"bcbbbcba"`.
 * 
 * Example 2:**
 * 
 * **Input:** s = "aaaa"
 * 
 * **Output:** 2
 * 
 * **Explanation:**
 * 
 * The following substring has a length of 2 and contains at most two occurrences of each character: `"aaaa"`.
 * 
 * **Constraints:**
 * 
 * 	- `2 <= s.length <= 100`
 * 
 * 	- `s` consists only of lowercase English letters.
 */

// Time:  O(n + 26)
// Space: O(26)

// freq table, sliding window, two pointers
class Solution {
public:
    int maximumLengthSubstring(string s) {
        static const int COUNT = 2;

        int result = 0;
        vector<int> cnt(26);
        int right = 0, left = 0;
        for (int invalid_cnt = 0; right < size(s); ++right) {
            if (cnt[s[right] - 'a'] == COUNT) {
                ++invalid_cnt;
            }
            ++cnt[s[right] - 'a'];
            if (invalid_cnt) {
                --cnt[s[left] - 'a'];
                if (cnt[s[left++] - 'a'] == COUNT) {
                    --invalid_cnt;
                }
            }
        }
        return right - left;
    }
};

// Time:  O(n + 26)
// Space: O(26)
// freq table, sliding window, two pointers
class Solution2 {
public:
    int maximumLengthSubstring(string s) {
        static const int COUNT = 2;

        int result = 0;
        vector<int> cnt(26);
        for (int right = 0, left = 0; right < size(s); ++right) {
            ++cnt[s[right] - 'a'];
            while (cnt[s[right] - 'a'] > COUNT) {
                --cnt[s[left++] - 'a'];
            }
            result = max(result, right - left + 1);
        }
        return result;
    }
};
