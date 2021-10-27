/*
Problem: https://codeforces.com/contest/1559/problem/D1

General idea:
	Use separate DSU structure for each forest. Add new edges that connect different componets in bots DSU`s until
	the bigger of them forms a spanning tree.
*/

#include <iostream>
#include <list>
#include <map>
#include <vector>
 
#define pii pair<int,int>
 
using namespace std;
 
struct Node
{
    int rank = 0;
    int parent = -1;
};
 
int find(Node* dsu, int p)
{
    if (dsu[p].parent == -1)
        return p;
 
    return dsu[p].parent = find(dsu, dsu[p].parent);
}
 
void merge(Node* dsu, int p, int q)
{
    p = find(dsu, p);
    q = find(dsu, q);
 
    if (p != q)
    {
        if (dsu[p].rank < dsu[q].rank)
            dsu[p].parent = q;
        else
        {
            dsu[q].parent = p;
            if (dsu[p].rank == dsu[q].rank)
                ++dsu[p].rank;
        }
    }
}
 
list<pii> solve(Node* big_dsu, Node* small_dsu, int m_max, int n)
{
    list<pii> result;
    int pi_big, pj_big, pi_small, pj_small;
    bool done = false;
 
    for (int i=1; i<=n and !done; ++i)
        for(int j=i+1; j<=n; ++j)
        {
            if (m_max == n - 1)
            {
                done = true;
                break;
            }
 
            pi_big = find(big_dsu, i);
            pj_big = find(big_dsu, j);
            pi_small = find(small_dsu, i);
            pj_small = find(small_dsu, j);
 
            if (pi_big != pj_big && pi_small != pj_small)
            {
                merge(big_dsu, i, j);
                merge(small_dsu, i, j);
                result.push_back({i, j});
                ++m_max;
            }
        }
 
    return result;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
 
    int n, m1, m2, u, v;
    cin >> n >> m1 >> m2;
 
    Node* dsu1 = new Node[n + 1];
    Node* dsu2 = new Node[n + 1];
 
    Node* big_dsu = dsu1;
    Node* small_dsu = dsu2;
    int m_max = m1;
    if (m2 > m1)
    {
        swap(big_dsu, small_dsu);
        m_max = m2;
    }
 
    while(m1--)
    {
        cin >> u >> v;
        merge(dsu1, u, v);
    }
    while(m2--)
    {
        cin >> u >> v;
        merge(dsu2, u, v);
    }
 
    cout << n - m_max - 1 << endl;
    list<pii> result = solve(big_dsu, small_dsu, m_max, n);
    for (pii& elem: result)
        cout << elem.first << ' ' << elem.second << endl;
}