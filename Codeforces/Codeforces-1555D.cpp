/*
Problem: https://codeforces.com/problemset/problem/1555/D

General idea:
	For each substring to not be a palindrome, each substring of length 3 must consist of distinct characters.
	Therefore, any character is induced by two previous characters. Start with 6 distinct pairs of characters that string can start with.
	In each step, induce third letter and check if new character differs from the character in given string 's'. If it does, increment modification counter.
	As answer, return modification counter with lowest value amongst 6 precalculated strings.
*/

#include <iostream>
#include <string>
 
using namespace std;
 
int** s_n_t_p(int n, string& s)
{
    string pairs[6] = {"ab", "ac", "ba", "bc", "ca", "cb"};
    int nexts[6] = {3, 5, 1, 4, 0, 2};
    int currents[6] = {0, 1, 2, 3, 4, 5};
    int accum[6] = {0, 0, 0, 0, 0, 0};
 
    int** dp = new int* [n + 1];
    for (int i=0; i<=n; ++i)
    {
        dp[i] = new int[6];
        for (int j=0; j<6; ++j)
            dp[i][j] = 0;
    }
 
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<6; ++j)
        {
            int id = currents[j];
 
            if (pairs[id][1] != s[i])
                ++accum[j];
            dp[i + 1][j] = accum[j];
 
            currents[j] = nexts[id];
        }
    }
 
    return dp;
}
 
int main() {
    ios_base::sync_with_stdio(false);
 
 
    int n, m, start, end, curr, best;
    int *ret_start, *ret_end;
    string s;
 
    cin >> n >> m;
    cin >> s;
 
    int** lookup = s_n_t_p(n, s);
    for (int i=0; i<m; ++i)
    {
        cin >> start >> end;
        ret_start = lookup[start - 1];
        ret_end = lookup[end];
 
        best = *ret_end - *ret_start;
        ++ret_start;
        ++ret_end;
        for (int j=0; j<5; ++j, ++ret_start, ++ret_end)
        {
            curr = *ret_end - *ret_start;
            if (curr < best)
                best = curr;
        }
 
        cout << best << endl;
    }
}