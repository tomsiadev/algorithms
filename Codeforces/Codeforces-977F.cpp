/*
Problem: https://codeforces.com/problemset/problem/977/F

General idea:
    Use hash map to store values key-pair, where key is number from array and value is length of
    the longest subsequence ending on that number so far.
    Process array from left to right and for each number, check if previous consecutive number
    is already in hash map and put the number with length of previous number + 1.
    Otherwise, put the number with value 1.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i=0; i<n; ++i)
        cin >> arr[i];

    map<int, int> sequence;
    int best_id = 0, best_val = 0;

    for (int i=0; i<n; ++i){

        int val = 1;
        auto it = sequence.find(arr[i] - 1);
        if (it != sequence.end())
            val = it->second + 1;
        sequence[arr[i]] = val;

        if (val > best_val){
            best_val = val;
            best_id = arr[i];
        }
    }

    cout << sequence[best_id] << endl;
    int val = best_id - sequence[best_id] + 1;
    for (int i=0; i<n; ++i)
        if (arr[i] == val){
            ++val;
            cout << i+1 << " ";
        }
}
