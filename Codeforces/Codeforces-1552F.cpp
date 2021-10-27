/*
Problem: https://codeforces.com/problemset/problem/1552/F

General idea:
    Observation: when reaching portal x_j, all portals x_i where i < j must have been previously armed (all are active now). 
	Therefore, if portal x_j teleports to coordinate x_k, the cost of crossing x_j is equal to: cost[j] = (x_j - x_k) + cost[i] for each i in range (k, j).
	Use two arrays:
		- sums: cumulative sum of using portals (sums[i] = cost[0] + cost[1] + ... + cost[i]), for quick computation of using portals in range any range (k, j)
		- ids: locations of portals(ids[j] = location of portal j)
	Process portals from left to right, and when adding new portal 'j' teleporting to 'k', use binary search on 'ids' array to find which portals should be included in cost[j],
	and use 'sums' to compute cumulative cost of using portals in range (lower_bound[k], j).
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
const int MOD = 998244353;
 
int main()
{
    int n, l, r, a, x_max;
    unsigned long long sum = 0;
    cin >> n;
 
    vector<int> ids(n+1);
    vector<unsigned long long> sums(n+1);
    for (int i=1; i<=n; ++i)
    {
        cin >> r >> l >> a;
        ids[i] = x_max = r;
        int lb = lower_bound(ids.begin(), ids.begin() + i + 1, l) - ids.begin();
        sums[i] = (MOD + 2 * sums[i-1] - sums[lb-1] + r - l) % MOD;
 
        if (a)
            sum = (MOD + sum + sums[i] - sums[i-1]) % MOD;
    }
    cout << (MOD + sum + x_max + 1) % MOD;
}