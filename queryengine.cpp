#include "queryengine.h"

// create the command words in the array
QueryEngine::QueryEngine()
{
    commands[0] = "and";
    commands[1] = "or";
    commands[2] = "not";
}

// return the indexHandler
IndexHandler* QueryEngine::getIndexHandler()
{
    return indexHandler;
}

// set the indexHandler
void QueryEngine::setIndexHandler(IndexHandler& iHandler)
{
    indexHandler = &iHandler;
}

// create an AVL index
void QueryEngine::AVL()
{
    indexHandler = new IndexHandler(false);
}

// create an HashTable index
void QueryEngine::HashTable()
{
    indexHandler = new IndexHandler(true);
}

// this will delete the current indexHandler and create a new one
void QueryEngine::switchIndex(bool HT)
{
    if (HT == true) // HashTable
    {
        IndexHandler* ih = new IndexHandler(true);
        delete indexHandler;
        indexHandler = ih;
    }
    else // AVL tree
    {
        IndexHandler* ih = new IndexHandler(false);
        delete indexHandler;
        indexHandler = ih;
    }
}

// clear the index
void QueryEngine::clearIndex()
{
    indexHandler->clearIndex();
}

// this will write the index out to a file
void QueryEngine::writeOutIndex()
{
    indexHandler->writeIndexToFile();
}

// this will open, parse, clean, and add the words to the index
bool QueryEngine::addFileToIndex(string filepath)
{
    string tempString;
    stringstream document;
    string xmlFileName = filepath;
    ifstream fin;
    fin.open(filepath);
    if(!fin.is_open())
        cout << "Could not open input file" << endl;
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
            filePath = "/Users/Owen/Desktop/Wiki/"+docID+".txt";
            //cout << "filepath: "<< filePath << endl;
            ofstream of(filePath);
            of << title << endl << date << endl << text << endl;
            of.close();
        }
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }

    cout << "DONE!" << endl;
    //index->writeOutIndex();

    fin.close();

}

// this is the boolean AND operation
void QueryEngine::ANDoperation(unordered_map<string, int>& map1, unordered_map<string, int>& map2)
{
    unordered_map<string,int> final;
    for (auto& x : map1)
    {
        for (auto& y : map2)
        {
            if (x.first == y.first)
            { // insert the item into the new map and add the frequencies
                final.insert(make_pair(x.first, (x.second+y.second)));
            }
        }
    }
    map1 = final;
}

// this is the boolean OR operation which will have all of the items in both lists together
void QueryEngine::ORoperation(unordered_map<string, int>& map1, unordered_map<string, int>& map2)
{
    // this will add the second map to the first map
    unordered_map<string,int> final;
    for (auto& x: map1)
    {
        final.insert(make_pair(x.first,x.second));
    }
    for (auto& x: map2)
    {
        final.insert(make_pair(x.first,x.second));
    }
    map1=final;
}

// this is the boolean NOT operation, map1 will equal the map without items in the notMap
void QueryEngine::NOToperation(unordered_map<string, int>& map1, unordered_map<string, int>& notMap)
{
    for (auto& x : map1)
    {
        for (auto& y : notMap)
        {
            if (x.first == y.first)
            { // remove the item from map1
                map1.erase(x.first);
            }
        }
    }
}

// this will check to see if the word is a keyword
bool QueryEngine::isCommand(string str)
{
    for (int i=0; i<3; i++)
    {
        if (str == commands[i])
            return true;
    }
    return false;
}


// this is the query function. It will perform the whole query, including calling
// the boolean AND, OR, and NOT functions. It will return an unordered_map<string,int>
// of max size 15 arranged in order from highest frequency to lowest
vector<string> QueryEngine::query(string str)
{
    unordered_map<string, int> temp1;
    unordered_map<string, int> temp2;

    // read in query to stringstream
    stringstream stream(str);
    string temp;
    vector<string> words;
    while (stream >> temp)
    {
        words.push_back(temp);
    } // words is now a vector of the words in the query

    // temp1 will hold the combined unordered_map after this for loop executes
    string currentCommand;
    for (size_t i=0; i<words.size(); i++)
    {
        if (isCommand(words[i]))
        {
            currentCommand = words[i];
        }
        else if (i == 0 && !isCommand(words[i]))
        {
            // clean and search for the word
            Cleaner.clean(words[i]);
            temp1 = indexHandler->searchForWord(words[i]);
        }
        else if (i == 1 && !isCommand(words[i]))
        {
            // clean and search for the word
            Cleaner.clean(words[i]);
            temp1 = indexHandler->searchForWord(words[i]);
        }
        else
        {
            // clean and search for the word
            Cleaner.clean(words[i]);
            temp2 = indexHandler->searchForWord(words[i]);
            if (currentCommand == commands[0]) // AND
            {
                ANDoperation(temp1,temp2);
            }
            else if (currentCommand == commands[1]) // OR
            {
                ORoperation(temp1,temp2);
            }
            else if (currentCommand == commands[2]) // NOT
            {
                NOToperation(temp1,temp2);
            }
        }
    }
    // now temp1 hold the list of docIDs and frequencies for the query

    // if there are no results, return this map with "dummyID"
    for (auto& a : temp1)
    {
        if (a.first == "dummyID")
        {
            vector<string> map;
            for (auto& y : temp1)
            {
                string name = y.first;
                map.push_back(name);
            }
            return map;
        }
    }
    return rank(temp1);
}


vector<string> QueryEngine::rank(unordered_map<string, int> map)
{
    // for calculating the TFIDF for each word
    double frequency;
    double totalTermsInDoc;
    double TF; // = frequency / totalTermsInDoc
    double totalDocs = 160453.0;
    int numDocsWithWord = map.size();
    double IDF; // = log e (totalDocs/numDocsWithWord)
    double TFIDF;
    ifstream fin;
    string indexPath;
    string buffer;
    double t;
    unordered_map<string,double> temp;
    vector<string> rankedlist;

    for (auto& x : map)
    {
        frequency = x.second;
        //cout << "frequency " << frequency << endl;
        indexPath = "/Users/Owen/Desktop/Wiki/"+x.first+".txt";
        fin.open(indexPath);

        // to ignore the title and the date
        getline(fin,buffer);
        buffer = "";
        getline(fin,buffer);
        buffer = "";
        // to calculate number of words in the document
        int f = 0;
        while (fin >> buffer)
        {
            f++;
            buffer = "";
        }
        //cout << "total terms in doc: " << f << endl;
        totalTermsInDoc = f;
        fin.close();

        // to calculate TFIDF
        //cout << "before log" << endl;
        TF = frequency/totalTermsInDoc;
        //cout << "TF " << TF << endl;
        t = totalDocs/numDocsWithWord;
        //cout << "t " << t << endl;
        IDF = log(t);
        //cout << "IDF" << IDF << endl;
        //cout << "after log" << endl;
        TFIDF = TF*IDF;

        // insert it into new map
        temp.insert(make_pair(x.first,TFIDF));
        //cout << "TFIDF" << TFIDF << endl;
    }
    // now temp has all of the docs and the TFIDF, but not ranked

    /*for (auto& i : temp)
    {
        cout << i.first << " " << i.second << endl;
    }*/
    string docname;
    // RANKING
    //unordered_map<string, double> rankedList;
    for (int i=0; i<15; i++)
    {
        /*unordered_map<string, double>::iterator biggest = temp.begin();
        for (unordered_map<string, double>::iterator x = temp.begin(); x != temp.end(); x++)
        {
            if (biggest->second < x->second)
            {
                biggest = x;
            }
        }*/
        double freq1 = temp.begin()->second;
        //unordered_map<string,double>::iterator biggest = temp.begin();
        for(auto x:temp)
        {
            if(x.second>freq1)
            {
                docname = x.first;
                freq1 = x.second;
            }

        }
        stringstream stream;
        stream<<docname;
        stream<<" ";
        stream<<freq1;
        //rankedList.insert(make_pair(docname, freq1));
        rankedlist.push_back(stream.str());
        temp.erase(docname);
    }

    // rankedList now equals the top 15 terms ranked in order by the frequencies
    return rankedlist;
}
