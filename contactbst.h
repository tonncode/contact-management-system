#ifndef ContactBST_H
#define ContactBST_H

#include<iostream>
#include "myvector.h"
#include "contact.h"
//#include "myvector.h"  create this header file where you define the vector class

using namespace std;

class Node
{
    private:
        MyVector<Contact>* contactVector;
        Node* left;
        Node* right;
    public:
        Node(string key, MyVector<Contact>* contactVector);
        ~Node();
        string key;
        string getKey() { return this->key;}
        MyVector<Contact>* getData() { return this->contactVector;}
        friend class ContactBST;
};

//=============================================================================
class ContactBST
{
    private:
        Node* root;
        MyVector<Contact>* contactsinorder = new MyVector<Contact>;
        int size;
    public:
        ContactBST();                                    //constructor
        ~ContactBST();                                    //destructor
        Node* getRoot() {return this->root;}                        //returns the root of the Tree
        Node* add(Node* ptr,string key, Contact* data);        //add key into tree/subtree with root ptr
        void insert_collection();
        Node* update(Node* ptr, string key); //Edit the node with key
        Node* del(Node* ptr,string key);        //Delete a node with key from the tree/subtree with root
        Node* findMinRight(Node* ptr);
        bool findKey(Node *ptr,string key);
        Node* search(Node* ptr,string key);    //Find and returns the node with key
        bool markFav(Node* ptr, string key);  //Mark a contact as favorite
        void markFav_helper(Node *ptr, string key);
        bool unmarkFav(Node* ptr, string key);  //Unmark a contact as favorite
        void printASC(Node* ptr);            //Print the data at nodes in an ascending order
        void printDES(Node* ptr);            //Print the data at nodes in a descending order
        void printFav(Node* ptr);           //Print the favorite data at nodes in an ascending order
        int importCSV(Node* ptr, string path); //Load all the contacts from the CSV file to the BST
        int exportCSV(Node* ptr, string path); //Export all the contacts from the BST to a CSV file in an ascending order
        void inorder(Node* ptr);
    public:    //helper methods
        void insert_helper(string key, Contact* data);                //Helper method for insert method
        void remove_helper(string key);                                //Helper method for remove method
    private:
        void printTreeHelper(string* A, bool* B, Node* ptr, int n); //Helper method for PrintTree()
};

#endif
