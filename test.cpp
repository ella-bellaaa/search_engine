//
// Created by Caleb Gould on 11/13/22.
//
#include "catch.hpp"
#include "AvlTree.h"
// add includes
#include "indexHandler.h"
#include "userInterface.h"

TEST_CASE("Check that Avl Tree works", "[AvlTree]")
{
    SECTION("testing copy constructor") {
        AvlTree<int,int> tree;
        tree.insert(1,2);

        AvlTree<int,int> copyTree(tree);
        CHECK(tree.get(1) == copyTree.get(1));
        CHECK(copyTree.isEmpty() == false);
    }
    SECTION("testing copy assignment operator"){
        AvlTree<int,int> tree;
        tree.insert(1,2);

        AvlTree<int,int> copyTree = tree;
        CHECK(tree.get(1) == copyTree.get(1));
        CHECK(copyTree.isEmpty() == false);
    }
    SECTION("testing contains"){
        AvlTree<int,int> tree;
        tree.insert(1,2);
        tree.insert(2,4);

        CHECK(tree.contains(2));
        CHECK(tree.isEmpty() == false);
    }
    SECTION("testing tree is empty"){
        AvlTree<int,int> tree;
        tree.insert(1,2);

        AvlTree<int,int> emptyTree;

        CHECK(tree.isEmpty() == false);
        CHECK(emptyTree.isEmpty() == true);
    }
    SECTION("testing makeEmpty"){
        AvlTree<int,int> tree1;
        tree1.insert(1,5);
        tree1.makeEmpty();

        AvlTree<int,int> tree2;
        tree2.insert(1,5);
        tree2.insert(2,10);
        tree2.makeEmpty();

        CHECK(tree1.isEmpty() == true);
        CHECK(tree2.isEmpty() == true);
    }
    SECTION("testing insert"){
        AvlTree<int,int> tree;
        tree.insert(1,2);

        CHECK(tree.isEmpty() == false);
        CHECK(tree.get(1) == 2);
    }
    SECTION("testing get"){
        AvlTree<int,int> tree;
        tree.insert(1,2);
        tree.insert(2,4);

        CHECK(tree.get(1) == 2);
        CHECK(tree.get(2) == 4);

    }

}

TEST_CASE("index handler tests", "[indexHandler]") {
    indexHandler h;
    h.createIndex("sample_data");
    // test that the handler is on the first search
    CHECK(h.isFirstSearch());
    string w = "Feb";
    h.searchWord(w);
    CHECK(!h.isFirstSearch());
    CHECK(h.getDocumentList().size() > 0);
}

TEST_CASE("Whole System test", "[wholeSystem]") {
    userInterface ui;
    ui.handler.createIndex("sample_data");
    string query = "ORG:reuters EARNINGS";
    CHECK(ui.handler.isFirstSearch());

    ui.handleQuery(query);

    CHECK(ui.handler.getDocumentList().size() == 3);
    CHECK(ui.handler.isFirstSearch() == false);

}