/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 11/12/2014
 * Jason Stumbaugh
 * Owen Klaiss
 **/

#ifndef INDEXEDWORD_H
#define INDEXEDWORD_H

#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

class IndexedWord
{
public:
    string word;
    unordered_map<string, int> map;

    IndexedWord();
    IndexedWord(string w, string id, int f);
    void print();
    bool operator<(const IndexedWord& rhs) const;
    IndexedWord& operator+=(const IndexedWord& rhs);
    friend ostream& operator<<(ostream& out, const IndexedWord& rhs);
    bool operator==(const IndexedWord& rhs);
};

#endif // INDEXEDWORD_H
