// Date: 2026-08-19
// Problem: Cinema Seat Allocation
// Difficulty: Medium
// URL: https://leetcode.com/problems/cinema-seat-allocation/

/*
 * Description:
 * A cinema has `n` rows of seats, numbered from 1 to `n`. Each row has 10 seats, numbered from 1 to 10.
 * 
 * You are given a 2D integer array reservedSeats`, where reservedSeats[i] = [rowi, seati]` means that seat seati` in row rowi` is already reserved.
 * 
 * A four-person group must be assigned to four seats in the **same** row. The group can be seated in one of the following seat blocks:
 * 
 * 	- seats 2, 3, 4, 5`
 * 
 * 	- seats 4, 5, 6, 7`
 * 
 * 	- seats 6, 7, 8, 9`
 * 
 * A block can be used only if **none** of its seats are reserved. Each seat can be assigned to **at most **one group.
 * 
 * Return an integer denoting the **maximum** number of four-person groups that can be assigned.
 * 
 * Example 1:**
 * 
 * **Input:** n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
 * **Output:** 4
 * **Explanation:** The figure above shows an optimal allocation of four groups. Seats marked in blue are already reserved, and each set of four contiguous seats marked in orange is assigned to one group.
 * 
 * Example 2:**
 * 
 * **Input:** n = 2, reservedSeats = [[2,1],[1,8],[2,6]]
 * **Output:** 2
 * 
 * Example 3:**
 * 
 * **Input:** n = 4, reservedSeats = [[4,3],[1,4],[4,6],[1,7]]
 * **Output:** 4
 * 
 * **Constraints:**
 * 
 * 	- `1 <= n <= 109`
 * 
 * 	- `1 <= reservedSeats.length <= min(10 * n, 104)`
 * 
 * 	- `reservedSeats[i] == [rowi, seati]`
 * 
 * 	- `1 <= rowi <= n`
 * 
 * 	- `1 <= seati <= 10`
 * 
 * 	- All `reservedSeats[i]` are distinct.
 */

// Time:  O(n)
// Space: O(n)

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, unordered_map<int, bool>> lookup;
        for (const auto& seat : reservedSeats) {
            if (2 <= seat[1] && seat[1] <= 5) {
                lookup[seat[0]][0] = true;
            }
            if (4 <= seat[1] && seat[1] <= 7) {
                lookup[seat[0]][1] = true;
            }
            if (6 <= seat[1] && seat[1] <= 9) {
                lookup[seat[0]][2] = true;
            }
        }
        int result = 2 * n;
        for (auto& [_, reserved] : lookup) {
            if (!reserved[0] && !reserved[2]) {
                continue;
            }
            if (!reserved[0] || !reserved[1] || !reserved[2]) {
                --result;
                continue;
            }
            result -= 2;
        }
        return result;
    }
};

// Time:  O(nlogn)
// Space: O(1)
class Solution2 {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        sort(begin(reservedSeats), end(reservedSeats));
        int result = 2 * n;
        for (int i = 0; i < reservedSeats.size();) {
            unordered_map<int, bool> reserved;
            int curr = reservedSeats[i][0];
            while (i < reservedSeats.size() && reservedSeats[i][0] == curr) {
                if (2 <= reservedSeats[i][1] && reservedSeats[i][1] <= 5) {
                    reserved[0] = true;
                }
                if (4 <= reservedSeats[i][1] && reservedSeats[i][1] <= 7) {
                    reserved[1] = true;
                }
                if (6 <= reservedSeats[i][1] && reservedSeats[i][1] <= 9) {
                    reserved[2] = true;
                }
                ++i;
            }
            if (!reserved[0] && !reserved[2]) {
                continue;
            }
            if (!reserved[0] || !reserved[1] || !reserved[2]) {
                --result;
                continue;
            }
            result -= 2;
        }
        return result;
    }
};
