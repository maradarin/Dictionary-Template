#ifndef _KEYCOMP_H_
#define _KEYCOMP_H_
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename K>
class KeyComp
{
public:
    int operator() (const K &key1, const K &key2) const
    {
        if(key1<key2)
            return true;
        else
            return false;
    }
};

template <>
class KeyComp<string>
{
public:
    bool operator() (const string &key1, const string &key2) const
    {
        int n = min(key1.length(), key2.length());
        if(n%2==0)
            n=n/2;
        else
            n=n/2+1;
		if (key1.substr(0, n) > key2.substr(0, n))
			return true;
		else
			return false;
    }
};

#endif // _KEYCOMP_H_

