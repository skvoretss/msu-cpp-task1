# Annotation:
The SparseMatrix class for working with sparse matrices is implemented. 

The class supports the following operations:

● double get(size_t, size_t) - getting values by indexes (also works for constant objects)

● void set(size_t, size_t, double) - changing the value by indexes

● size_t num_rows() - number of rows (also works for constant objects)

● size_t num_columns() - number of rows (also works for constant objects)

● operations of comparing two matrices (==, !=) (also works for constant objects)

● binary operation +, addition of sparse matrices (also works for constant objects)

● binary operation *, multiplication * matrix multiplication (mult) (also works for constant objects)

● indexing operation [i] (see examples) (also works for constant objects)

● operations to support address arithmetic (see examples) (also works for constant objects)

### Examples:
SparseMatrix m1(10, 20); // matrix 10 by 20

m1[4][2] = 42; // set the value 42 for the element in row 4, column 2

*(*(m1 + 4) + 2) = 42; // same

const SparseMatrix m2 = m1; // saving copy m1

double v1 = m2[4][2]; // getting value of 4th row, 2nd column

double v2 = *(*(m2 + 4) + 2); // same

SparseMatrix sum = m1 + m2; // calculate the sum of two matrices 10x20

double v3 = m1.get(5, 5); // v3 == 0

bool bb = (m1 == m2); // compare two matrices for an element-by-element match

# Примечание:
Реализован класс SparseMatrix по работе с разряженными матрицами. 

Класс поддерживает следующие операции:

● double get(size_t, size_t) - получение значения по индексам (работает и для константных объектов)

● void set(size_t, size_t, double) - изменение значения по индексам

● size_t num_rows() - количество строк (работает и для константных объектов)

● size_t num_columns() - количество строк (работает и для константных объектов)

● операции сравнения двух матриц (==, !=) (работает и для константных объектов)

● бинарная операция +, сложение разряженных матриц (работает и для константных объектов)

● бинарная операция *, умножение * умножение матриц (mult) (работает и для константных объектов)

● операция индексации [i] (см. примеры) (работает и для константных объектов)

● операции для поддержки адресной арифметики (см. примеры) (работает и для константных объектов)

### Примеры:
SparseMatrix m1(10, 20); // матрица 10 на 20

m1[4][2] = 42; // установить значение 42 для элемента в строке 4, столбце 2

*(*(m1 + 4) + 2) = 42; // аналогично

const SparseMatrix m2 = m1; // сохранение копии m1

double v1 = m2[4][2]; // получение значения элемента из 4й строки, 2 столбца

double v2 = *(*(m2 + 4) + 2); // аналогично

SparseMatrix sum = m1 + m2; // вычислить сумму двух матриц 10x20

double v3 = m1.get(5, 5); // v3 == 0

bool bb = (m1 == m2); // сравнить две матрицы на поэлементное совпадение
