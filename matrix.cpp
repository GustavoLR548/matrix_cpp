#include<iostream>
#include<cstdlib>
#include"matrix.hpp"

//Constructor 1: no size specified, creating 3x3 matrix
template <typename T>
Matrix<T>::Matrix(T default_value) {
    this->default_value = default_value;

    this->last_searched_c = 0;
    this->last_searched_r = 0;

    this->number_of_columns = MIN;
    this->number_of_rows    = MIN;
    build_matrix(default_value);
}

//Constructor 2: creating a NxN matrix
template <typename T>
Matrix<T>::Matrix(short n,T default_value) {
    this->default_value = default_value;

    this->last_searched_c = 0;
    this->last_searched_r = 0;

    if(n < MIN) {
        n = MIN;
    }
    else {
        this->number_of_columns = this->number_of_rows = n;
    }

    build_matrix(default_value);
}

//Constructor 3: creating a CxR matrix
template <typename T>
Matrix<T>::Matrix(short c, short r,T default_value) {
    this->default_value = default_value;

    this->last_searched_c = 0;
    this->last_searched_r = 0;

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
    build_matrix(default_value);
}

template <typename T> 
Matrix<T>::~Matrix() {
    free(this->first);
}


template <typename T>
counter Matrix<T>::get_number_of_columns() {
    return this->number_of_columns;
}

template <typename T>
counter Matrix<T>::get_number_of_rows() {
    return this->number_of_rows;
}

//Creating all linked cells to the first cell of the Matrix
template <typename T>
void Matrix<T>::build_matrix(T default_value) {

    //Creating the first element
    this->first = new Cell<T>(default_value);
    Cell<T>* tmp = this->first;
    this->last_searched_cell = this->first;

    // -1 because the first element was already created
    short r = this->number_of_rows    - 1;
    short c = this->number_of_columns - 1;

    expand_horizontally(tmp,r,default_value);

    //reset the pointer to link to the first cell
    tmp = this->first;

    //Deploy consecutive rows of cells in the Matrix
    for (int i = 0; i < c ;i++) {
        Cell<T>* tmp2 = expand_vertically(tmp,1,default_value);
        expand_horizontally_linked_up(tmp2,r,default_value);
        tmp = tmp->down;
    }
}

//Expand the matrix horizontally
template <typename T>
void Matrix<T>::expand_horizontally(Cell<T>* c, int n,T default_value) {

    for(int i = 0 ; i < n; i++) {
        Cell<T>* tmp = new Cell<T>(default_value);

        c->right  = tmp;
        tmp->left = c;

        c = c->right;
    }
}   

//Expand the matrix horizontally, and link the same cells
//to the ones on the top
template <typename T>
void Matrix<T>::expand_horizontally_linked_up(Cell<T>* c,int n,T default_value) {

    for(int i = 0; i < n; i++) {
        Cell<T>* tmp  = new Cell<T>(default_value);

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
Cell<T>* Matrix<T>::expand_vertically(Cell<T>* c, int n,T default_value) {
    Cell<T>* tmp;
    for(int i = 0; i < n; i++) {
        tmp = new Cell<T>(default_value);

        c->down = tmp;
        tmp->up  = c;

    }

    return tmp;
}

//Search the position the cell in the position (x,y)
template <typename T>
Cell<T>* Matrix<T>:: search(int x, int y, Cell<T>* resp) {

    if(y < 0) 
        for(int i = 0; i < abs(y);i++, resp = resp->up);
    else 
        for(int i = 0; i < y;i++, resp = resp->down);
    
    if(x < 0)
        for(int i = 0; i < abs(x);i++, resp = resp->left);
    else 
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
    T resp = default_value;

    if(is_outside_matrix(x,y)) 
        return resp;

    int distance_x = x - this->last_searched_r;
    int distance_y = y - this->last_searched_c;

    if(abs(distance_x) <= x || abs(distance_y) <= y) {
        this->last_searched_cell = search(distance_x,distance_y,this->last_searched_cell);
        resp = this->last_searched_cell->getElement();
    } else { 
        Cell<T>* tmp = this->first;
        this->last_searched_cell = search(x,y,tmp);
        resp = this->last_searched_cell->getElement();
    }

    this->last_searched_r = x;
    this->last_searched_c = y;

    return resp;
}

//Insert a element T in the position(x,y)
template <typename T>
bool Matrix<T>::insert(T element,int x,int y) {
    if(is_outside_matrix(x,y)) 
        return false;

    Cell<T>* tmp = search(x,y,this->first);

    tmp->setElement(element);

    return true;
}

//Fill the matrix with one value
template <typename T> 
void Matrix<T>::fill(T element) {

    for(Cell<T>* i = this->first; i != NULL ; i = i->down ) 
        for(Cell<T>* j = i; j != NULL ; j = j->right ) 
            j->setElement(element);
    
}

//Expand the matrix both vertically and horizontally
template <typename T>
void Matrix<T>::expand_matrix(int expanded, T t) {
    expand_matrix_horizontally(expanded,t);
    expand_matrix_vertically(expanded,t);

}

//Expand the matrix only horizontally
template <typename T>
void Matrix<T>::expand_matrix_horizontally(int expanded, T default_value) {

    number_of_rows    += expanded;
    Cell<T>* tmp = this->first;

    for(/**/; tmp->right != NULL; tmp = tmp->right);
    
    Cell<T>* tmp2 = tmp;

    expand_horizontally(tmp2,expanded,default_value);

    do {
        tmp2 = tmp->down;
        expand_horizontally_linked_up(tmp2,expanded,default_value);
        tmp = tmp->down;
    } while(tmp2->down != NULL);

    tmp2 = NULL;
    tmp  = NULL;
}

//Expand the matrix only vertically
template <typename T>
void Matrix<T>::expand_matrix_vertically(int expanded, T default_value) {
    std::cout << "teste" << std::endl;

    number_of_columns += expanded;
    Cell<T>* tmp = this->first;

    for(/**/; tmp->down != NULL; tmp = tmp->down);

    counter n_horizontal;
    if(this->number_of_columns == this->number_of_rows) 
        n_horizontal = this->number_of_columns - expanded + 1;
    else 
        n_horizontal = this->number_of_rows - 1;
    
    for (int i = 0; i < expanded;i++) {
        tmp = expand_vertically(tmp,1,default_value);
        expand_horizontally_linked_up(tmp,n_horizontal,default_value);
    }
}
