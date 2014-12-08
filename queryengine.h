#ifndef QUERYENGINE_H
#define QUERYENGINE_H

#include "rapidxml.h"
#include "rapidxml_utils.h"
#include "indexhandler.h"
#include "docparser.h"
#include "referencestringcleaner.h"
#include <algorithm>
#include <cmath>
#include "math.h"
#include <fstream>
#include <iostream>
using namespace std;
class QueryEngine
{
private:
    IndexHandler* indexHandler;
    ReferenceStringCleaner Cleaner;
    string commands[3];
public:
    QueryEngine();
    IndexHandler* getIndexHandler();
    void setIndexHandler(IndexHandler& iHandler);
    vector<string> query(string str);
    vector<string> rank(unordered_map<string, int>);
    void AVL();
    void HashTable();
    bool addFileToIndex(string filepath);
    void ANDoperation(unordered_map<string,int>&, unordered_map<string,int>&);
    void ORoperation(unordered_map<string,int>&, unordered_map<string,int>&);
    void NOToperation(unordered_map<string,int>&, unordered_map<string,int>&);
    bool isCommand(string);
    void switchIndex(bool HT);
    void writeOutIndex();
    void clearIndex();
};

#endif // QUERYENGINE_H
