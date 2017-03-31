/*********************************************************************
** Author: Jonathan Nicolosi
** Date: February 24, 2016
** Description: ShiftVec template class with a vector as a data member.
*********************************************************************/

#ifndef SHIFTVEC_HPP_INCLUDED
#define SHIFTVEC_HPP_INCLUDED
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>


using namespace std;

template <class T>
class ShiftVec{

private:
    vector<T> myvector; //Data member

public:
    ShiftVec(vector<T> v){ //Constructor declaration.
        myvector = v;

    }
/*********************************************************************
** Description: Function declarations
**
*********************************************************************/
    vector<T> getVec();
    void shiftRight(int);
    void shiftLeft(int);

};



#endif // SHIFTVEC_HPP_INCLUDED
