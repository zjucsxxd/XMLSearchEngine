#ifndef REFERENCESTRINGCLEANER_H
#define REFERENCESTRINGCLEANER_H
#include "avltree.h"
#include "porter2_stemmer.h"
#include "stemmedword.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <utility>
using namespace std;

class ReferenceStringCleaner
{
private:
    AVLTree<string> stopwords;
    ifstream fin;
    char character;
    string now;
    string final;
    int num;
    unordered_map<string, string> map;
    string beforeStemming;
    bool test;
    AVLTree<StemmedWord> stemmedTree;
public:
    ReferenceStringCleaner();
    void clean(string& needsCleaning);
    void removeStopWords(/*stringstream& full*/);
    bool checkPunctuation(char& cha);
    void turnToStem(string& dirty);
    bool checkStopWord(string& dirty);
    stringstream word;
};

#endif // REFERENCESTRINGCLEANER_H
