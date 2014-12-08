/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 11/12/2014
 * Jason Stumbaugh
 * Owen Klaiss
 **/
#include "avlinterface.h"

// basic constructor
AVLInterface::AVLInterface() : IndexInterface()
{
    setFilePath("/Users/Owen/Desktop/persistedindex.txt");
    loadIndexFromFile();

}

// write the index before it is deleted
AVLInterface::~AVLInterface()
{
    //writeOutIndex();
    clearIndex();
}

// this will add an IndexedWord object with the word, docID, and frequency to the AVLtree
void AVLInterface::addWord(string w, string ID, int freq)
{
    // create IndexedWord object
    IndexedWord temp(w,ID,freq);
    temp.map[ID] = freq;
    tree.insert(temp);
}

// this will search for a specific word in the tree and return the pairs of docIds and freqs
// if the word is not found, it will return a map with the pair map["dummyID"] = -1
unordered_map<string, int> AVLInterface::searchForWord(string str)
{
    string dummyString = "dummyID";
    int dummyInt = -1;
    IndexedWord x(str,dummyString,dummyInt);

    if (tree.isFound(x))
    {
        IndexedWord returnedWord = tree.find(x);
        return returnedWord.map;
    }
    else
    {
        return x.map;
    }
}

// empty the tree to clear the index
void AVLInterface::clearIndex()
{
    tree.makeEmpty();
}

// writes the index to the defaulted file
void AVLInterface::writeOutIndex()
{
    ofstream out(getFilePath());
    if (!out.is_open())
    {
        cout << "Error opening output file: " << getFilePath() << endl;
        exit(1);
    }
    else
    {
        tree.printTree(out);
    }
    out.close();
}


// this will load the index from file and put in in the tree
void AVLInterface::loadIndexFromFile()
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
        // add the indexedWord to the tree
        tree.insert(indexedWord);
    }
    fin.close();
}
