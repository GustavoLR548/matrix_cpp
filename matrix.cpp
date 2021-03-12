#include<iostream>
#include"matrix.hpp"


//Constructor 1: no size specified, creating 3x3 matrix
template <typename T>
Matrix<T>::Matrix() {
    this->number_of_columns = MIN;
    this->number_of_rows    = MIN;
    build_matrix();
}

//Constructor 2: creating a NxN matrix
template <typename T>
Matrix<T>::Matrix(short n) {
    if(n < MIN) {
        n = MIN;
    }
    else {
        this->number_of_columns = this->number_of_rows = n;
    }

    build_matrix();
}

//Constructor 3: creating a CxR matrix
template <typename T>
Matrix<T>::Matrix(short c, short r) {

    if( c < MIN || r < MIN ) {
        if( c < MIN) {
            c = MIN;
        }
        if ( r < MIN) {
            r = MIN;
        }
    }
    else {
        this->number_of_columns = c;
        this->number_of_rows    = r;
    }

    build_matrix();
}

template <typename T> 
Matrix<T>::~Matrix() {
    free(this->first);
}


template <typename T>
short Matrix<T>::get_number_of_columns() {
    return this->number_of_columns;
}

template <typename T>
short Matrix<T>::get_number_of_rows() {
    return this->number_of_rows;
}

//Creating all linked cells to the first cell of the Matrix
template <typename T>
void Matrix<T>::build_matrix() {

    //Creating the first element
    this->first = new Cell<T>();
    Cell<T>* tmp = this->first;

    // -1 because the first element was already created
    short r = this->number_of_rows    - 1;
    short c = this->number_of_columns - 1;

    expand_horizontally(tmp,r);

    //reset the pointer to link to the first cell
    tmp = this->first;

    //Deploy consecutive rows of cells in the Matrix
    for (int i = 0; i < c;i++) {
        Cell<T>* tmp2 = expand_vertically(tmp);
        expand_horizontally_linked_up(tmp2,r);
    }
}

//Expand the matrix horizontally
template <typename T>
void Matrix<T>::expand_horizontally(Cell<T>* c, int n) {

    for(int i = 0 ; i < n; i++) {
        Cell<T>* tmp = new Cell<T>();

        c->right  = tmp;
        tmp->left = c;

        c = c->right;
    }
}   

//Expand the matrix horizontally, and link the same cells
//to the ones on the top
template <typename T>
void Matrix<T>::expand_horizontally_linked_up(Cell<T>* c,int n) {

    for(int i = 0; i < n; i++) {
        Cell<T>* tmp  = new Cell<T>();

        //Linking cells horizontally
        c->right = tmp;
        tmp->left  = c;

        //Linking cells vertically
        c->up->right->down = tmp;
        tmp->up = c->up->right;

        //Moving the pointer to the right, to continue to create the row
        c = c->right;
    }
}

//Expand the matrix vertically, and return the pointer
//for the last cell
template <typename T>
Cell<T>* Matrix<T>::expand_vertically(Cell<T>* c, int n) {
    Cell<T>* tmp;
    for(int i = 0; i < n; i++) {
        tmp = new Cell<T>();

        c->down = tmp;
        tmp->up  = c;

    }

    return tmp;
}

//Search the position the cell in the position (x,y)
template <typename T>
Cell<T>* Matrix<T>:: search(int x, int y) {
    Cell<T>* resp = this->first;

    for(int i = 0; i < y;i++, resp = resp->down);
    for(int i = 0; i < x;i++, resp = resp->right);

    return resp;
}

//Verify if a set coordenate(x,y) is outside of the bounds of the matrix
template <typename T>
bool Matrix<T>::is_outside_matrix(int x,int y) {
    return (x > this->number_of_rows || y > this->number_of_columns || x < 0 || y < 0);
}

//Print the Matrix using std::cout
template <typename T>
void Matrix<T>::print() {
    for(Cell<T>* i = this->first; i != NULL ; i = i->down ) {
        for(Cell<T>* j = i; j != NULL ; j = j->right ) 
            std::cout << j->getElement() << " " ;
        
        std::cout << "\n" ; //Add spacing in between the columns
    }
    std::cout << "\n" ; //Add spacing after the final column
}

//Return a element T in the position (x,y)
template <typename T>
T Matrix<T>::get(int x,int y) {
    T resp;

    if(is_outside_matrix(x,y)) 
        return resp;
    
    resp = search(x,y)->getElement();

    return resp;
}

//Insert a element T in the position(x,y)
template <typename T>
bool Matrix<T>::insert(T element,int x,int y) {
    if(is_outside_matrix(x,y)) 
        return false;

    Cell<T>* tmp = search(x,y);

    tmp->setElement(element);

    return true;
}

//Expand the matrix both vertically and horizontally
template <typename T>
void Matrix<T>::expand_matrix(int expanded) {
    expand_matrix_horizontally(expanded);
    expand_matrix_vertically(expanded);

}

//Expand the matrix only horizontally
template <typename T>
void Matrix<T>::expand_matrix_horizontally(int expanded) {

    number_of_rows    += expanded;
    Cell<T>* tmp = this->first;

    for(/**/; tmp->right != NULL; tmp = tmp->right);
    
    Cell<T>* tmp2 = tmp;

    expand_horizontally(tmp2,expanded);

    do {
        tmp2 = tmp->down;
        expand_horizontally_linked_up(tmp2,expanded);
    } while(tmp2->down != NULL);

    tmp2 = NULL;
    tmp  = NULL;
}

//Expand the matrix only vertically
template <typename T>
void Matrix<T>::expand_matrix_vertically(int expanded) {

    number_of_columns += expanded;
    Cell<T>* tmp = this->first;

    for(/**/; tmp->down != NULL; tmp = tmp->down);
    
    for (int i = 0; i < expanded;i++) {
        tmp = expand_vertically(tmp);
        expand_horizontally_linked_up(tmp,number_of_columns-1);
    }
}
