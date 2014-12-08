/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 12/4/2014
 * Jason Stumbaugh
 * Owen Klaiss
 **/

#ifndef HASHTABLEINTERFACE_H
#define HASHTABLEINTERFACE_H

#include "indexinterface.h"
#include "indexedword.h"
#include "avltree.h"
#include <string>
#include <sstream>

class HashTableInterface : public IndexInterface
{
private:
    int numBuckets;
    AVLTree<IndexedWord> array [26];
public:
    HashTableInterface();
    ~HashTableInterface();
    void addWord(string, string, int);
    unordered_map<string, int> searchForWord(string);
    void clearIndex();
    void writeOutIndex();
    void loadIndexFromFile();
    int hash(string);
};

#endif // HASHTABLEINTERFACE_H
