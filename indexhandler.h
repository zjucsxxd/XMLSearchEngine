#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "indexinterface.h"
#include "avlinterface.h"
#include "hashtableinterface.h"
#include "referencestringcleaner.h"
#include "rapidxml.h"
#include "rapidxml_utils.h"
//#include "docparser.h"
// double includes
class IndexHandler
{
private:
    IndexInterface* index;
    string xmlFileName;
    ifstream fin;
    //DocParser parser;
public:
    IndexHandler();
    IndexHandler(bool HT);
    ~IndexHandler();
    IndexHandler* getIndexHandler();
    IndexInterface* getIndex();
    void setIndex(IndexInterface* indx);
    unordered_map<string, int> searchForWord(string str);
    void addWord(string word, string ID, int freq);
    void writeIndexToFile();
    void clearIndex();
    void addFileToIndex(string filename);
    void processFile();

};

#endif // INDEXHANDLER_H
