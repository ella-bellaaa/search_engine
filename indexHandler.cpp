//
// Created by Ella Grace Collard on 11/14/22.
//

#include "indexHandler.h"
#include <fstream>
#include "porter2_stemmer.h"
#include <chrono>
using namespace Porter2Stemmer;
using namespace chrono;

indexHandler::indexHandler() {
    //to be implemented
    firstSearch = true;
}

void indexHandler::searchWord(string word) {
    stem(word);
    if (firstSearch) {
        firstSearch = false;
        if (processor.getWords().contains(word)) {
            currentSearch = processor.getWords().get(word);
        }
        else {
            currentSearch.clear();
        }
    }
    // if it is not the first search
    else {
        // find the intersection (what is common) between current search and searching for this new term

        // get the new search
        vector<int> newSearch;
        if (processor.getWords().contains(word))
            newSearch = processor.getWords().get(word);
        // if we have never seen the word before
        else {
            currentSearch.clear();
            return;
        }

        vector<int> intersection;
        // find the intersection
        for (auto &x : currentSearch) {
            for (auto &y : newSearch) {
                if (x == y) {
                    intersection.push_back(y);
                }
            }
        }

        currentSearch = intersection;
    }
}

void indexHandler::searchNotWord(string word) {
    // check if it is first search first
    stem(word);
    if (firstSearch) {
        firstSearch = false;
        if (processor.getWords().contains(word)) {
            // get the list of the word
            vector<int> wordList = processor.getWords().get(word);
            // compare it to the full list
            vector<int> intersection;
            for (auto & x : wordList) {
                bool seen = false;
                for (auto & y : processor.getAllDocs()) {
                    if (y.getId() == x) {
                        seen = true;
                    }
                }
                if (!seen) {
                    intersection.push_back(x);
                }
            }
            this->currentSearch = intersection;
        }
    }
    else {
        if (processor.getWords().contains(word)) {
            // get the list of the word
            vector<int> wordList = processor.getWords().get(word);

            // compare it to the current list
            vector<int> intersection;
            for (auto & x : wordList) {
                bool seen = false;
                for (auto & y : currentSearch) {
                    if (y == x) {
                        seen = true;
                    }
                }
                if (!seen) {
                    intersection.push_back(x);
                }
            }
            currentSearch = intersection;
        }
    }
}

void indexHandler::searchOrg(string org) {
    if (firstSearch) {
        firstSearch = false;
        if (processor.getOrg().contains(org)) {
            currentSearch = processor.getOrg().get(org);
        }
        else {
            currentSearch.clear();
        }
    }
        // if it is not the first search
    else {
        // find the intersection (what is common) between current search and searching for this new term

        // get the new search
        vector<int> newSearch;
        if (processor.getOrg().contains(org))
            newSearch = processor.getOrg().get(org);
            // if we have never seen the word before
        else {
            currentSearch.clear();
            return;
        }

        vector<int> intersection;
        // find the intersection
        for (auto &x : currentSearch) {
            for (auto &y : newSearch) {
                if (x == y) {
                    intersection.push_back(y);
                }
            }
        }

        currentSearch = intersection;
    }

}

void indexHandler::searchNotOrg(string org) {
    if (firstSearch) {
        firstSearch = false;
        if (processor.getOrg().contains(org)) {
            // get the list of the word
            vector<int> wordList = processor.getOrg().get(org);
            // compare it to the full list
            vector<int> intersection;
            for (auto & x : wordList) {
                bool seen = false;
                for (auto & y : processor.getAllDocs()) {
                    if (y.getId() == x) {
                        seen = true;
                    }
                }
                if (!seen) {
                    intersection.push_back(x);
                }
            }
            this->currentSearch = intersection;
        }
    }
    else {
        if (processor.getOrg().contains(org)) {
            // get the list of the word
            vector<int> wordList = processor.getOrg().get(org);

            // compare it to the current list
            vector<int> intersection;
            for (auto & x : wordList) {
                bool seen = false;
                for (auto & y : currentSearch) {
                    if (y == x) {
                        seen = true;
                    }
                }
                if (!seen) {
                    intersection.push_back(x);
                }
            }
            currentSearch = intersection;
        }
    }
}

void indexHandler::searchPerson(string person) {
    if (firstSearch) {
        firstSearch = false;
        if (processor.getPeople().contains(person)) {
            currentSearch = processor.getPeople().get(person);
        }
        else {
            currentSearch.clear();
        }
    }
        // if it is not the first search
    else {
        // find the intersection (what is common) between current search and searching for this new term

        // get the new search
        vector<int> newSearch;
        if (processor.getPeople().contains(person))
            newSearch = processor.getPeople().get(person);
            // if we have never seen the word before
        else {
            currentSearch.clear();
            return;
        }

        vector<int> intersection;
        // find the intersection
        for (auto &x : currentSearch) {
            for (auto &y : newSearch) {
                if (x == y) {
                    intersection.push_back(y);
                }
            }
        }

        currentSearch = intersection;
    }

}

void indexHandler::searchNotPerson(string person) {
    if (firstSearch) {
        firstSearch = false;
        if (processor.getPeople().contains(person)) {
            // get the list of the word
            vector<int> wordList = processor.getPeople().get(person);
            // compare it to the full list
            vector<int> intersection;
            for (auto & x : wordList) {
                bool seen = false;
                for (auto & y : processor.getAllDocs()) {
                    if (y.getId() == x) {
                        seen = true;
                    }
                }
                if (!seen) {
                    intersection.push_back(x);
                }
            }
            this->currentSearch = intersection;
        }
    }
    else {
        if (processor.getPeople().contains(person)) {
            // get the list of the word
            vector<int> wordList = processor.getPeople().get(person);

            // compare it to the current list
            vector<int> intersection;
            for (auto & x : wordList) {
                bool seen = false;
                for (auto & y : currentSearch) {
                    if (y == x) {
                        seen = true;
                    }
                }
                if (!seen) {
                    intersection.push_back(x);
                }
            }
            currentSearch = intersection;
        }
    }
}

void indexHandler::createIndex(const char *fileName) {
    auto start = chrono::high_resolution_clock::now();
    processor.processDocuments(fileName);
    auto end = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::seconds>(end - start).count();
    cout << "Parsing Time was " << duration << " seconds" << endl;
    this->parsingTime = duration;
}

void indexHandler::createPersistence() {
    processor.createPersistence();
}

void indexHandler::pullFromPersistence() {
    processor.pullFromPersistence();
}

DocumentProcessor &indexHandler::getProcessor(){
    return processor;
}

void indexHandler::setProcessor(const DocumentProcessor &processor) {
    indexHandler::processor = processor;
}

bool indexHandler::isFirstSearch() const {
    return firstSearch;
}

void indexHandler::setFirstSearch(bool firstSearch) {
    indexHandler::firstSearch = firstSearch;
}

const vector<int> &indexHandler::getCurrentSearch() const {
    return currentSearch;
}

void indexHandler::setCurrentSearch(const vector<int> &currentSearch) {
    indexHandler::currentSearch = currentSearch;
}

vector<doc> indexHandler::getDocumentList() {
    vector<doc> returnMe;
    for (auto & index : currentSearch) {
        returnMe.push_back(processor.getAllDocs()[index]);
    }
    return returnMe;
}

long long indexHandler::getUniqueWordCount() {
    unordered_map<string, vector<int>> wordMap;
    processor.getWords().getMap(wordMap);
    return wordMap.size();
}

