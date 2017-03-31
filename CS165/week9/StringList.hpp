/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 2, 2016
** Description: StringList class declaration
*********************************************************************/

#ifndef STRINGLIST_HPP_INCLUDED
#define STRINGLIST_HPP_INCLUDED
#include <iostream>
#include <vector>
using namespace std;

/*********************************************************************
** Description: Declare StringList class
**
*********************************************************************/

class StringList {
protected:
    struct Node {
        string value;
        Node *next;
        Node(string val, Node *nxt=NULL) {
            value = val;
            next = nxt;
        }
    };
    Node *head;
public:
    StringList();
    StringList(StringList &obj);
    ~StringList();
    void add(string);
    //void displayList();
    int positionOf(string);
    vector<string> getAsVector();
    bool setNodeVal(int, string);
};

#endif // STRINGLIST_HPP_INCLUDED
