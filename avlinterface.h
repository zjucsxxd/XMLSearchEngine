/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 11/12/2014
 * Jason Stumbaugh
 * Owen Klaiss
 **/

#ifndef AVLINTERFACE_H
#define AVLINTERFACE_H

#include "indexinterface.h"
#include "indexedword.h"
#include "avltree.h"
#include <string>
#include <sstream>

class AVLInterface : public IndexInterface
{
private:
    AVLTree<IndexedWord> tree;
public:
    AVLInterface();
    ~AVLInterface();
    void addWord(string, string, int);
    unordered_map<string, int> searchForWord(string);
    void clearIndex();
    void writeOutIndex();
    void loadIndexFromFile();
};

#endif // AVLINTERFACE_H
