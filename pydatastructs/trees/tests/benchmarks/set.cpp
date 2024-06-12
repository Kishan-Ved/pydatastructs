#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    clock_t time_req;

    map<long long int, long long int> s;

    // stores time in t1
    time_req = clock();

    for (int i = -100000; i < 100000; i++)
    {
        s[i] = i;
    }

    time_req = clock() - time_req;
    cout << (float)time_req / CLOCKS_PER_SEC << endl;

    time_req = clock();

    for (int i = -100000; i < 100000; i++)
    {
        s.find(i);
    }

    time_req = clock() - time_req;
    cout << (float)time_req / CLOCKS_PER_SEC << endl;

    time_req = clock();

    for (int i = -100000; i < 100000; i++)
    {
        s.erase(i);
    }

    time_req = clock() - time_req;
    cout << (float)time_req / CLOCKS_PER_SEC << endl;

    return 0;
}