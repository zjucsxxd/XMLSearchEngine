#include "indexhandler.h"

// basic constructor
IndexHandler::IndexHandler()
{
}

// this will construct an index based on the bool passed in
IndexHandler::IndexHandler(bool HT)
{
    if (HT)
    {
        index = new HashTableInterface;
    }
    else
    {
        index = new AVLInterface;
    }
}

// deletes the index
IndexHandler::~IndexHandler()
{
    clearIndex();
}

// returns the index
IndexInterface* IndexHandler::getIndex()
{
    return index;
}

void IndexHandler::setIndex(IndexInterface* indx)
{
    index = indx;
}

// this will call the index to add the word to it
void IndexHandler::addWord(string word, string ID, int freq)
{
    index->addWord(word, ID, freq);
}

// this will return the index's search for the word which will be an unordered_map<string,int>
unordered_map<string, int> IndexHandler::searchForWord(string str)
{
    return index->searchForWord(str);
}

// this will write out the index to a file
void IndexHandler::writeIndexToFile()
{
    index->writeOutIndex();
}

void IndexHandler::clearIndex()
{
    index->clearIndex();
}


void IndexHandler::addFileToIndex(string filename)
{
    //parser.setFilePath(filename)
    //parser.parse();
    xmlFileName = filename;
    fin.open(filename);
    if(!fin.is_open())
    {
        cerr << "DocParser constructor error while opening file: " << filename << endl;
        exit(1);
    }
    processFile();
}

void IndexHandler::processFile()
{
    //variable declarations
    string tempString;
    stringstream document;

    ReferenceStringCleaner cleaner;
    unordered_map<string, int> map;
    string filePath;
    string docID;
    string temp;
    string word;
    string temp2;
    string cleaned;
    string buffer;
    string title;
    string text;
    string author;
    string date;
    int beginPage=0;
    int endPage=0;
    int beginText=0;
    int endText=0;
    int beginID=0;
    int endID=0;
    stringstream stream;
    cout << "Running..." << endl;

    //RAPIDXML
    try
    {
        int x = 0;

        rapidxml::file<> xmlFile(xmlFileName.c_str());
        rapidxml::xml_document<> doc;
        doc.parse<0>(xmlFile.data());

        rapidxml::xml_node<>* root_node = doc.first_node();
        rapidxml::xml_node<>* revision_node;
        rapidxml::xml_node<>* contributor_node;
        if(root_node == 0)
            cout << "Unrecognizeable XML format" << endl;

        for(rapidxml::xml_node<>* page_node = root_node->first_node("page"); page_node;
            page_node = page_node->next_sibling())
        {
            map.clear();
            /*x++;
            if(x == 1000)
            {
                break;
            }*/
            revision_node = page_node->first_node("revision");
            contributor_node = revision_node->first_node("contributor");
            docID = revision_node->first_node("sha1")->value();
            title = page_node->first_node("title")->value();
            text = revision_node->first_node("text")->value();
            date = revision_node->first_node("timestamp")->value();

            stream.str("");
            stream.clear();
            stream << revision_node->first_node("text")->value();
            word.clear();
            while(stream.good())
            {
                stream >> word;
                cleaner.clean(word);
                map[word]++;
//                cleaned.str("");
//                cleaned.clear();
//                stringstream cleaned(word);
//                while(cleaned.good())
//                {
//                    cleaned >> word;
//                    map[word]++;
//                }
            }
            for(auto& x : map)
            {
                addWord(x.first, docID, x.second);//first is word, id is id, second is frequency
            }

            //save data to file for current page
            //filePath = "/Users/Owen/Desktop/Wiki/"+docID+".txt";
            //cout << "filepath: "<< filePath << endl;
            //ofstream of(filePath);
            //of << title << endl << date << endl << text << endl;
            //of.close();
        }
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }

    cout << "DONE!" << endl;
    //index->writeOutIndex();

    fin.close();
    //close input file!


}
