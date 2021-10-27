/*
Problem: https://codeforces.com/problemset/problem/1528/D

General idea:
    Iterate over all cannons and for each vertex 'u' calculate shortest arival time to vertex 'v' (being fired from 'u'), at time t0 = 0.
	Store results at dp[u][v] = arival_time. Since cannons are rotating periodically, getting from vertex 'u' to vertex 'v' at time 't' is
	the same as getting from vertex 'u' to vertex 'v - t' at time t0 (dp[u][v] at t = dp[u][v - t] at t0). Therefore, we can use 'dp' to story only values from t0.
	With 'dp' filled, we can use dijkstra algorith to find shortest paths.
*/

#include <iostream>
#include <vector>
#include <climits>
#include <queue>
 
#define pii pair<int, int>
 
using namespace std;
 
 
int main()
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
 
    int n, m;
    cin >> n >> m;
 
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX/2));
 
    int u, v, w;
    while (m--)
    {
        cin >> u >> v >> w;
        for(int i=0; i<n; ++i)
        {
            int vmod = (v + i) % n;
            dp[u][vmod] = min(dp[u][vmod], i + w);
        }
    }
 
    auto comp = [](pii a, pii b){return a.second > b.second;};
 
    for (u=0; u<n; ++u)
    {
        priority_queue<pii, vector<pii>, decltype(comp)> s(comp);
        s.push({u, 0});
        vector<int> distance(n, INT_MAX/2);
        distance[u] = 0;
 
        while (!s.empty())
        {
            pair<int, int> v_cost = s.top();
            s.pop();
 
            v = v_cost.first, w = v_cost.second;
 
            if (w != distance[v])
                continue;
 
            for (int i=0; i<n; ++i)
                if (i != v)
                {
                    int cost = dp[v][(n + (i - w) % n) % n];
                    if (distance[i] > distance[v] + cost)
                    {
                        distance[i] = distance[v] + cost;
                        s.push({i, distance[i]});
                    }
                }
        }
 
        for (int i=0; i<n; ++i)
            cout << distance[i] << " ";
        cout << endl;
    }
}