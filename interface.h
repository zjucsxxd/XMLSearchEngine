#ifndef INTERFACE_H
#define INTERFACE_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono>
#include "queryengine.h"

using namespace std;

class Interface
{
private:
    QueryEngine Pro1;
    int mode;
    bool indexbuilt;
    string modeString;
    void getCMD();
    void command(string);
    void runAVL();
    void runHASH();
    void runStressTest();
    void runMaintenance();
    void search(string);
    void setMode();
    void help();
    void addFile(string);
    void clearIndex();
    void quit();
    void lowerCase(string&);
    //search in query processor?
    //add memory destructors to quit or end function
public:
    Interface();

    friend DocParser;
};

#endif // INTERFACE_H
