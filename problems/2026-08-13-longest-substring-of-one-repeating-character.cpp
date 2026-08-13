// Date: 2026-08-13
// Problem: Longest Substring of One Repeating Character
// Difficulty: Hard
// URL: https://leetcode.com/problems/longest-substring-of-one-repeating-character/

/*
 * Description:
 * You are given a **0-indexed** string `s`. You are also given a **0-indexed** string `queryCharacters` of length `k` and a **0-indexed** array of integer **indices** `queryIndices` of length `k`, both of which are used to describe `k` queries.
 * 
 * The `ith` query updates the character in `s` at index `queryIndices[i]` to the character `queryCharacters[i]`.
 * 
 * Return *an array* `lengths` *of length *`k`* where* `lengths[i]` *is the **length** of the **longest substring** of *`s`* consisting of **only one repeating** character **after** the* `ith` *query** is performed.*
 * 
 * Example 1:**
 * 
 * **Input:** s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
 * **Output:** [3,3,4]
 * **Explanation:** 
 * - 1st query updates s = "b**b**bacc". The longest substring consisting of one repeating character is "bbb" with length 3.
 * - 2nd query updates s = "bbb**c**cc". 
 *   The longest substring consisting of one repeating character can be "bbb" or "ccc" with length 3.
 * - 3rd query updates s = "bbb**b**cc". The longest substring consisting of one repeating character is "bbbb" with length 4.
 * Thus, we return [3,3,4].
 * 
 * Example 2:**
 * 
 * **Input:** s = "abyzz", queryCharacters = "aa", queryIndices = [2,1]
 * **Output:** [2,3]
 * **Explanation:**
 * - 1st query updates s = "ab**a**zz". The longest substring consisting of one repeating character is "zz" with length 2.
 * - 2nd query updates s = "a**a**azz". The longest substring consisting of one repeating character is "aaa" with length 3.
 * Thus, we return [2,3].
 * 
 * **Constraints:**
 * 
 * 	- `1 <= s.length <= 105`
 * 
 * 	- `s` consists of lowercase English letters.
 * 
 * 	- `k == queryCharacters.length == queryIndices.length`
 * 
 * 	- `1 <= k <= 105`
 * 
 * 	- `queryCharacters` consists of lowercase English letters.
 * 
 * 	- `0 <= queryIndices[i] < s.length`
 */

// Time:  O(nlogn)
// Space: O(n)

template <typename Node, typename T>
class SegmentTree {
 public:
    explicit SegmentTree(
        int N,
        const function<Node(const int&)>& build_fn,
        const function<Node(const T&)>& update_fn,
        const function<Node(const Node&, const Node&)>& query_fn)
      : tree(N > 1 ? 1 << (__lg(N - 1) + 2) : 2),
        base_(N > 1 ? 1 << (__lg(N - 1) + 1) : 1),
        build_fn_(build_fn),
        query_fn_(query_fn),
        update_fn_(update_fn) {

        for (int i = base_; i < base_ + N; ++i) {
            tree[i] = build_fn_(i - base_);
        }
        for (int i = base_ - 1; i >= 1; --i) {
            tree[i] = query_fn_(tree[2 * i], tree[2 * i + 1]);
        }
    }

    void update(int i, const T& h) {
        int x = base_ + i;
        tree[x] = update_fn_(h);
        while (x > 1) {
            x /= 2;
            tree[x] = query_fn_(tree[x * 2], tree[x * 2 + 1]);
        }
    }

    vector<Node> tree;

private:
    int base_;
    const function<Node(const int&)> build_fn_;
    const function<Node(const T&)> update_fn_;
    const function<Node(const Node&, const Node&)> query_fn_;
};

// segment tree
class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        struct Node {
            Node(char left = 0, char right = 0, int left_len = 0, int right_len = 0, int len = 0, int max_len = 0) 
             : left(left), right(right), left_len(left_len), right_len(right_len), len(len), max_len(max_len) {
            }

            char left;
            char right;
            int left_len;
            int right_len;
            int len;
            int max_len;
        };
        const auto& update = [] (const auto& c) {
            return Node(c, c, 1, 1, 1, 1);
        };
        const auto& build = [&s, &update] (const auto& i) {
            return update(s[i]);
        };
        const auto& query = [] (const auto& x, const auto& y) {
            if (x.len == 0) {
                return y;
            }
            if (y.len == 0) {
                return x;
            }
            return Node(x.left,
                        y.right,
                        x.left_len + ((x.left_len == x.len && x.right == y.left) ? y.left_len : 0),
                        y.right_len + ((y.right_len == y.len && y.left == x.right) ? x.right_len : 0),
                        x.len + y.len,
                        max({x.max_len, y.max_len, (x.right == y.left) ? x.right_len + y.left_len : 0}));
        };
        vector<int> result;
        SegmentTree<Node, char> st(size(s), build, update, query);
        for (int i = 0; i < size(queryCharacters); ++i) {
            st.update(queryIndices[i], queryCharacters[i]);
            result.emplace_back(st.tree[1].max_len);
        }
        return result;
    }
};

// Time:  O(nlogn)
// Space: O(n)

template <typename Node, typename T>
class SegmentTree2 {
 public:
    explicit SegmentTree2(
        int N,
        const function<Node(const int&)>& build_fn,
        const function<Node(const T&)>& update_fn,
        const function<Node(const Node&, const Node&)>& query_fn)
      : tree_(N > 1 ? 1 << (__lg(N - 1) + 2) : 2),
        base_(N > 1 ? 1 << (__lg(N - 1) + 1) : 1),
        build_fn_(build_fn),
        query_fn_(query_fn),
        update_fn_(update_fn) {

        for (int i = base_; i < base_ + N; ++i) {
            tree_[i] = build_fn_(i - base_);
        }
        for (int i = base_ - 1; i >= 1; --i) {
            tree_[i] = query_fn_(tree_[2 * i], tree_[2 * i + 1]);
        }
    }

    void update(int i, const T& h) {
        int x = base_ + i;
        tree_[x] = update_fn_(h);
        while (x > 1) {
            x /= 2;
            tree_[x] = query_fn_(tree_[x * 2], tree_[x * 2 + 1]);
        }
    }

    Node query(int L, int R) {
        Node none;
        if (L > R) {
            return none;
        }
        L += base_;
        R += base_;
        auto left = none;
        auto right = none;
        for (; L <= R; L /= 2, R /= 2) {
            if (L & 1) {
                left = query_fn_(left, tree_[L]);
                ++L;
            }
            if ((R & 1) == 0) {
                right = query_fn_(tree_[R], right);
                --R;
            }
        }
        return query_fn_(left, right);
    }

private:
    vector<Node> tree_;
    int base_;
    const function<Node(const int&)> build_fn_;
    const function<Node(const T&)> update_fn_;
    const function<Node(const Node&, const Node&)> query_fn_;
};

// segment tree
class Solution2 {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        struct Node {
            Node(char left = 0, char right = 0, int left_len = 0, int right_len = 0, int len = 0, int max_len = 0) 
             : left(left), right(right), left_len(left_len), right_len(right_len), len(len), max_len(max_len) {
            }

            char left;
            char right;
            int left_len;
            int right_len;
            int len;
            int max_len;
        };
        const auto& update = [] (const auto& c) {
            return Node(c, c, 1, 1, 1, 1);
        };
        const auto& build = [&s, &update] (const auto& i) {
            return update(s[i]);
        };
        const auto& query = [] (const auto& x, const auto& y) {
            if (x.len == 0) {
                return y;
            }
            if (y.len == 0) {
                return x;
            }
            return Node(x.left,
                        y.right,
                        x.left_len + ((x.left_len == x.len && x.right == y.left) ? y.left_len : 0),
                        y.right_len + ((y.right_len == y.len && y.left == x.right) ? x.right_len : 0),
                        x.len + y.len,
                        max({x.max_len, y.max_len, (x.right == y.left) ? x.right_len + y.left_len : 0}));
        };
        vector<int> result;
        SegmentTree2<Node, char> st(size(s), build, update, query);
        for (int i = 0; i < size(queryCharacters); ++i) {
            st.update(queryIndices[i], queryCharacters[i]);
            result.emplace_back(st.query(0, size(s) - 1).max_len);
        }
        return result;
    }
};
