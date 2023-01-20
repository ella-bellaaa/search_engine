//
// Created by Ella Grace Collard on 11/8/22.
//

#ifndef FINALPROJEXAMPLES_DOCUMENTPROCESSOR_H
#define FINALPROJEXAMPLES_DOCUMENTPROCESSOR_H
#include "doc.h"
#include "AvlTree.h"
#include <vector>

using namespace std;

class DocumentProcessor {
public:
    void processDocuments(const char* filePath);

    AvlTree<string, vector<int>> &getWords();

    void setWords(const AvlTree<string, vector<int>> &words);

    AvlTree<string, vector<int>> &getPeople();

    void setPeople(const AvlTree<string, vector<int>> &people);

    AvlTree<string, vector<int>> &getOrg();

    void setOrg(const AvlTree<string, vector<int>> &org);

    void createPersistence();

    void pullFromPersistence();

    vector<doc>& getAllDocs() { return allDocs; }

    void makePersistenceOf(const char* fileName, AvlTree<string, vector<int>>& tree);

    void pullPersistenceOf(const char* fileName, AvlTree<string, vector<int>>& tree);
private:
    AvlTree<string, vector<int>> words;
    AvlTree<string, vector<int>> people;
    AvlTree<string, vector<int>> org;
    vector<doc> allDocs;
};


#endif //FINALPROJEXAMPLES_DOCUMENTPROCESSOR_H
