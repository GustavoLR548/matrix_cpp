#include"cell.hpp"

#include<iostream>

template <typename T>
Cell<T>::Cell(T element) {
    this->left    = nullptr;
    this->right   = nullptr;
    this->up      = nullptr;
    this->down    = nullptr;

    this->element = element;
}

template <typename T> 
Cell<T>::~Cell() {
    if(!left) 
        delete left;
    if(!right) 
        delete right;
    if(!up) 
        delete up;
    if(!down) 
        delete down;
}

template <typename T>
T Cell<T>::getElement() {
    return this->element;
}

template <typename T>
void Cell<T>::setElement(T element) {
    this->element = element;
}
