/*********************************************************************
** Author: Jonathan Nicolosi
** Date: February 24, 2016
** Description: ShiftVec implementation
*********************************************************************/

#include "ShiftVec.hpp"
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

/*********************************************************************
** Description: Getter that returns a vector.
**
*********************************************************************/

template <class T>
vector<T> ShiftVec<T>::getVec(){
    return myvector;
}

/*********************************************************************
** Description: Shift elements in vector to the right.
**
*********************************************************************/

template <class T>
void ShiftVec<T>::shiftRight(int shiftamount){
    int counter = 0;
    while(counter<shiftamount){
    myvector.insert(myvector.begin(),myvector.at(myvector.size()-1));
    myvector.pop_back();
    counter++;
    }

}

/*********************************************************************
** Description: Shift elements in vector to the left.
**
*********************************************************************/

template <class T>
void ShiftVec<T>::shiftLeft(int shiftamount){
    int counter = 0;
    while(counter<shiftamount){
    myvector.push_back(myvector.at(0));
    myvector.erase(myvector.begin());
    counter++;
    }

}








template class ShiftVec<int>;
template class ShiftVec<double>;
template class ShiftVec<bool>;
template class ShiftVec<std::string>;
