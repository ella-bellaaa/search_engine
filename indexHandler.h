//
// Created by Ella Grace Collard on 11/14/22.
//

#ifndef FINALPROJEXAMPLES_INDEXHANDLER_H
#define FINALPROJEXAMPLES_INDEXHANDLER_H
#include "AvlTree.h"
#include "doc.h"
#include <string>
#include "DocumentProcessor.h"
#include <vector>
using namespace std;

class indexHandler {
public:
    DocumentProcessor &getProcessor();

    void setProcessor(const DocumentProcessor &processor);

    bool isFirstSearch() const;

    void setFirstSearch(bool firstSearch);

    const vector<int> &getCurrentSearch() const;

    void setCurrentSearch(const vector<int> &currentSearch);

    indexHandler();
    void searchWord(string word);
    void searchNotWord(string word);
    void searchOrg(string org);
    void searchNotOrg(string org);
    void searchPerson(string person);
    void searchNotPerson(string person);
    void createIndex(const char* fileName);
    void createPersistence();
    void pullFromPersistence();
    vector<doc> getDocumentList();
    long long getUniqueWordCount();
    long long getParsingTime() const {return parsingTime;}
private:
    DocumentProcessor processor;
    bool firstSearch;
    vector<int> currentSearch;
    long long parsingTime;

};
#endif //FINALPROJEXAMPLES_INDEXHANDLER_H