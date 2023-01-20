//
// Created by Ella Grace Collard on 11/14/22.
//

#include "userInterface.h"
#include <iostream>
#include <string>
#include "porter2_stemmer.h"
#include <chrono>

using namespace chrono;
using namespace std;
using namespace Porter2Stemmer;

string userInterface::decipherInput(string input) {
    return string();
}

string userInterface::promptUser() {
    cout << "enter 1 to parse an index" << endl;
    cout << "enter 2 to save current index as persistence" << endl;
    cout << "enter 3 to load persistence index" << endl;
    cout << "enter 4 to see statistics" << endl;
    cout << "enter \"E\" to exit" << endl;
    string input;
    getline(cin, input);
    return input;
}

void userInterface::start() {
    cout << "Welcome to the search engine!" << endl;

    while (true) {
        string input = promptUser();
        if (input == "E") {
            break;
        }
        else if (input == "1") {
            parseIndex();
            indexParsed = true;
            search();
        }
        else if (input == "2") {
            if (indexParsed)
                saveIndex();
            else
                cerr << "You have not parsed an index. Do that first!" << endl;
        }
        else if (input == "3") {
            loadPersistence();
            search();
        }
        else if (input == "4") {
            printStats();
        }
    }
}

void userInterface::search() {
    while (true) {
        cout << "enter a query: " << endl;
        string query;
        getline(cin, query);

        auto start = chrono::high_resolution_clock::now();
        handleQuery(query);
        auto end = chrono::high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();
        cout << "Query took " << duration << " microseconds" << endl;
        printResult();
        handler.setFirstSearch(true);

        cout << "Do you want to search again? (y/n)" << endl;
        string answer;
        getline(cin, answer);
        if (answer == "y" || answer == "Y") {
            continue;
        }
        else {
            break;
        }
    }
}

void userInterface::parseIndex() {
    cout << "what file would you like to parse? " << endl;
    string file;
    getline(cin, file);
    handler.createIndex(file.c_str());
}

void userInterface::saveIndex() {
    handler.createPersistence();
}

void userInterface::loadPersistence() {
    handler.pullFromPersistence();
}

void userInterface::printStats() {
    cout << "printing stats" << endl;
    cout << "Time to parse index: " << handler.getParsingTime() << " seconds" << endl;
    cout << "number of articles processed: " << handler.getProcessor().getAllDocs().size() << endl;
    cout << "number of unique words: " << handler.getUniqueWordCount() << endl;
}

void userInterface::handleQuery(string query) {
    // we have a query, we need to split it by space and call the right fuctions on the  handler.
    stringstream ss(query);
    string term;
    while (getline(ss, term, ' ')) {
        handleTerm(term);
    }
}

// ORG:eu
// -ORG:eu - all the docs that don't contain eu
void userInterface::handleTerm(string term) {
    // we have a term, figure out if it is seenNegativeSign, a person, org, or word, and call the right function

    // figure out if the term is seenNegativeSign
    bool seenNegativeSign = false;
    if (term[0] == '-') {
        seenNegativeSign = true;
        term = string(term.c_str() + 1);
    }

    // searching for a person or org, it has a colon in it
    if (term.find(':') != string::npos) {
        // searching for person
        if (term[0] == 'P') {
            // remove PERSON:
            term = string(term.c_str() + 7);
            if (seenNegativeSign) {
                handler.searchNotPerson(term);
            }
            else {
                handler.searchPerson(term);
            }
        }
        // searching for org
        else if (term[0] == 'O') {
            term = string(term.c_str() + 4);
            if (seenNegativeSign) {
                handler.searchNotOrg(term);
            }
            else {
                handler.searchOrg(term);
            }
        }
    }
    // searching for a word
    else {
        stem(term);
        if (seenNegativeSign) {
            handler.searchNotWord(term);
        }
        else {
            handler.searchWord(term);
        }
    }
}

void userInterface::printResult() {
    vector<doc> results = handler.getDocumentList();
    int iter = 1;
    cout << "number of results: " << results.size() << endl;
    for (auto & x : results) {
        if (iter == 16) break;
        cout << iter << ": " << x.getTitle() << endl;
        iter++;
    }
    if (results.size() > 0) {
choice:
        cout << "What document would you like to see the text of?" << endl;
        string temp;
        getline(cin, temp);
        int choice = stoi(temp);
        if (choice < 0 || choice >= results.size()) {
            cout << "bad choice. Try again." << endl;
            goto choice;
        }
        cout << results[choice - 1].getText() << endl;
    }
}
