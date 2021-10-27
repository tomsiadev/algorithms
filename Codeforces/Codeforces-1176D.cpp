/*
Problem: https://codeforces.com/problemset/problem/1176/D

General Idea:
    Use Sieve of Eratosthenes to find all prime and complex numbers in given range. Use resulting 'complex' array to get list of 'prime' numbers sequence.
	Partition base array into two parts: one containing complex numbers and one containing prime numbers.
	Since transformed prime numbers add only prime numbers, but transformed complex numbers add both prime and complex numbers, process compelx numbers first.
	Each complex number adds nubmer which is smaller than given number, so process them in decreasing order. Next, process prime numbers in increasing order.
	When a number is processed, add it`s transformation to removeSet. Skip processing of numbers in removeSet.
	Result will contain every processed number (not removed).
	
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <list>
#include <set>
using namespace std;
 
typedef unsigned int ui;
 
ui greatest_div(ui x)
{
    if (x%2==0) return x/2;
    for (ui i = 3; i<=sqrt(x); i+=2)
        if (x%i==0) return x/i;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    vector <ui> b(2*N);
    for (int i=0;i<2*N;i++)
        cin >> b[i];
 
	
    ui n = 2750131 + 1;
	//Sieve
    bool * complex = (bool*) calloc(n,sizeof(bool));
    complex[1] = true;
    for (ui i=2; i<sqrt(n); i++)
        if (!complex[i])
            for (ui j=i*i; j<n; j+=i)
                complex[j]=true;
	
	//Find sequence of prime numbers
    vector <ui> primes(200000);
    ui i = 1;
    for (ui j=2; j<n; j++)
        if (!complex[j])
            primes[i++] = j;
	
	//Partition array to complex and prime numbers
    auto p = partition(b.begin(), b.end(), [&](int a){return complex[a];});
    sort (b.begin(), p);
    sort (p, b.end());
 
    list <ui> result;
    multiset <ui> removeSet;
 
    for (auto it = p-1; it>=b.begin(); it--) //process complex
    {
        auto f = removeSet.find(*it);
        if (f!=removeSet.end())
            removeSet.erase(f);
        else
        {
            result.push_back(*it);
            removeSet.insert(greatest_div(*it));
        }
    }
 
    for (auto it = p; it<b.end(); it++) //process primes
    {
        auto f = removeSet.find(*it);
        if (f!=removeSet.end())
            removeSet.erase(f);
        else
        {
            result.push_back(*it);
            removeSet.insert(primes[*it]);
        }
    }
 
    for (ui x: result)
        cout << x << endl;
 
}
