# LeetCode Daily Challenge Commits

An automated repository that fetches, solves (where possible), and commits the LeetCode **Question of the Day** in C++ every day.

## How It Works
1. **Trigger:** A GitHub Actions workflow runs every day at `2:30 PM IST (09:00 UTC)` (and can also be triggered manually).
2. **Fetch:** A Python script queries the LeetCode GraphQL API to obtain the details of the active Daily Coding Challenge.
3. **Solve:** The script attempts to find a matching C++ solution from [kamyu104/LeetCode-Solutions](https://github.com/kamyu104/LeetCode-Solutions). 
   - *If found:* The solution code is saved.
   - *If not found:* The starter C++ code template is saved with a placeholder comment, so the commit still occurs.
4. **Log:** The `README.md` is automatically updated with a link to the new solution, difficulty, and status badge.
5. **Commit:** The action commits the new files and updates back to this repository automatically.

---

## Daily Progress Tracker

| Date | # | Problem Title | Difficulty | Status | Solution Link |
| :--- | :--- | :--- | :--- | :---: | :---: |
<!-- LEETCODE_LIST_START -->
| 2026-07-31 | 3016 | [Minimum Number of Pushes to Type Word II](https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/) | 🟡 Medium | ✅ Solved | [Solution](problems/2026-07-31-minimum-number-of-pushes-to-type-word-ii.cpp) |

| 2026-07-30 | 3014 | [Minimum Number of Pushes to Type Word I](https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-i/) | 🟢 Easy | ✅ Solved | [Solution](problems/2026-07-30-minimum-number-of-pushes-to-type-word-i.cpp) |

| 2026-07-29 | 3518 | [Smallest Palindromic Rearrangement II](https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/) | 🔴 Hard | ✅ Solved | [Solution](problems/2026-07-29-smallest-palindromic-rearrangement-ii.cpp) |

| 2026-07-28 | 3517 | [Smallest Palindromic Rearrangement I](https://leetcode.com/problems/smallest-palindromic-rearrangement-i/) | 🟡 Medium | ✅ Solved | [Solution](problems/2026-07-28-smallest-palindromic-rearrangement-i.cpp) |

| 2026-07-27 | 1464 | [Maximum Product of Two Elements in an Array](https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/) | 🟢 Easy | ✅ Solved | [Solution](problems/2026-07-27-maximum-product-of-two-elements-in-an-array.cpp) |

| 2026-07-26 | 628 | [Maximum Product of Three Numbers](https://leetcode.com/problems/maximum-product-of-three-numbers/) | 🟢 Easy | ✅ Solved | [Solution](problems/2026-07-26-maximum-product-of-three-numbers.cpp) |

| 2026-07-25 | 3536 | [Maximum Product of Two Digits](https://leetcode.com/problems/maximum-product-of-two-digits/) | 🟢 Easy | ✅ Solved | [Solution](problems/2026-07-25-maximum-product-of-two-digits.cpp) |

| 2026-07-24 | 3514 | [Number of Unique XOR Triplets II](https://leetcode.com/problems/number-of-unique-xor-triplets-ii/) | 🟡 Medium | ✅ Solved | [Solution](problems/2026-07-24-number-of-unique-xor-triplets-ii.cpp) |

| 2026-07-23 | 3513 | [Number of Unique XOR Triplets I](https://leetcode.com/problems/number-of-unique-xor-triplets-i/) | 🟡 Medium | ✅ Solved | [Solution](problems/2026-07-23-number-of-unique-xor-triplets-i.cpp) |

| 2026-07-22 | 3501 | [Maximize Active Section with Trade II](https://leetcode.com/problems/maximize-active-section-with-trade-ii/) | 🔴 Hard | ✅ Solved | [Solution](problems/2026-07-22-maximize-active-section-with-trade-ii.cpp) |

| 2026-07-21 | 3499 | [Maximize Active Section with Trade I](https://leetcode.com/problems/maximize-active-section-with-trade-i/) | 🟡 Medium | ✅ Solved | [Solution](problems/2026-07-21-maximize-active-section-with-trade-i.cpp) |

<!-- LEETCODE_LIST_END -->

---

## Setup Instructions

### Enable Workflow Read/Write Permissions
For GitHub Actions to be able to push the commits back to your repository:
1. Go to your repository settings on GitHub.
2. Select **Actions** > **General** on the left-hand menu.
3. Scroll down to **Workflow permissions**.
4. Select **Read and write permissions**.
5. Click **Save**.
