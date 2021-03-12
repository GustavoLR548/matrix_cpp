#ifndef cell_hpp
#define cell_hpp

template <typename T>
class Cell {

    private:

        T element;

    public:

        Cell* left;
        Cell* right;
        Cell* up;
        Cell* down;

        Cell();
        ~Cell();
        T getElement();
        void setElement(T element);
};

#endif
