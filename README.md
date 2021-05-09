# matrix_cpp
An implementation of a expandable matrix in C++

![escudo2](https://img.shields.io/badge/license-MIT-green) ![escudo](https://img.shields.io/badge/build-passing-brightgreen)

The ideia to create this project arised when I started to work with my implementation of graphs in C++. When working with graphs,
the most know options to store information about graphs are: Matrix and Lists. So.. I decided to implement my own method do make 
a flexible Matrix in C++, while also making the basic operations very cheap.

Here is a list of the current operations that are available:

## Constructors 

 > * **Matrix(T default_value)** is the default constructor, it allows you to create a matrix with any value that you desire. 
 *Obs: If you don't specify any value, it will start with the default value of the chosen type. Ex: integers will be zero.*
 > * **Matrix(short n, T default value)** is the second constructor, and it allows you to create a matrix with a fixed value
 .Just like the first constructor , it defines a starting value for all elements in the Matrix.
 > *  **Matrix(short c, short r, T default value)** is the third and final constructor. It allows you to create a Matrix with ```c``` number of columns and 
 ```r``` number of rows. Just like the first constructor , it defines a starting value for all elements in the Matrix.

## Functions 

> * **get(int x, int y)**: get the element in the cell that it's in the position (x,y) of the matrix
> * **insert(T element, int x, int y)**: insert ```element``` in the cell that it's in the position (x,y) of the matrix
> * **fill(T element)**: fill all of the Matrix's cells with the value ```element``` 
> * **expand_matrix(int expanded, T t)**: expand the matrix ```expanded``` number of times, and start the new cells with the value ```t```
*Obs: if the value ```t``` is not specified, then the value first inserted in the constructor will be the one filled*

> *Obs2: You can also expand the matrix in a single axis using **expand_matrix_vertically** and **expand_matrix_horizontally** using the same arguments as before*

## Efficient method of insert and getting elements

Traversing a matrix might be a costing method, especially if your matrix is large. For this reason, I tried making a efficient way of traversing the matrix, and lowering the cost necessary to get the components for the operations. 

Basically, whenever the user makes an operation, it stores the position of the searched cell, so that it can use it for next operations, if traversing the matrix with the previously searched cell is cheaper, then the matrix will use it, if not, then it will use the first cell in the matrix.

Here is a basic demonstration of its use:

*Obs: the ```contador``` is how many cells it has traversed to insert a new element*

```
contador: 1
contador: 1
contador: 2
contador: 2
contador: 5
contador: 5
contador: 3
contador: 3
contador: 4
contador: 4
contador: 8
contador: 8
contador: 11
contador: 11
contador: 12
contador: 12
contador: 13
contador: 13
contador: 15
contador: 15
contador: 17
contador: 17

Matrix
0 1 1 0 0 0 0 0 0 0 
1 0 1 1 1 0 0 0 0 0 
1 1 0 0 0 0 0 0 0 0 
0 1 0 0 0 1 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 
0 0 0 1 0 0 1 1 1 0 
0 0 0 0 0 1 0 0 0 0 
0 0 0 0 0 1 0 0 1 0 
0 0 0 0 0 1 0 1 0 1 
0 0 0 0 0 0 0 0 1 0 

contador: 1
contador: 2
contador: 3
contador: 4
contador: 5
contador: 6
contador: 4
contador: 2
contador: 3
contador: 4
contador: 4
contador: 4
contador: 3
contador: 2
contador: 3
contador: 4
contador: 5
contador: 6
contador: 4
contador: 2
contador: 2
contador: 2

Matrix
0 1 1 0 0 0 0 0 0 0 
1 0 1 1 1 0 0 0 0 0 
1 1 0 0 0 0 0 0 0 0 
0 1 0 0 0 1 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 
0 0 0 1 0 0 1 1 1 0 
0 0 0 0 0 1 0 0 0 0 
0 0 0 0 0 1 0 0 1 0 
0 0 0 0 0 1 0 1 0 1 
0 0 0 0 0 0 0 0 1 0 
```

Notice that, both resulting matrixes are the same, but the number of movements necessary to insert every element into the matrix is lower.
