/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 2, 2016
** Description: StringList implementation
*********************************************************************/

#include <iostream>
#include <vector>
#include "StringList.hpp"

using namespace std;

/*********************************************************************
** Description: Default constructor
**
*********************************************************************/

StringList::StringList() {
    head = NULL;
}

/*********************************************************************
** Description: Copy Constructor
**
*********************************************************************/

StringList::StringList(StringList &obj) {
    if (obj.head == NULL) {
        head = NULL;
    }
    else {
        head = new Node(obj.head->value);
        Node *current = head;
        Node *objHead = obj.head;
        Node *currentObj = objHead;
        while (currentObj->next != NULL) {
            current->next = new Node(currentObj->next->value);
            currentObj = currentObj->next;
            current = current->next;
        }
    }
}

/*********************************************************************
** Description: Destructor
**
*********************************************************************/

StringList::~StringList() {
    Node *current = head;
    while (current != NULL) {
        Node *garbage = current;
        current = current->next;
        delete garbage;
    }
}

/*********************************************************************
** Description: Appends a node to the StringList
**
*********************************************************************/

void StringList::add(string s)
{
Node *newNode;
Node *nodePtr;
Node *previousNode = NULL;

newNode = new Node(s, newNode);//creates a new node
newNode->value = s;//adds string passed to function to list
newNode->next = NULL;//makes next value in list NULL

//if its the first value, it is equal to the new value
if(!head)
head = newNode;

else
{
//position pointer at the head of the list, initializes prevNode to null
nodePtr = head;
previousNode = NULL;

//skip the nodes whose value is < the passed string value
while(nodePtr != NULL && nodePtr->value < s)
{
previousNode = nodePtr;
nodePtr = nodePtr->next;
}

//if the new node will be the first, insert it before the others
if (previousNode == NULL)
{
head = newNode;
newNode->next = nodePtr;
}

else //insert it after the aforementioned nodes
{
previousNode->next = newNode;
newNode->next = nodePtr;
}
}
};

/*********************************************************************
** Description: Prints the list. Used for debugging.
**
*********************************************************************/

// void StringList::displayList()
// {
	// Node *nodePtr;
	// nodePtr = head;
	// while (nodePtr)
	// {
		// cout << nodePtr->value << endl;
		// nodePtr = nodePtr->next;
	// }
// }

/*********************************************************************
** Description: Returns a vector with all of the values in the
** StringList in the same order.
*********************************************************************/

vector<string> StringList::getAsVector(){
    vector<string> s;
    Node *nodePtr;
    nodePtr = head;
    while(nodePtr){
        s.push_back(nodePtr->value);
        nodePtr = nodePtr->next;
    }

    return s;
}

/*********************************************************************
** Description: Returns the zero-based position of a node containing
** the value specified by the user.
*********************************************************************/

int StringList::positionOf(string s){

    int pos = 0;
    if(head == NULL)
        return -1;
    else{
        Node *ptr = head;
        while(ptr!=NULL && ptr->value!=s){
            ptr = ptr->next;
            pos++;
        }
    return pos;
    }
}

/*********************************************************************
** Description: Sets the value of the node at a zero-based position
** specified by the user.
*********************************************************************/

bool StringList::setNodeVal(int i, string s){
    int count = 0;
    Node* p = head;
    while (p != NULL)
    {
    count++;

    p = p->next;
    }
    if(i>=count){

        return false;
    }

    Node *ptr = head;

    int pos = -1;

    while(pos!=i+1){

        ptr = ptr->next;
        if(i==pos){

            head->value = s;
            return true;
        }

        pos++;
    }

}





