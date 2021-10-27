/*
Problem: https://codeforces.com/problemset/problem/977/E

General idea:
    Use DSU during edge addition to merge vertices to connected components.
    Component forms a cycle if Euler tour condition is satisfied (all vertices have even degree).
*/

#include <iostream>
using namespace std;

//odds - number of odd degree vertices in component
//adj - number of adjacent vertices
struct node
{
    int odds=0, adj=0, rank=0, parent;
};

int find(node * tab,int i)
{
    if (tab[i].parent==i)
        return i;
    else
        return tab[i].parent= find(tab,tab[i].parent);
}

void Union (node * tab, int a ,int b, int &cycles)
{
    int pr_a, pr_b;
    pr_a=find(tab,a);
    pr_b=find(tab,b);

    //increase number of a`s neighbours. If it is even now, check if it`s component have no left odd
    //vertices. If so, increment cycle counter.
    //If a`s degree is odd now, decrease cycle counter (unless it`s first vertex added to that edge)
    tab[a].adj++;
    if (tab[a].adj%2==0)
    {
        if (--tab[pr_a].odds==0)
            cycles++;
    }
    else
        if (tab[pr_a].odds++==0 && tab[a].adj!=1)
            cycles--;

    //same for b
    tab[b].adj++;
    if (tab[b].adj%2==0)
    {
        if (--tab[pr_b].odds==0)
            cycles++;
    }
    else
        if (tab[pr_b].odds++==0 && tab[b].adj!=1)
            cycles--;

    if (tab[pr_a].rank < tab[pr_b].rank)
    {
        tab[pr_a].parent=pr_b;
        tab[pr_b].odds+=tab[pr_a].odds;
    }
    else
    {
        tab[pr_b].parent=pr_a;
        tab[pr_a].odds+=tab[pr_b].odds;

        if (tab[pr_a].rank==tab[pr_b].rank)
            tab[pr_a].rank++;
    }
}

int main ()
{
    ios_base::sync_with_stdio(false);
    int v,e, u,w;
    cin >> v >> e;

    node tab[v+1];
    for (int i=1;i<=v;i++)
        tab[i].parent=i;

    int cycles=0;
    for (int i=0;i<e;i++)
    {
        cin >> u >> w;
        Union(tab,u,w,cycles);
    }
    cout << cycles;
}
