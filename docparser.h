#ifndef DOCPARSER_H
#define DOCPARSER_H

#include "referencestringcleaner.h"
#include "rapidxml.h"
#include "rapidxml_utils.h"
#include "indexinterface.h"
#include "avlinterface.h"
#include "indexhandler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <unordered_map>

using namespace std;

class DocParser
{
private:
    bool structureBuilt;
    ifstream fin;
    IndexHandler* indexHandler;
    string xmlFileName;
    stringstream stream;
public:
    DocParser();
    DocParser(char* fileName, char* output);
    void setFilePath(string);
    bool isStructureBuilt() const;
    void clearStructure();
    void parse();
    void searchFor(string);

    friend IndexInterface;
};

#endif // DOCPARSER_H
