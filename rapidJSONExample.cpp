/**
 * Example code related to final project
 */
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "userInterface.h"
#include "DocumentProcessor.h"
#include "userInterface.h"

int main(int argc, char** argv)
{
    if (argc == 1) {
        Catch::Session().run();
    }
    string arg = argv[1];

    if (arg == "ui") {
        userInterface interface;
        interface.start();
    }
    else if (arg == "query") {
        string query = argv[2];
        userInterface interface;
        interface.loadPersistence();
        interface.handleQuery(query);
        interface.printResult();
    }
    else if (arg == "index") {
        string index = argv[2];
        userInterface interface;
        interface.handler.createIndex(index.c_str());
        interface.handler.createPersistence();
    }

    return 0;
}




