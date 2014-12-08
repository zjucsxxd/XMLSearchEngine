#include "referencestringcleaner.h"
using namespace std;

ReferenceStringCleaner::ReferenceStringCleaner()
{
    fin.open("StopWords.txt");
    if(!fin.is_open()){
        cout << "Cannot Open Stopword File" << endl;}
    string word;
    while(fin>>word){
        stopwords.insert(word);}

}

//cleans word by checking for stop words, stemming, removing punctuation and making lower case
void ReferenceStringCleaner::clean(string& needsCleaning)
{
    //word.clear();
    // check to see if the word is a stop word first
    if (stopwords.isFound(needsCleaning))
    {
        needsCleaning = "";
        return;
    }


    // stem the word
    // TURN THIS INTO AN AVL TREE
    try
    {
        StemmedWord a(needsCleaning, "");
        StemmedWord P = stemmedTree.find(a);
        needsCleaning = P.afterStemming;
    }
    catch (logic_error &e)
    { // if the word is not found
        beforeStemming = needsCleaning;
        Porter2Stemmer::stem(needsCleaning);
        StemmedWord sword(beforeStemming, needsCleaning);
        stemmedTree.insert(sword);
    }
    for(int x=0; x<needsCleaning.length(); x++)
    {

        if(checkPunctuation(needsCleaning[x]))
        {
            word << " ";
        }
        else
        {
            character = tolower(character);
            word << character;
        }
    }
    //removeStopWords(/*word*/);//pass original word and final
    //needsCleaning = final;
}

//checking for stop words (we are no longer using this b/c our stop words are stored in an AVL tree)
void ReferenceStringCleaner::removeStopWords(/*stringstream& full*/)//change to boolean
{
    final = "";
    while(word>>now)
    {
        if(!stopwords.isFound(now))
        {
            //Porter2Stemmer::stem(now);
            final += now + " ";
        }
        else
        {
            final += "";
        }
    }
    now = "";
    //cout << final << endl;
    //return final;
}

//checks each character of word for punctuation
bool ReferenceStringCleaner::checkPunctuation(char& cha)
{
    num = cha;
    //check for punctuation or non characters
    if((num >=65 && num <= 90) || (num >= 97 && num <= 122))
        return false;
    else
        return true;
}

//Porter2
void ReferenceStringCleaner::turnToStem(string& dirty)
{
    Porter2Stemmer::stem(dirty);
    return;
}

//checking for stop words (we are no longer using this b/c our stop words are stored in an AVL tree)
bool ReferenceStringCleaner::checkStopWord(string& dirty)
{
    return stopwords.isFound(dirty);
    //cout << dirty << endl;
    /*for(int i=0; i<stopwords.size(); i++)
    {
        if(dirty.compare(stopwords[i])==0)
            return true;
    }*/
    //check for stop words
    //eventually change stopword vector to a AVLTree
    return false;
}

