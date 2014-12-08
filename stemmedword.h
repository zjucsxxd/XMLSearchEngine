#ifndef STEMMEDWORD_H
#define STEMMEDWORD_H

#include <string>
using namespace std;
class StemmedWord
{
public:
    string beforeStemming;
    string afterStemming;
    StemmedWord();
    StemmedWord(string, string);
    bool operator<(const StemmedWord&) const;
    StemmedWord& operator+=(const StemmedWord& rhs);
};

#endif // STEMMEDWORD_H
