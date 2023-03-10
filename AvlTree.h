//
// Created by Ella Grace Collard on 11/8/22.
//

#ifndef FINALPROJEXAMPLES_AVLTREE_H
#define FINALPROJEXAMPLES_AVLTREE_H

//#define DEBUG

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;

template <typename Key, typename Value>
class AvlTree
{
private:
    struct AvlNode
    {
        Key key;
        Value value;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Key &ele, const Value& value, AvlNode *lt, AvlNode *rt, int h = 0)
                : key{ele}, value{value}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;

public:
    /**
     * @brief Construct a new Avl Tree object
     */
    AvlTree() : root{nullptr}
    {
    }

    /**
     * @brief Copy constructor
     */
    AvlTree(const AvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    ~AvlTree()
    {
        makeEmpty();
    }

    /**
     * Copy assignment operator
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
        return *this;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Key &x) const
    {
        return contains(x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }

    /**
     * Print the tree structure.
     */
    void prettyPrintTree() const
    {
        prettyPrintTree("", root, false);
    }

    /**
     * Make the tree empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Key &key, const Value& val)
    {
        insert(key, val, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Key &x)
    {
        remove(x, root);
    }

    Value& get(const Key& key)
    {
        return get(key, root);
    }

    void getMap(unordered_map<Key, Value>& map){
        getMap(map, root);
    }

private:
    void getMap(unordered_map<Key, Value>& map, AvlNode* c) {
        if (c == nullptr) {
            return;
        }
        else {
            map[c->key] = c->value;
            getMap(map, c->left);
            getMap(map, c->right);
        }
    }

    Value& get(const Key& key, AvlNode* current)
    {
        if (current == nullptr) {
            throw exception();
        }
        else {
            if (key == current->key) {
                return current->value;
            }
            else if (key < current->key) {
                return get(key, current->left);
            }
            else {
                return get(key, current->right);
            }
        }
    }
    /**
     * Internal method to insert into a subtree.
     * key is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Key &key, const Value& value, AvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{key, value, nullptr, nullptr, 0};
            return; // a single node is always balanced
        }

        if (key < t->key)
            insert(key, value, t->left);
        else if (t->key < key)
            insert(key, value, t->right);
        else
        {
        } // Duplicate; do nothing

        // This will call balance on the way back up the tree. It will only balance
        // once at node the where the tree got imbalanced (called node alpha in the textbook).
        balance(t);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
//    void remove(const Key &x, AvlNode *&t)
//    {
//        throw std::runtime_error("Not implemented yet!");
//        // same as in a binary search tree
//
//        // don't forget to balance
//        balance(t);
//    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode *findMin(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        if (t->left == nullptr)
            return t;

        return findMin(t->left);
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(const Key &x, AvlNode *t) const
    {
        if (t == nullptr)
            return false;

        else if (x < t->key)
            return contains(x, t->left);
        else if (t->key < x)
            return contains(x, t->right);
        else
            return true; // Match
    }
    /****** NONRECURSIVE VERSION*************************
        bool contains( const Key & x, AvlNode *t ) const
        {
            while( t != nullptr )
                if( x < t->key )
                    t = t->left;
                else if( t->key < x )
                    t = t->right;
                else
                    return true;    // Match

            return false;   // No match
        }
    *****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        return new AvlNode{t->key, t->value, clone(t->left), clone(t->right), t->height};
    }

    // Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const
    {
        if (node == nullptr)
            return;

        std::cout << prefix;
        std::cout << (isRight ? "?????????" : "?????????");
        // print the value of the node
        std::cout << node->key << std::endl;

        // enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "???   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "???   " : "    "), node->left, false);
    }

    // Avl manipulations

    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    static const int ALLOWED_IMBALANCE = 1; // 1 is the default; more will make balancing cheaper
    // but the search less efficient.

    // Assume t is balanced or within one of being balanced since we check this after each manipulation
    // t represents alpha in the textbook
    void balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)  // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t); // case 1 (outside)
            else
                doubleWithLeftChild(t); // case 2 (inside)
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t); // case 4 (outside)
            else
                doubleWithRightChild(t); // case 3 (inside)
        }

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2)
    {
#ifdef DEBUG
        cout << "need to rotateWithLeftChild for node " << k2->key << endl;
        cout << "Before:" << endl;
        prettyPrintTree();
#endif

        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
#ifdef DEBUG
        cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1)
    {
#ifdef DEBUG
        cout << "need to rotateWithRightChild for node " << k1->key << endl;
        cout << "Before:" << endl;
        prettyPrintTree();

#endif

        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
#ifdef DEBUG
        cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3)
    {
#ifdef DEBUG
        cout << "doubleWithLeftChild" << endl;
#endif
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1)
    {
#ifdef DEBUG
        cout << "doubleWithRightChild" << endl;
#endif
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};

#endif //FINALPROJEXAMPLES_AVLTREE_H
