//
// Created by Ella Grace Collard on 11/14/22.
//

#ifndef FINALPROJEXAMPLES_USERINTERFACE_H
#define FINALPROJEXAMPLES_USERINTERFACE_H

#include <string>
#include "indexHandler.h"
#include <sstream>
using namespace std;

class userInterface {
private:
    bool indexParsed = false;
public:
    indexHandler handler;
    string decipherInput(string);
    string promptUser();
    void start();
    void search();
    void parseIndex();
    void saveIndex();
    void loadPersistence();
    void printStats();
    void handleQuery(string query);
    void handleTerm(string term);
    void printResult();
};



#endif //FINALPROJEXAMPLES_USERINTERFACE_H
