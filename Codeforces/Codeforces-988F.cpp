/*
Problem: https://codeforces.com/problemset/problem/988/F

General idea:
    Mark raining cells as wet. Process array from left to right and if cell 'i' is not wet,
    then the cost(sum of carried weight) of getting there is distance[i] = distance[i-1].
    Otherwise, we will need to bring umbrella with lower total cost. Carrying umbrella can
    be expressed as linear funtion with slope being it`s weight, and intercept being it`s
    initial location.
    Use Li Chao tree to add new functions when picking umbrellas and find lowest value function (umbrella) at
    any point 'i'.
*/

#include <iostream>
#include <list>
#include <utility>
#include <cmath>
using namespace std;

typedef pair<int,int> pii;
const int INF = 1e9;


struct cell
{
    bool wet = false;
    int umbrella = INF;
    unsigned int distance;
};

//lichao tree functions
long long f(pii line, int x)
{
    return line.first * x + line.second;
}

void addline (pii * lichao, pii line, int v, int l, int r)
{
    pii curr = lichao[v];
    int m = (l+r)/2;
    bool left = f(line, l) < f(curr, l);
    bool mid = f(line, m) < f(curr, m);

    if (mid)
        swap(lichao[v], line);

    if (r-l > 1)
    {
        if (left != mid)
            addline(lichao, line, 2*v, l, m);
        else
            addline(lichao, line, 2*v+1, m, r);
    }
}

long long getmin (pii * lichao, int x, int v, int l, int r)
{
    pii curr = lichao[v];

    if (r-l == 1)
        return f(curr, x);

    int m = (l+r)/2;
    if (x < m)
        return min( f(curr,x), getmin(lichao, x, 2*v, l, m) );
    else
        return min( f(curr,x), getmin(lichao, x, 2*v+1, m, r) );
}

int main()
{
    ios_base::sync_with_stdio(false);
    int a, n, m;
    cin >> a >> n >> m;
    cell cells[a+1];

    int s = 1;
    while (s<a+1)
        s*=2;
    pii lichao[2*s];

    for (int i=0; i<2*s; i++)
    {
        lichao[i].first = 0;
        lichao[i].second = INF;
    }

    int minUmb = INF, minWet = INF, l, r;
    for (int i=0; i<n; i++)
    {
        cin >> l >> r;
        minWet = min(minWet, l+1);
        for (int j=l+1; j<=r; j++)
            cells[j].wet = true;
    }

    for (int i=0; i<m; i++)
    {
        cin >> l >> r;
        minUmb = min(minUmb, l);
        cells[l].umbrella = min(cells[l].umbrella , r);
    }

    if (minUmb >= minWet)
        cout << -1 << endl;
    else
    {
        cells[0].distance = 0;
        if (cells[0].umbrella != INF)
            addline(lichao, {cells[0].umbrella, 0}, 1, 0, s);

        for (int i=1; i<=a; i++)
        {
            if (!cells[i].wet)
                cells[i].distance = cells[i-1].distance;
            else
                cells[i].distance = getmin(lichao, i, 1, 0, s);

            if (cells[i].umbrella != INF)
            {
                pii line;
                line.first = cells[i].umbrella;
                line.second = cells[i].distance - i * line.first;
                addline(lichao, line, 1, 0, s);
            }

        }

        cout << cells[a].distance << endl;
    }
}
