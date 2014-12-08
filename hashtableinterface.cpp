/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 12/4/2014
 * Jason Stumbaugh
 * Owen Klaiss
 **/

#include "hashtableinterface.h"

// basic constructor setting the hash table to have 26 buckets, one for each letter, which point to AVL trees
HashTableInterface::HashTableInterface() : IndexInterface()
{
    numBuckets = 26;
    setFilePath("/Users/Owen/Desktop/persistedindex.txt");
    loadIndexFromFile();
}

// write the index before it is deleted
HashTableInterface::~HashTableInterface()
{
    //writeOutIndex();
    clearIndex();
}

// this will add an IndexedWord object to the hashTable
void HashTableInterface::addWord(string w, string ID, int freq)
{
    // create IndexedWord object
    IndexedWord temp(w,ID,freq);
    temp.map[ID] = freq;

    // insert into correct bucket
    int number = hash(w);
    if (number != -1)
    {
        array[number].insert(temp);
    }
}


// this will search for a specific word in the hash table and return the pairs of docIds and freqs
// if the word is not found, it will return a map with the pair map["dummyID"] = -1
unordered_map<string, int> HashTableInterface::searchForWord(string str)
{
    string dummyString = "dummyID";
    int dummyInt = -1;
    IndexedWord x(str,dummyString,dummyInt);

    if (array[hash(str)].isFound(x))
    {
        IndexedWord returnedWord = array[hash(str)].find(x);
        return returnedWord.map;
    }
    else
    {
        return x.map;
    }
}


// empty each tree to clear the index
void HashTableInterface::clearIndex()
{
    for (int i=0; i<numBuckets; i++)
    {
        array[i].makeEmpty();
    }
}


// writes the index to the defaulted file
void HashTableInterface::writeOutIndex()
{
    setFilePath("Users/Owen/Desktop/PersistedIndex/PersistedIndexHash.txt");
    ofstream out(getFilePath());
    if (!out.is_open())
    {
        cout << "Error opening output file: " << getFilePath() << endl;
        exit(1);
    }
    else
    {
        // print out each tree in alphabetical order
        for (int i=0; i<numBuckets; i++)
        {
            if (!array[i].isEmpty())
            {
                array[i].printTree(out);
            }
        }
    }
    out.close();
}


// this will load the index from the file
void HashTableInterface::loadIndexFromFile()
{
    // empty the index before creating a new one
    clearIndex();

    // open the file where the index is saved
    ifstream fin(getFilePath());
    if (!fin.is_open())
    {
        cout << "Error loading file: " << getFilePath() << endl;
        exit(1);
    }

    string str;
    while (!fin.eof())
    {
        getline(fin,str);
        // str will contain the word along with the document ID's and their frequencies
        IndexedWord indexedWord;
        stringstream stream(str);

        stream >> indexedWord.word;

        string id;
        int f;
        while(stream >> id)
        {
            stream >> f;
            // add the pair to the map
            indexedWord.map.insert(make_pair(id,f));
            // reset the variables
            id = "";
            f = 0;
        }
        // add the indexedWord to the hash table
        int number = hash(indexedWord.word);
        if (number != -1)
        {
            array[number].insert(indexedWord);
        }
    }
    fin.close();
}

// this is the hashing function
// it will return and int (0-25) based on the first letter of each word
int HashTableInterface::hash(string str)
{
    for (int i=0; i<26; i++)
    {
        if ((int)str[0] == i+97)
        {
            return i;
        }
    }
    // will never reach this point but throw -1 to avoid errors
    return -1;
}

