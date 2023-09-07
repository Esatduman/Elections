#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ourvector.h"
#include <sstream>
#include <math.h>
#include <algorithm>

using namespace std;
/* -----------------------------------------
Title: Project 1 - Gerrymandering Project
Name: Esat Duman 
UIN:662726641
Course: Data Structures (CS251)
IDE used: VS code 
Professor: Adam Koehler
--------------------------------------------*/

struct district {         //struct used throughout the program 
    string district_ID;  // for districts 
    string voter_ID;    // voter count 
    ourvector<int> eligVoter;
    ourvector<int> democrat;
    ourvector<int> republic;

};

struct states {        // struct for state names 
    string stateName;
};

ourvector<string> loadFileData1(string dataFile) { // Function to load file.
    ifstream inFS;
    ourvector<string> storeFiles; // vector declared to store data
    inFS.open(dataFile);

    while(getline(inFS, dataFile)) {
        cout << dataFile << endl;
        storeFiles.push_back(dataFile);
    }

    inFS.close();
   return storeFiles;

}

ourvector<string> loadFileData2(string dataFile2) { // Function to load file.
    ifstream inFile;
    ourvector<string> storeFiles; // vector declared to store data
    inFile.open(dataFile2);

    while(getline(inFile, dataFile2)) {
        cout << dataFile2 << endl;
        storeFiles.push_back(dataFile2);
    }

    inFile.close();
   return storeFiles;

}

bool searchState(string state, vector<string> &stateData) {       // search function if the word is capital it will function has loading issues
  transform(state.begin(), state.end(), state.begin(), ::toupper);
  for (int i = 0; i < stateData.size(); i++) {
    if (stateData[i] == state) {
      return true;
    }
  }
  return false;
}

void exitProgram(string command) { // Function to exit program
    if (command == "exit"){
        //cout << "Exiting Program" << endl;
        exit(0);
    }
    return exit(0);
}

ourvector<string> readingFile1(const string &fileName) {  // Funtion that will read district_ID and the state with it 

    //ifstream inFile(fileName);
    ourvector<string> dataList;
    string fileLine;
    ifstream inFile(fileName);
     
    cout << "Reading: " << fileName << endl;
    
    while (getline(inFile, fileLine)) {
        district temp;
        dataList.push_back(fileLine);
        stringstream ss(fileLine);
       // string totalDistrict = fileLine.substr(1,pos);
        string stateName;
        string data;
        string demVotes;
        string repVotes;

        int third_last = -1; // second_last = -1, last = -1;
        getline(ss, stateName, ',');
        temp.district_ID = stateName; // using the strust district and storing data into district_ID
        while(getline(ss, data, ','))
        {
        getline(ss, demVotes, ',');
        getline(ss, repVotes, ',');
        temp.democrat.push_back(stoi(demVotes));
        temp.republic.push_back(stoi(repVotes));
            
            if (data == "AL") {    // if data comes across "AL" make it 1;
            third_last = 1;
            } else {
            if(all_of(data.begin(), data.end(), ::isdigit)) // The all_of what it does it checks if the if all elements in range satify the condition
            {
                //third_last = second_last;
               // second_last = last;
                third_last = stoi(data);
            }
            }
        }
        cout << "..." << stateName << "..." << third_last << " districts total" << endl;
        
    }

    inFile.close();
    return dataList;
}

ourvector<string> fragmentStr(const string& str, const string& eligVoter)  // Function cuts the string to make it easier 
{                                                                          // to get the total eligible voters #
    ourvector<string> result;                              
    size_t start = 0; // the start of the string 
    size_t end = str.find(eligVoter); // end of the string I use str.find() to do this.
    while (end != string::npos) // loop condition checks if the value of end is equal to the string if not while loop does the following arithmetic between strings and divides them apart.
    {
        result.push_back(str.substr(start, end - start));
        start = end + eligVoter.length();
        end = str.find(eligVoter, start);
    }
    result.push_back(str.substr(start, end));
    return result;
}

ourvector<ourvector<string>> readingFile2(const string& filename)
{
    ourvector<ourvector<string>> voter_records;

    fstream input_file(filename);
    if (!input_file.good())
    {
        cout << "Invalid second file, try again. "<< endl;
       // cout << endl << "Data loaded? " << "No" << endl;
       // cout << "State: N/A" << endl;
       // cout << endl;
        return voter_records;

    }  else {

        cout << "Reading: " << filename << endl;

    }
    while (!input_file.eof())
    {
        string line;
        getline(input_file, line);
        if (line.empty()) {
            break;
        }
        auto record = fragmentStr(line, ",");
        if (record.size() < 2) {
            continue;
        }
        if (record[0] == "District of Columbia")  // if the program sees "District of Columbia" ignore it 
        {
            continue;
        }

        string state = record[0];
        string eligible_voters = record[1];
        eligible_voters.erase(remove(eligible_voters.begin(), eligible_voters.end(), '\r'), eligible_voters.end());
        cout << "..." << state << "..." << eligible_voters << " eligible voters" << endl;

        voter_records.push_back(record);
    }

    input_file.close();
    return voter_records;
}

int main() {

string input, fileInput1, fileInput2, fileInput3;
string fileName;
vector<string> storeFiles;
ifstream inFS(fileName);
string line;

//--------------------------------------------------------- * Starting Message *
cout << "Welcome to the Gerrymandering App!" << endl;
cout << '\n';
cout << "Data loaded? No" << endl;
cout << "State: N/A" << endl;
cout << "\n";

while(true) {

ourvector<string> districts;

string y = "Yes";
string n = "No";
string load = "load";
string search = "search";

cout << "Enter command: ";
getline(cin, input);
cout << "-----------------------------" << endl;
cout << endl;
stringstream ss(input);  // stringstream used just as the professor had showed us in the 2nd week 
ss >> fileInput1 >> fileInput2 >> fileInput3;

if (fileInput1 == load) {  // load command will load file 
    
    districts = readingFile1(fileInput2);
    cout << endl;
    readingFile2(fileInput3);
    cout << endl;
    cout << endl << "Data loaded? " << y << endl;
    cout << "State: N/A" << endl;
    cout << endl;

} else {

}
    vector<string> stateData;
  if(fileInput1 == "search") {
   
      if (searchState(fileInput2, stateData)) {
        cout << "State: " << fileInput2 << endl;
      } else {

        cout << endl << "Data loaded? " << y << endl;
        cout << "State: " << fileInput2 << endl;
        cout << endl;
      }
  
  }
if (input == "exit") {     // exits the program 
    exitProgram(input);
}
   
}  // end of the while loop 

    return 0;
  
}