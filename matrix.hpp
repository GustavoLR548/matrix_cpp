#ifndef matrix_hpp
#define matrix_hpp

#include"cell.cpp"
#include<stdint.h>

int const MIN = 2;

using counter = uint16_t;

template <typename T>
class Matrix {

    private: 

        //Atributes

        Cell<T>* first;

        T default_value;

        Cell<T>* last_searched_cell;
        counter last_searched_c;
        counter last_searched_r;

        counter number_of_columns;
        counter number_of_rows;

        //Inside functions

        void build_matrix(T default_value = T());
        void expand_horizontally(Cell<T>* c, int n = 1,T default_value = T());
        void expand_horizontally_linked_up(Cell<T>* c,int n = 1,T default_value = T());
        Cell<T>* expand_vertically(Cell<T>* c, int n = 1,T default_value = T());
        Cell<T>* search(int x, int y, Cell<T>* result);
        bool is_outside_matrix(int x,int y);

    public: 

        //Constructors
        
        Matrix() = default;
        
        Matrix(T default_value = T());
        Matrix(short n, T default_value = T());
        Matrix(short c, short r, T default_value= T());

        //Destructor

        ~Matrix();

        //Get

        counter get_number_of_columns();
        counter get_number_of_rows();

        //Basic functionalities of the Matrix

        void print();
        void fill(T value);
        T get(int x,int y);
        bool insert(T element,int x,int y);
        void expand_matrix(int expanded, T default_value = T());
        void expand_matrix_horizontally(int expanded, T default_value = T());
        void expand_matrix_vertically(int expanded, T default_value = T());
    
};

#endif
