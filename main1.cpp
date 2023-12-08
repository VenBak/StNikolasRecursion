#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

// bool valid (const vector<Wishlist>& wishlist) {
//     /* Postcondition: Result is true only if all elements in ‘coins‘ are valid, i.e., > 0 */
//     return true;
// }

// // void show (const vector<Coin>& money);


// bool match (string sub, string source)
// {// Precondition:
//     assert (true) ;
// /*  Postcondition:
//     Result is true only if sub is a literal (case sensitive) sub string of source.
// */
//     return source.find(sub) != string::npos ;
// }

// bool match_coins (const vector<Giftstore>& g, Slice a, const vector<Wishlist>& w, Slice b) {
//     int count = 0;
//     for(int i = 0; i < ssize(w); i++){
//         if(match(track, tracks.at(i).title)){
//             count++;
//             if(display){
//                 show_track(w.at(i), trueall, cout);
//             }
//         }
//     }
// }

struct Slice
{  int from;     // from >= 0
   int length;   // length >= 0
};

struct Gifts {
    int price;
    string name;
};

// typedef Item El;




Slice make_slice (int from, int length)
{// Precondition:
    assert (from >= 0 && length >= 0);
/*  post-condition:
    return slice with given from and length
*/
    Slice s = { from, length};
    return s;
}

typedef string Wishlist;
vector<Wishlist> w = {"sport cross-country ski", "game Mens erger je niet!", "game The settlers of Catan", "cd Marco by Marco Borsato", "cd Als geen ander by Marco Borsato"};// > 0

typedef string Giftstore;

// int gifts (const vector<Wishlist>& m, const vector<Giftstore>& g, const vector<int> cur, int c, int t, int p) {
//     // TODO: assign item_name based on line (or if the entire line is 
//     // the item name, replace line with item_name in the code above)
//     assert (valid (m) && 0 <= c && c <= ssize (m));

//     /* Result is the number of combinations comparing the items on the wishlist considering the budget with giftsore
//     w.at (c) . . . w.at (ssize (w)-1) */
    
    

//     if (t == 0) { return 1; }
//     else if (t < 0) { return 0; }
//     else if (c >= ssize (m)) { return 0; }
//     else
//     {
//         int with_c = gifts (m, g, cur, c+1, t-m.at (c), p.at(c+1));
//         int without_c = gifts (m, g, cur, c+1, t, p.at(c+1));
//         return with_c + without_c;
//     }
// }

#ifndef TESTING
int main ()
{// Precondition:
    assert (true);
/*  Postcondition: the gift store has been loaded, and the optimal gift lists of each name
    (Andrew ... Fabienne) has been computed and printed to `cout`
*/  
    // string candidates[6] ={"Andrew.txt", "Belle.txt", "Chris.txt", "Desiree.txt", "Edward.txt", "Fabienne.txt"};
    // ifstream giftstore;
    // giftstore.open("giftstore.txt");
    // string inventory;
    // getline(giftstore, inventory);
    // cout << inventory << endl;


    // for (int i = 0; i < 6; ++i) {
    //     ifstream wishlist;
    //     wishlist.open(candidates[i]);

    //     if (wishlist.is_open() && giftstore.is_open()) {
    //         string budget;
    //         getline(wishlist, budget);
    //         cout << "Budget for " << candidates[i] << ": " << budget << endl;
    //         string gift;
    //         getline(wishlist, gift);
    //         cout << gift << endl;
    //         wishlist.close(); 
    //     } else {
    //         cout << "Failed to open file";
    //     }
    // }
    vector<string> wlist = {};
    vector<Gifts> gift = {};
    cout<<"enter a file name ";
    string file_name;
    cin>>file_name;

    ifstream file_list(file_name);
    ifstream file_store("giftstore.txt");
    string item;
    string budget;

    if(!file_list.is_open()) cout <<"error not open list";
    if(!file_store.is_open()) cout <<"error not open store";
    getline(file_list, budget);
    cout << budget << endl;
    while (!file_list.fail()) {
        getline(file_list,item);
        cout << item << endl;
        wlist.push_back(item);
    }

    string item2;
    int i = 0;
    while (!file_store.fail()) {

        int price;
        string name;
        file_store>>price;
        getline(file_store,name);
        gift.at(i).price=price;
        gift.at(i).name=name;
        i++;
    }

    return 0;
}
#endif
