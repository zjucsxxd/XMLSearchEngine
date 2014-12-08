#include "interface.h"

using namespace std;

//Internal UI functions are private

Interface::Interface()
{
    cout << endl << "Starting WikiSearch" << endl << "..." << endl << "..." << endl << "..." << endl;
    mode = 1;
    indexbuilt=false;
    help();
}

//prompts user for command
void Interface::getCMD()
{
    cout << endl;
    cout << "Enter command" << endl;
    cout << "-> ";
    string terminal;
    getline(cin, terminal);
    return command(terminal);
}

//search
void Interface::search(string words)
{
    ifstream fin;
    string indexPath;
    string title;
    int counter=1;
    string response;
    string buffer;
    string array[15];
    string name;
    string freq;
    //x.first = idstr
    //x.second = freq
    vector<string> map = Pro1.query(words);
//    if(map.size()==1||map.size()==0)
//        return;

    if(map[0]=="dummyID")
    {
        cout << "No results for " << words << endl;
        return;
    }

    for(int x=0; x<map.size(); x++)    //loop through map and print top 15 results
    {
        stringstream stream(map[x]);
        stream >> name;
        indexPath = "/Users/Owen/Desktop/Wiki/"+name+".txt";
        //cout << name;
        fin.open(indexPath);
        getline(fin,title);
        stream >> freq;
        cout << "Item " << counter << ": " << title << endl
             << "       -TF/IDF: " << freq << endl;
        array[counter-1]=indexPath;
        counter++;
        fin.close();
    }
    if(mode==3) //if in stress-test, do no ask to view
        return;
    cout << "Enter result you would like to view or type 'end' to end search:" << endl << "-> ";
    cin >> response;
    int num = atoi(response.c_str());
    if(response=="end")
    {
        return;
    }
    if(num<1||num>15)
    {
        cout << "Invalid command entered";
        return;
    }
    counter = 1;
    indexPath = array[num-1];
    fin.open(indexPath);
    if(!fin.is_open())
    {
        cout << "Cannot open search file" << endl;
        return getCMD();
    }
    getline(fin,buffer);
    cout << "Title: " << buffer << endl;
    buffer = "";
    getline(fin,buffer);
    cout << "Timestamp: " << buffer << endl;
    buffer = "";
    while(getline(fin,buffer))
    {
        cout << buffer << endl;
        buffer="";
    }
    fin.close();
}

//change data structure to AVL tree
void Interface::runAVL() //sets up data structure as AVL Tree
{
    if(indexbuilt==true)
        clearIndex();
    cout << "Building as AVL Tree" << endl << "Please wait" << endl;
    Pro1.AVL();
    indexbuilt=true;
    cout << "Index built" << endl;
}

//change data structure to Hash table
void Interface::runHASH() //sets up data structure as Hash Table
{
    if(indexbuilt==true)
        clearIndex();
    cout << "Building as Hash Table" << endl << "Please wait" << endl;
    Pro1.HashTable();
    indexbuilt=true;
    cout << "Index built" << endl;
    //Pro1.writeOutIndex();
}

//run maintenance mode
void Interface::runMaintenance()
{
    string xmlpath;
    cout << "Please input the file path to the file you with to add to the current index" << endl
         << "If you would like to return to interactive mode, type 'exit'" << endl
         << "-> ";
    cin >> xmlpath;
    if(xmlpath=="exit")
    {
        cout << "Returning to interactive mode" << endl;
        mode = 1;
        return getCMD();
    }
    cout << "File path = " << xmlpath << endl;
    addFile(xmlpath);
    cout << "Returning to interactive mode" << endl;
    mode = 1;
    return getCMD();
}

//run commands from stress-test file
void Interface::runStressTest() //runs stress test commands from stresstest.txt file
{
    string stressPath;
    cout << "Enter the file path to the file containing the 'stress-test-' commands" << endl
         << "Each line of the file must contain a command and its arguments if applicable" << endl
         << "Each command will be timed to the nearest millisecond" << endl
         << "If you would like to return to interactive mode, type 'exit'" << endl
         << "-> ";
    cin >> stressPath;
    if(stressPath=="exit")
    {
        cout << "Returning to interactive mode" << endl;
        mode = 1;
        return getCMD();
    }
    ifstream fin(stressPath);
    if(fin)
    {
        chrono::time_point<std::chrono::system_clock> start, end;
        unsigned int time;
        string cmd;
        while(getline(fin,cmd))
        {
            start = std::chrono::system_clock::now();
            command(cmd);
            end = chrono::system_clock::now();
            time = chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
            cout << cmd << " took " << time << " milliseconds to run" << endl;
        }
        cout << "Stress-test completed" << endl
             << "Returning to interactive mode" << endl;
        mode = 1;
    }
    else
    {
        cout << "Could not open file: " << stressPath << endl
             << "Returning to interactive mode" << endl;
        mode = 1;
    }
    return getCMD();
}

//add file to current index
void Interface::addFile(string filePath)
{
    Pro1.addFileToIndex(filePath);
}

//clears index in RAM
void Interface::clearIndex() //clears current index in memory
{
    if(indexbuilt==false)
    {
        cout << "Cannot clear memory because no index is currently built" << endl;
    }
    else
    {
        cout << endl << "Clearing current index in memory" << endl;
        Pro1.clearIndex();
        indexbuilt=false;
    }
}

//sets mode to interactive(1) maintenance(2) or stress-test(3)
void Interface::setMode()
{
    for(int i=0; i<100; i++)
    {
        cout << endl << "Enter WikiSearch Mode:" << endl;
        cout << "interactive " << endl;
        cout << "maintenance " << endl;
        cout << "stress-test " << endl << endl;
        cin >> modeString;
        lowerCase(modeString);

        if(modeString == "interactive")
        {
            mode = 1;
            break;
        }
        else if(modeString == "maintenance")    //have to be able to add files to index
        {
            mode = 2;
            break;
        }
        else if(modeString == "stress-test")
        {
            mode = 3;
            break;
        }
        else
        {
            cout << endl << "No mode selected" << endl;
            return getCMD();
        }

    }
    cout << modeString << " selected" << endl;
    cout << "Running " << modeString << " mode" << endl;
    if(mode==2)
        return runMaintenance();
    if(mode==3)
        return runStressTest();
    else
        return getCMD();
}

//analyzes command
void Interface::command(string what)
{
    if(mode == 3)
    {
        //stress test
        lowerCase(what);
        if(what=="")
            return;
        else if(what=="clearindex")
            return clearIndex();
        else if(what.substr(0,7)=="search:") //search
        {
            search(what.substr(7));
            return;
        }
        else if(what=="runasavl")
        {
            return runAVL();
        }
        else if(what=="runashash")
        {
            return runHASH();
        }
        else if(what.substr(0,4)=="add:")
        {
            return addFile(what.substr(4));
        }
    }
    else
    {
        cout << "command: " << what << endl;
        lowerCase(what);
        if(what=="")
            return getCMD();
        else if(what=="help")
            return help();
        else if(what=="clearindex")
        {
            clearIndex();
            return getCMD();
        }
        else if(what.substr(0,7)=="search:") //search
        {
            cout << "SEARCHING FOR: " << what.substr(7) << endl;
            search(what.substr(7));
            return getCMD();
        }
        else if(what=="setmode")
        {
            return setMode();
        }
        else if(what=="runasavl")
        {
            runAVL();
            return getCMD();
        }
        else if(what=="runashash")
        {
            runHASH();
            return getCMD();
        }
        else if(what=="quit")
        {
            return quit();
        }
        else
        {
            cout << endl << "Unrecognizable command";
            return getCMD();
        }
    }

}

//help will display basic instructions on screen
void Interface::help()
{
    //cout instructions here
    cout << "Hello! Welcome to WikiSearch!" << endl
         << "To search, type 'search:' followed immediately by your query" << endl
         << "Use 'AND ' followed by words to combine results" << endl
         << "Use 'OR ' followed by words to or results" << endl
         << "Use 'NOT' followed by words to exclude results" << endl
         << "Here is a list of other commands you may use:" << endl
         << "SetMode" << endl
         << "RunAsAVL" << endl
         << "RunAsHash" << endl
         << "ClearIndex" << endl
         << "Quit" << endl
         << "Type 'help' at any time to repeat these directions." << endl
         << "If you have more questions about WikiSearch, refer to the user manual." << endl;
    return getCMD();
}

//end the program
void Interface::quit()
{
    exit(1);
}

//converts string to lower case by reference
void Interface::lowerCase(string& word)
{
    for(int x=0; x<word.length(); x++)
    {
        word[x] = tolower(word[x]);
    }
}

