//
//  myvector.h
//  project.cpp
//
//  Created by Assylbek Saduakhassov on 14/04/2022.
//

#ifndef myvector_h
#define myvector_h

#include<iostream>
#include "contact.h"
using namespace std;

template <typename T>
class MyVector
{
    private:
        T **data;                        //pointer to int(array) to store elements
        int v_size;                        //current size of vector (number of elements in vector)
        int v_capacity;                    //capacity of vector
    public:
        MyVector();                        //No argument constructor
        ~MyVector();                    //Destructor
        void push_back(T *element);        //Add an element at the end of vector
        void erase(int index);            //Removes an element from the index
        T* at(int index);                //return reference of the element at index
        int size() const;                //Return current size of vector
        void recapacity(int ncap);
};

template <typename T>
MyVector<T>::MyVector()
{
    data = new T *[0];
    v_size = 0;
    v_capacity = 0;
}

template <typename T>
MyVector<T>::~MyVector()
{
    for (int i=0; i<v_size; ++i) {
        delete data[i];
    }
    delete [] data;
}

template <typename T>
void MyVector<T>::erase(int index)
{
    if (index > v_size - 1 || index < 0)
    {
        cout<<"Invalid input..."<<endl;
    }
    else
    {
        for (int j = index + 1; j <= v_size - 1; j++)
        {
            data[j-1] = data[j];
        }
        v_size = v_size - 1;
    }
}

template <typename T>
T* MyVector<T>::at(int index)
{
    if (index > v_size - 1 || index < 0)
    {
        cout<<"Invalid input..."<<endl;
        return nullptr;
    }
    else
    {
        return data[index];
    }
}

template <typename T>
int MyVector<T>::size() const
{
    return v_size;
}

template <typename T>
void MyVector<T>::push_back(T *element)
{
    if (v_size >= v_capacity)
    {
        recapacity(max(1, 2 * v_capacity));
    }
    data[v_size] = element;
    v_size++;
}

template <typename T>
void MyVector<T>::recapacity(int ncap)
{
    T** temp = new T *[v_size];
    for (int i = 0; i < v_size; ++i)
    {
        temp[i] = data[i];
    }
    delete [] data;
    data = new T *[ncap];
    v_capacity = ncap;
    for (int i = 0; i < v_size; ++i)
    {
        data[i] = temp[i];
    }
    delete [] temp;
}

#endif /* myvector_h */
