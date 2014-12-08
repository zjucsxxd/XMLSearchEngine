#include "docparser.h"
#include "sstream"
#include "string"
using namespace std;

DocParser::DocParser()
{
    structureBuilt = false;
}

DocParser::DocParser(char* fileName, char* output)
{
    //index = new AVLInterface;
    //index->setFilePath(output);
    xmlFileName = fileName;
    fin.open(fileName);
    //error message if file is not open
    if(!fin.is_open())
    {
        cerr << "DocParser constructor error while opening file: " << fileName << endl;
        exit(1);
    }
}

void DocParser::setFilePath(string path)
{
    xmlFileName = path;
    fin.open(path);
    if(!fin.is_open())
    {
        cerr << "DocParser constructor error while opening file: " << path << endl;
        exit(1);
    }
}

void DocParser::clearStructure()
{
    return;
}

bool DocParser::isStructureBuilt() const
{
    return false;
}

void DocParser::searchFor(string str)
{
    unordered_map<string, int> map;
    map = indexHandler->searchForWord(str);
    cout << "Searching for: " << str << endl;
    for (auto& x : map)
    {
        cout << "Page ID: " << x.first << " Frequency: " << x.second << endl;
    }
}

//parse will look through xml document, cleaning the text and adding it to the index of choice
void DocParser::parse()
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
                indexHandler->addWord(x.first, docID, x.second);//first is word, id is id, second is frequency
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
    indexHandler->writeIndexToFile();

    fin.close();
    //close input file!
}
