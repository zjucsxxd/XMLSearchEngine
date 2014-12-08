/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 11/12/2014
 * Jason Stumbaugh
 * Owen Klaiss
 **/

#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include <string>
#include "indexedword.h"
#include "avltree.h"
using namespace std;
class IndexInterface
{
private:
    string filePath;
public:
    IndexInterface() {}
    ~IndexInterface() {}
    string getFilePath() {return filePath;}
    void setFilePath(string s) {filePath = s;}
    virtual void addWord(string, string, int) = 0;
    virtual unordered_map<string, int> searchForWord(string) = 0;
    virtual void clearIndex() = 0;
    virtual void writeOutIndex() = 0;
    virtual void loadIndexFromFile() = 0;
};

#endif // INDEXINTERFACE_H
