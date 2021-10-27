/*
Problem: https://codeforces.com/problemset/problem/1556/E

General idea:
	Subtract second array from the first one. In the resulting array, negative number means that array n. 1 had smaller value that array n. 2 and vice versa.
	For any sequence to be valid, following conditions must be met in the resulting array:
		- sequence sums to 0
		- there cannot be a prefix with positive sum.
		- there cannot be a suffix with negative sum.
	The total number of balancing operations is equal to the maximum absolute value of any consecutive subsequence in the array.
	Sparse table with custom combiner function can be used to quickly compute anser for each segment.
*/

#include <iostream>
#include <algorithm>
 
using namespace std;
 
struct node
{
    node(){}
    node(long long val)
    {
        sum = left_min = left_max = right_max = right_min = val;
        max_abs_val = abs(val);
 
        if (val > 0)
            left_min = right_min = 0;
        else if (val < 0)
            left_max = right_max = 0;
    }
 
    long long sum, left_min, left_max, right_min, right_max, max_abs_val;
};
 
const int MAXN = 1e5;
const int K = 17;
 
node st[MAXN][K + 1];
 
void combine(node& a, node& b, node& c)
{
    c.sum = a.sum + b.sum;
 
    c.left_min = min(a.left_min, a.sum + b.left_min);
    c.left_max = max(a.left_max, a.sum + b.left_max);
 
    c.right_min = min(b.right_min, b.sum + a.right_min);
    c.right_max = max(b.right_max, b.sum + a.right_max);
 
    c.max_abs_val = max({abs(c.left_min), abs(c.left_max), abs(c.right_min), abs(c.right_max),
                         a.max_abs_val, b.max_abs_val});
}
 
int main()
{
    ios_base::sync_with_stdio(false);
 
    int n, q, x;
    cin >> n >> q;
 
    int arr[n];
 
    for (int i=0; i<n; ++i)
        cin >> arr[i];
 
    for (int i=0; i<n; ++i)
    {
        cin >> x;
        st[i][0] = node(arr[i] - x);
    }
 
    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            combine(st[i][j-1], st[i + (1 << (j - 1))][j - 1], st[i][j]);
 
    int l, r;
    while (q--)
    {
        cin >> l >> r;
        --l, --r;
 
        bool first = true;
        pair<node, node> res;
 
        for (int j = K; j >= 0; j--)
        {
            if ((1 << j) <= r - l + 1)
            {
                if (first)
                {
                    first = false;
                    res.first = st[l][j];
                }
                else
                {
                    combine(res.first, st[l][j], res.second);
                    swap(res.first, res.second);
                }
 
                l += 1 << j;
            }
        }
 
        if (res.first.sum==0 && res.first.left_max <= 0 && res.first.right_min >= 0)
            cout << res.first.max_abs_val << endl;
        else
            cout << -1 << endl;
    }
}