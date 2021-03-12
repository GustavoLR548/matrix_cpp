#ifndef matrix_hpp
#define matrix_hpp

#include"cell.cpp"

int const MIN = 2;

template <typename T>
class Matrix {

    private: 

        //Atributes
        Cell<T>* first;
        short number_of_columns;
        short number_of_rows;

        //Inside functions
        void build_matrix();
        void expand_horizontally(Cell<T>* c, int n = 1);
        void expand_horizontally_linked_up(Cell<T>* c,int n = 1);
        Cell<T>* expand_vertically(Cell<T>* c, int n = 1);
        Cell<T>* search(int x, int y);
        bool is_outside_matrix(int x,int y);

    public: 

        Matrix();
        ~Matrix();
        Matrix(short n);
        Matrix(short c, short r);

        //Get
        short get_number_of_columns();
        short get_number_of_rows();

        //Basic functionalities of the Matrix
        void print();
        T get(int x,int y);
        bool insert(T element,int x,int y);
        void expand_matrix(int expanded);
        void expand_matrix_horizontally(int expanded);
        void expand_matrix_vertically(int expanded);
    
};

#endif
