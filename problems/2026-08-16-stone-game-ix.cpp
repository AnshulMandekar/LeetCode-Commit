// Date: 2026-08-16
// Problem: Stone Game IX
// Difficulty: Medium
// URL: https://leetcode.com/problems/stone-game-ix/

/*
 * Description:
 * Alice and Bob continue their games with stones. There is a row of n stones, and each stone has an associated value. You are given an integer array `stones`, where `stones[i]` is the **value** of the `ith` stone.
 * 
 * Alice and Bob take turns, with **Alice** starting first. On each turn, the player may remove any stone from `stones`. The player who removes a stone **loses** if the **sum** of the values of **all removed stones** is divisible by `3`. Bob will win automatically if there are no remaining stones (even if it is Alice's turn).
 * 
 * Assuming both players play **optimally**, return `true` *if Alice wins and* `false` *if Bob wins*.
 * 
 * Example 1:**
 * 
 * **Input:** stones = [2,1]
 * **Output:** true
 * **Explanation:** The game will be played as follows:
 * - Turn 1: Alice can remove either stone.
 * - Turn 2: Bob removes the remaining stone. 
 * The sum of the removed stones is 1 + 2 = 3 and is divisible by 3. Therefore, Bob loses and Alice wins the game.
 * 
 * Example 2:**
 * 
 * **Input:** stones = [2]
 * **Output:** false
 * **Explanation:** Alice will remove the only stone, and the sum of the values on the removed stones is 2. 
 * Since all the stones are removed and the sum of values is not divisible by 3, Bob wins the game.
 * 
 * Example 3:**
 * 
 * **Input:** stones = [5,1,2,4,3]
 * **Output:** false
 * **Explanation:** Bob will always win. One possible way for Bob to win is shown below:
 * - Turn 1: Alice can remove the second stone with value 1. Sum of removed stones = 1.
 * - Turn 2: Bob removes the fifth stone with value 3. Sum of removed stones = 1 + 3 = 4.
 * - Turn 3: Alices removes the fourth stone with value 4. Sum of removed stones = 1 + 3 + 4 = 8.
 * - Turn 4: Bob removes the third stone with value 2. Sum of removed stones = 1 + 3 + 4 + 2 = 10.
 * - Turn 5: Alice removes the first stone with value 5. Sum of removed stones = 1 + 3 + 4 + 2 + 5 = 15.
 * Alice loses the game because the sum of the removed stones (15) is divisible by 3. Bob wins the game.
 * 
 * **Constraints:**
 * 
 * 	- `1 <= stones.length <= 105`
 * 
 * 	- `1 <= stones[i] <= 104`
 */

// Time:  O(n)
// Space: O(1)

class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        unordered_map<int, int> count;
        for (const auto& x : stones) {
            ++count[x % 3];
        }
        if (count[0] % 2 == 0) {
            // iff both counts are not zero, then alice takes the least one at first, the remains are deterministic for bob to lose:
            // - assumed count[1] is the least one:
            //   1(,1,2)*,2,(,2)* => bob loses
            //            ^
            // - assumed count[2] is the least one:
            //   2(,2,1)*,1,(,1)* => bob loses
            //            ^
            return count[1] && count[2];
        }
        // iff abs(count[1]-count[2]) >= 3, then alice takes the most one at first, the remains are deterministic for bob to lose:
        // - assumed count[1] is the most one
        //   1(,1,2)*,0,1(,2,1)*,1,(,1)* => bob loses
        //                       ^
        //   1(,1,2)*,1,0,1,(,1)* => bob loses
        //                ^
        // - assumed count[2] is the most one
        //   2(,2,1)*,0,2(,1,2)*,2,(,2)* => bob loses
        //                       ^
        //   2(,2,1)*,2,0,2,(,2)* => bob loses
        //                ^
        return abs(count[1] - count[2]) >= 3;
    }
};
