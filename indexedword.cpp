/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 11/12/2014
 * Jason Stumbaugh
 * Owen Klaiss
 **/
#include "indexedword.h"
using namespace std;

// basic constructor
IndexedWord::IndexedWord()
{
    word = "";
}

// set the word and the pair in the map
IndexedWord::IndexedWord(string w, string id, int f)
{
    word = w;
    map.insert(make_pair(id,f));
}

// printing the word out with its associated docIDs and freqs
void IndexedWord::print()
{
    cout << "Word: " << word << endl;
    cout << "Map: " << endl;
    for (auto& x : map)
    {
        cout << "PageID: " << x.first << " Frequency: " << x.second << endl;
    }
}

// for comparing the words in the AVL tree
bool IndexedWord::operator<(const IndexedWord& rhs) const
{
    return (strcmp(this->word.c_str(), rhs.word.c_str()) < 0);
}

// adds the new pair to the existing map
IndexedWord& IndexedWord::operator+=(const IndexedWord& rhs)
{
    for(auto& w: rhs.map)
        map.insert(w);
    return *this;
}

// for printing out the word and its associated pages and frequencies to the index
ostream& operator<<(ostream& out, const IndexedWord& rhs)
{
    out << rhs.word << " ";
    for(auto& x: rhs.map)
        out << x.first << " " << x.second << " ";
    return out;
}

// for comparisons between the words for searching
bool IndexedWord::operator==(const IndexedWord& rhs)
{
    return (this->word == rhs.word);
}
