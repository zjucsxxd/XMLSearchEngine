#include "stemmedword.h"

StemmedWord::StemmedWord()
{
}

StemmedWord::StemmedWord(string str1, string str2)
{
    beforeStemming = str1;
    afterStemming = str2;
}


// for comparing the words in the AVL tree
bool StemmedWord::operator<(const StemmedWord& rhs) const
{
    return (strcmp(this->beforeStemming.c_str(), rhs.beforeStemming.c_str()) < 0);
}


// adds the new pair to the existing map
StemmedWord& StemmedWord::operator+=(const StemmedWord& rhs)
{
    return *this;
}
