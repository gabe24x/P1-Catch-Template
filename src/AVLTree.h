#include "Student.h"
#include <algorithm>
#include <utility>
#include <stack>
#include <iostream>
#pragma once
using namespace std;

class AVLTree {
    // Nested node struct with student object holding data, left/right child pointers, and height variable
    struct Node {
        Student student;
        Node* left;
        Node* right;
        int height;
        // Node constructor
        Node(Student student);
    };

    // Node pointer to the root of the tree
    Node* head;

    // Private functions
    Node* rotateRight(Node* root);
    Node* rotateLeft(Node* root);
    int getBalanceFactor(Node* root);
    int getHeight(Node* root);
    Node* insertNode(Node* root, Student student);
    Node* deleteNode(Node* root, string ID);
    string stringInOrder(Node* root);
    string stringPreOrder(Node* root);
    string stringPostOrder(Node* root);
    void fillInorder(Node* root, vector<string>& ids);

public:
    // Public functions
    AVLTree();
    void insert(string name, string ID);
    void remove(string ID);
    void searchID(string ID);
    void searchName(string name);
    void searchNameHelper(Node* root, string name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder(int N);
};
