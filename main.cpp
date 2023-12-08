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

int sum(vector<Gifts> &gifts)
/* Postcondition: return sum of coins in ‘money‘ */
{
    assert(true);
    int s = 0;
    int end = ssize(gifts) - 1;
    int su = 0;
    while (s <= end)
    {
        su = su + gifts.at(s).price;
        s++;
    }
    return su;
}

// int sum(const vector<int> &money, int from)
// /* Postcondition: Return sum of coins in ‘money.at (from)‘ ... ‘money.at (ssize (money)-1)‘ */
// {
//     assert(from < ssize(money));
//     int s = from;
//     int end = ssize(money) - 1;
//     int su = 0;
//     while (s <= end)
//     {
//         su = su + money.at(s);
//         s++;
//     }
//     return su;
// }

int minimum(const vector<int> &money, int from)
/* Postcondition: Return minimum of ‘money.at (from)‘ ... ‘money.at (ssize (money)-1)‘ */
{
    assert(from < ssize(money));
    int s = 0;
    int end = ssize(money) - 1;
    int mn = money.at(0);
    while (s <= end)
    {
        if (mn > money.at(s))
            mn = money.at(s);
        s++;
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

int gifts(vector<Gifts> &cur, vector<Gifts> &m, int c, int budget, vector<Gifts> &bestSolution, int &bestRemainingBudget)
{
    // Precondition:
    assert(budget >= 0 && c >= 0);
    // Postcondition:

    int currentCost = sum(cur);
    if (currentCost > budget) 
    {
        return budget; 
    }
    if (c >= ssize(m)) 
    {
        return budget;
    }

    if (currentCost <= budget && currentCost > sum(bestSolution))
    {
        bestSolution = cur;
        bestRemainingBudget = budget - currentCost;
    }

    for (int i = c; i < ssize(m); i++)
    {
        if (currentCost + m.at(i).price <= budget)
        {
            cur.push_back(m.at(i));
            gifts(cur, m, i + 1, budget, bestSolution, bestRemainingBudget);
            cur.pop_back();
        }
    }
    return bestRemainingBudget;
}


#ifndef TESTING
int main()
{ // Precondition:
    assert(true);
    /*  Postcondition: the gift store has been loaded, and the optimal gift lists of each name
        (Andrew ... Fabienne) has been computed and printed to `cout`
    */

    vector<Gifts> wlist = {};
    vector<Gifts> gift = {};
    cout << "Enter a file name: ";
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
        string name;
        Gifts temporary;
        file_store >> temporary.price;
        file_store.ignore();
        getline(file_store, temporary.name);
        if (!file_store.fail())
            gift.push_back(temporary);
    }
    // show(gift);

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
    // show(wlist);

    vector<Gifts> currentSelection;
    vector<Gifts> bestSolution;     
    int bestRemainingBudget = budget;

    cout << "Budget for "+file_name+ " is "  << budget << endl;;

    cout << "Remaining Budget " << gifts(currentSelection, wlist, 0, budget, bestSolution, bestRemainingBudget);


    return 0;
}
#endif