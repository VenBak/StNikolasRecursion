#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

struct Gifts
{
    int price;
    string name;
};

struct Slice
{
    int from;   // from >= 0
    int length; // length >= 0
};

Slice make_slice(int from, int length)
{ // Precondition:
    assert(from >= 0 && length >= 0);
    /*  post-condition:
        return slice with given from and length
    */
    Slice s = {from, length};
    return s;
}

Slice make_slice(const vector<int> &data)
{ // Precondition:
    assert(true);
    /*  Postcondition:
        returns the slice for the entire vector data.
    */
    Slice s = {0, static_cast<int>(ssize(data))};
    return s;
}

bool valid_slice(Slice s)
{ // Precondition:
    assert(true);
    /*  Postcondition:
        returns true only if all selector values of s are not negative.
    */
    return 0 <= s.from && 0 <= s.length;
}
bool valid_slice(const vector<int> &data, Slice s)
{ // Precondition:
    assert(true);
    /*  Postcondition:
        returns true only if s is a valid slice for data
    */
    return valid_slice(s) && s.from + s.length <= ssize(data);
}

int first(Slice s)
{ // Precondition:
    assert(valid_slice(s));
    /*  Postcondition:
        result is index of first element in s (s.from)
    */
    return s.from;
}

int last(Slice s)
{ // Precondition:
    assert(valid_slice(s));
    /*  Postcondition:
        result is index of last element in s (s.from + s.length - 1)
    */
    return s.from + s.length - 1;
}

int sum(const vector<int> &money)
/* Postcondition: return sum of coins in ‘money‘ */
{
    assert(true);
    int s = 0;
    int end = ssize(money) - 1;
    int su = 0;
    while (s <= end)
    {
        su = su + money.at(s);
    }
    return su;
}

int sum(const vector<int> &money, int from)
/* Postcondition: Return sum of coins in ‘money.at (from)‘ ... ‘money.at (ssize (money)-1)‘ */
{
    assert(from < ssize(money));
    int s = from;
    int end = ssize(money) - 1;
    int su = 0;
    while (s <= end)
    {
        su = su + money.at(s);
    }
    return su;
}

int minimum(const vector<int> &money, int from)
/* Postcondition: Return minimum of ‘money.at (from)‘ ... ‘money.at (ssize (money)-1)‘ */
{
    assert(from < ssize(money));
    int s = 1;
    int end = ssize(money) - 1;
    int mn = money.at(0);
    while (s <= end)
    {
        if (mn > money.at(s))
            mn = money.at(s);
    }
    return mn;
}

void show(vector<int> &cur)
{
    for (int i = 0; i < ssize(cur); i++)
        cout << cur.at(i) << " ";
    cout << endl;
}

void show(vector<string> &cur)
{
    for (int i = 0; i < ssize(cur); i++)
        cout << cur.at(i) << " ";
    cout << endl;
}

void show(vector<Gifts> &cur)
{
    for (int i = 0; i < ssize(cur); i++)
    {
        cout << cur.at(i).price << " " << cur.at(i).name;
        cout << endl;
    }
    cout << endl;
}

int gifts(vector<int> &cur, const vector<int> &m, int c, int t)
{
    // Precondition
    // assert(valid(m) && 0 <= c && c <= ssize(m) &&
    //        match_coins(cur, make_slice(cur), m, make_slice(0, c)));
    /* Postcondition: Result is the number of ways of creating target ‘t‘ with coin
    collection ‘m.at (c)‘ ... ‘m.at (ssize (m)-1)‘ and these results are printed with
    ‘cur‘ in front of them. */

    if (t == 0)
    {
        show(cur);
        return 1;
    }
    else if (t < 0)
    {
        return 0;
    }
    else if (c >= ssize(m))
    {
        return 0;
    }
    else if (sum(m, c) < t)
    {
        return 0;
    }
    else if (minimum(m, c) > t)
    {
        return 0;
    }
    else
    {
        cur.push_back(m.at(c));
        int with_c = gifts(cur, m, c + 1, t - m.at(c));
        cur.pop_back();
        int without_c = gifts(cur, m, c + 1, t);
        return with_c + without_c;
    }
}

// bool bin_search (El el, El data [], int low, int up)
//  {
//  // Precondition:
// assert (0 <= low && 0 <= up);
// // Postcondition:
// // result is only true iff el is in data[low] .. data[up]

//  if (low > up)
//  return false;
// else
//  {
//  const int MIDDLE = low + (up - low)/2;
//  if (el == data[MIDDLE])
//  return true;
// else if (el < data[MIDDLE])
//  return bin_search (el, data, low, MIDDLE - 1);
//  else
//  return bin_search (el, data, MIDDLE + 1, up);
//  }
// }

#ifndef TESTING
int main()
{ // Precondition:
    assert(true);
    /*  Postcondition: the gift store has been loaded, and the optimal gift lists of each name
        (Andrew ... Fabienne) has been computed and printed to `cout`
    */

    vector<Gifts> wlist = {};
    vector<Gifts> gift = {};
    cout << "enter a file name";
    string file_name;
    cin >> file_name;
    int budget;

    ifstream file_list(file_name);
    ifstream file_store("giftstore.txt");

    if (!file_list.is_open())
        cout << "error not open list";
    if (!file_store.is_open())
        cout << "error not open store";

    while (!file_store.fail())
    {
        int price;
        string name;
        Gifts temporary;
        file_store >> temporary.price;
        file_store.ignore();
        getline(file_store, temporary.name);
        if (!file_store.fail())
            gift.push_back(temporary);
    }
    show(gift);

    Gifts temporary;

    file_list >> budget;
    file_list.ignore();
    while (!file_list.fail())
    {
        string line;

        getline(file_list, line);
        Gifts temporary;
        temporary.name = line;
        for (int i = 0; i < ssize(gift); i++)
        {
            if (gift.at(i).name == temporary.name)
                temporary.price = gift.at(i).price;
        }
        if (!file_list.fail())
            wlist.push_back(temporary);
    }
    show(wlist);

    // cout<<gifts(cur,m,0,T)<<" ";

    return 0;
}
#endif