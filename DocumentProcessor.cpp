//
// Created by Ella Grace Collard on 11/8/22.
//

#include "DocumentProcessor.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "porter2_stemmer.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace rapidjson;
using namespace Porter2Stemmer;
using namespace std;
void DocumentProcessor::processDocuments(const char *filePath) {
    // recursive_director_iterator used to "access" folder at parameter -path-
    // we are using the recursive iterator so it will go into subfolders.
    // see: https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator
    auto it = filesystem::recursive_directory_iterator(filePath);
    int id = 0;
    // loop over all the entries.
    for (const auto &entry : it)
    {

//        cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;

        // We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json")
        {
            if (id % 2000 == 0)
                cout << "parsing doc num " << id << endl;

            // open an ifstream on the file of interest and check that it could be opened.
            ifstream input(entry.path().c_str());
            if (!input.is_open())
            {
                cerr << "cannot open file: " << filePath << endl;
                return;
            }

            // Create a RapidJSON IStreamWrapper using the file input stream above.
            IStreamWrapper isw(input);

            // Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
            Document d;
            d.ParseStream(isw);

            // Now that the document is parsed, we can access different elements the JSON using
            // familiar subscript notation.

            // This accesses the -title- key in the JSON. Since the value
            //  associated with title is a string (rather than
            //  an array or something else), we call the GetString()
            //  function to return the actual title of the article
            //  as a c-string.
            auto val = d["title"].GetString();
//            cout << "Title: " << val << "\n";
            auto author = d["author"].GetString();
            auto date = d["published"].GetString();

            string text = d["text"].GetString();
            // remove the newlines from the text
            text.erase(std::remove(text.begin(), text.end(), '\n'), text.cend());
            doc currentDocument(val, author, date, text, id);
            allDocs.push_back(currentDocument);
            // loop through the text word by word
            stringstream ss(text);
            string temp;
            while (getline(ss, temp, ' ')) {
                // stem the word
                stem(temp);

                // if the word doesn't exist already in our avl tree
                if (!words.contains(temp)) {
                    vector<int> tempVec;
                    tempVec.push_back(id);
                    words.insert(temp, tempVec);
                }
                else {

                    // check for duplicate documents before this line
                    // here
                    bool dupe = false;
                    for(auto & i : words.get(temp)) {
                        if(id == i){
                            dupe = true;
                        }
                    }
                    // loop through all the documents in the vector currently (of words.get(temp))
                    // see if currentDocument exists in the vector already
                    if(!dupe) {
                        words.get(temp).push_back(id);
                    }
                }
            }


            // The Persons entity fosdcr which you're building a specific
            //  inverted index is contained in top level -entities- key.
            //  So that's why we subscript with ["entities"]["persons"].
            //  The value associated with entities>persons is an array.
            //  So we call GetArray() to get an iterable collection of elements
            auto persons = d["entities"]["persons"].GetArray();

            // We iterate over the Array returned from the line above.
            //  Each key kind of operates like a little JSON document
            //  object in that you can use the same subscript notation
            //  to access particular values.
//            cout << "  Person Entities + sentiment:"
//                 << "\n";
            for (auto &p : persons)
            {

                stringstream ss(p["name"].GetString());
                string temp;
                while (getline(ss, temp, ' ')) {
                    // if the word doesn't exist already in our avl tree
                    if (!people.contains(temp)) {
                        vector<int> tempVec;
                        tempVec.push_back(id);
                        people.insert(temp, tempVec);
                    }
                    else {
                        people.get(temp).push_back(id);
                    }
                }
            }



            auto organizations = d["entities"]["organizations"].GetArray();

            // We iterate over the Array returned from the line above.
            //  Each key kind of operates like a little JSON document
            //  object in that you can use the same subscript notation
            //  to access particular values.
//            cout << "  Organizations"
//                 << "\n";
            for (auto &o : organizations)
            {
                stringstream ss(o["name"].GetString());
                string temp;
                while (getline(ss, temp, ' ')) {
                    // if the word doesn't exist already in our avl tree
                    if (!org.contains(temp)) {
                        vector<int> tempVec;
                        tempVec.push_back(id);
                        org.insert(temp, tempVec);
                    }
                    else {
                        org.get(temp).push_back(id);
                    }
                }
            }

            input.close();
            id++;
        }
    }

//    // search for the word the
//    if (words.contains("the")) {
//        cout << "num results: " << words.get("the").size() << endl;
//        for (auto& i : words.get("the")) {
//            cout << i.getTitle() << endl;
//        }
//    }
}

 AvlTree<string, vector<int>> &DocumentProcessor::getWords() {
    return words;
}

void DocumentProcessor::setWords(const AvlTree<string, vector<int>> &words) {
    DocumentProcessor::words = words;
}

AvlTree<string, vector<int>> &DocumentProcessor::getPeople() {
    return people;
}

void DocumentProcessor::setPeople(const AvlTree<string, vector<int>> &people) {
    DocumentProcessor::people = people;
}

AvlTree<string, vector<int>> &DocumentProcessor::getOrg() {
    return org;
}

void DocumentProcessor::setOrg(const AvlTree<string, vector<int>> &org) {
    DocumentProcessor::org = org;
}

void DocumentProcessor::makePersistenceOf(const char* fileName, AvlTree<string, vector<int>>& tree){
    ofstream out(fileName);
    unordered_map<string, vector<int>> thisMap;
    tree.getMap(thisMap);

    // for each entry in the avl tree
    for (auto & x : thisMap) {
        out << x.first << char(31);
        // each of the document ids
        for (auto & y : x.second) {
            out << y << ",";
        }
        out << endl;
    }
}

void DocumentProcessor::createPersistence() {
    cout << "creating persistence" << endl;
    cout << "making persistence of words" << endl;
    makePersistenceOf("words.GouldGrace", words);
    cout << "making persistence of people" << endl;
    makePersistenceOf("people.GouldGrace", people);
    cout << "making persistence of orgs" << endl;
    makePersistenceOf("orgs.GouldGrace", org);

    // make the persistence of all the documents
    cout << "making persistence of all Docs" << endl;
    ofstream out("docs.GouldGrace");
    for (auto & x : allDocs) {
        out << x.getTitle() << char(31)
            << x.getPublication() << char(31)
            << x.getId() << char(31)
            << x.getDatePublished() << char(31)
            << x.getText() << endl;
    }
    cout << "Creating persistence finished" << endl << "============" << endl;
}

void DocumentProcessor::pullPersistenceOf(const char *fileName, AvlTree<std::string, vector<int>> &tree) {
    ifstream input(fileName);
    string line;
    // get a whole line
    while(getline(input, line)) {
        stringstream streamer(line);
        // get the key
        string key;
        getline(streamer, key, char(31));

        // get all the values
        vector<int> documentIds;
        string temp;
        while (getline(streamer, temp, ',')) {
            if (!temp.empty()) {
                documentIds.push_back(stoi(temp));
            }
        }
        tree.insert(key, documentIds);
    }

}

void DocumentProcessor::pullFromPersistence() {
    cout << "pulling from persistence" << endl;
    cout << "pulling persistence of words" << endl;
    pullPersistenceOf("words.GouldGrace", words);
    cout << "pulling persistence of people" << endl;
    pullPersistenceOf("people.GouldGrace", people);
    cout << "pulling persistence of orgs" << endl;
    pullPersistenceOf("orgs.GouldGrace", org);
    cout << "pulling persistence of all docs" << endl;

    ifstream input("docs.GouldGrace");
    string line;
    while(getline(input, line)) {
        stringstream documentLine(line);
        string title;
        getline(documentLine, title, char(31));
        string publication;
        getline(documentLine, publication, char(31));
        string idNum;
        getline(documentLine, idNum, char(31));
        int id = stoi(idNum);
        string datePublished;
        getline(documentLine, datePublished, char(31));
        string text;
        getline(documentLine, text);

        doc document(title, publication, datePublished, text, id);
        allDocs.push_back(document);
    }

    cout << "Pulling persistence finished" << endl << "============" << endl;
}
