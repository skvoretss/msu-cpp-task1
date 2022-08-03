#include <iostream>
#include "class.hpp"
SparseMatrix::SparseMatrix (int a, int b)
{
    row_size = a; // кол-во строк в матрице
    column_size = b; //  кол-во стобцов в матрице
    nonzero_cnt = 0; // кол-во ненулевых элементов
    accuracy = ACCUR; // точность
    std::cout << "Please, input the values of matrix elements" << std::endl;
    double t = 0.0;
    for (int i = 0; i < row_size; ++i)
    {
        for (int j = 0; j < column_size; ++j)
        {
            std::cin >> t;
            if ((t > 0.0) || (t < 0.0))
            {
                ///выделить под этот элемент память и проинициализировать
                nonzero_cnt++;
                if (nonzero_cnt == 1)
                {
                    el = (Element*)malloc(sizeof(Element));
                }
                else
                {
                    el = (Element*)realloc(el, nonzero_cnt * sizeof(Element));
                }
                el[nonzero_cnt-1].k = i;
                el[nonzero_cnt-1].m = j;
                el[nonzero_cnt-1].n = t;
                //std::cout << el[nonzero_cnt-1].k << " " << el[nonzero_cnt-1].m << " " << el[nonzero_cnt-1].n <<std::endl;
            }
        }
    }
    if (nonzero_cnt == 0)
    {
        el = (Element*)malloc(sizeof(Element));
        el[0].k = 0;
        el[0].m = 0;
        el[0].n = 0;
    }   
};

SparseMatrix::SparseMatrix (Element* el_new, int nonzero_cnt_new, int col_size, int r_size)
{
    row_size = r_size; // кол-во строк в матрице
    column_size = col_size; //  кол-во стобцов в матрице
    nonzero_cnt = nonzero_cnt_new; // кол-во ненулевых элементов
    accuracy = ACCUR; // точность
    if (nonzero_cnt != 0)
    {
        el = (Element*)malloc(nonzero_cnt*sizeof(Element));
        for (int i = 0; i < nonzero_cnt; ++i)
        {
            el[i].k = el_new[i].k;
            el[i].m = el_new[i].m;
            el[i].n = el_new[i].n;
            //std::cout << el[i].k << " " << el[i].m << " " << el[i].n <<std::endl;
        }
    }
    else
    {
        el = (Element*)malloc(sizeof(Element));
        el[0].k = 0;
        el[0].m = 0;
        el[0].n = 0;
        //std::cout << el[0].k << " " << el[0].m << " " << el[0].n <<std::endl;
    }
    free(el_new);
};

SparseMatrix::~SparseMatrix ()
{
    if (el != NULL)
    {
        free(el);
    }   
}


double SparseMatrix::get(int isk_1, int isk_2) const
{
    for (int i = 0; i < nonzero_cnt; ++i)
    {
        if ((el[i].k == isk_1) && (el[i].m == isk_2))
        {
            return el[i].n;
        }
    }
    return 0;
};

void SparseMatrix::set(int i_new, int j_new, double n_new)
{
    bool value_change = false;
    if (nonzero_cnt == 0)
    {
        if ((n_new > 0.0) || (n_new < 0.0))
        {
            el[0].k = i_new;
            el[0].m = j_new;
            el[0].n = n_new;
            nonzero_cnt = 1;
        }
    };
    for (int i = 0; i < nonzero_cnt; ++i)
    {
        if ((el[i].k == i_new) && (el[i].m == j_new))
        {
            el[i].n = n_new;
            value_change = true;
        }
    }
    if ((value_change == false) && ((n_new > 0) || (n_new < 0)))
    {
        nonzero_cnt++;
        el = (Element*)realloc(el, nonzero_cnt*sizeof(Element));
        int indx = 0;
        while ((indx < nonzero_cnt - 1) && (el[indx].k < i_new)) { indx++; } // дошли до начала нужно строчки
        while ((indx < nonzero_cnt - 1) &&(el[indx].m < j_new) && (el[indx].k == i_new)) { indx++; }
        for (int i = nonzero_cnt - 1; i > indx; --i)
        {
            el[i].k = el[i-1].k;
            el[i].m = el[i-1].m;
            el[i].n = el[i-1].n;
        }
        el[indx].k = i_new;
        el[indx].m = j_new;
        el[indx].n = n_new;
    }
};

int SparseMatrix::num_rows()
{
    return row_size;
};

int SparseMatrix::num_columns()
{
    return column_size;
};

bool SparseMatrix::operator==(const SparseMatrix& obj) const
{
    for (int i = 0; i < nonzero_cnt; ++i)
    {
        if (obj.el[i].n - el[i].n < 0)
        {
            if (obj.el[i].n - el[i].n < accuracy*(-1))
            {
                return false;
            }
        }
        else
        {
            if (obj.el[i].n - el[i].n > accuracy)
            {
                return false;
            }
        }
    }
    return true;
};

bool SparseMatrix::operator!=(const SparseMatrix& obj) const
{
    for (int i = 0; i < nonzero_cnt; ++i)
    {
        if (obj.el[i].n - el[i].n < 0)
        {
            if (obj.el[i].n - el[i].n <= accuracy*(-1))
            {
                return true;
            }
        }
        else
        {
            if (obj.el[i].n - el[i].n >= accuracy)
            {
                return true;
            }
        }
    }
    return false;
};

SparseMatrix SparseMatrix::operator+(const SparseMatrix& obj) const
{
    Element* el_new = NULL;
    if ((nonzero_cnt == 0) && (obj.nonzero_cnt != 0))
    {
        el_new = (Element*)malloc(obj.nonzero_cnt*sizeof(Element));
        for (int i = 0; i < obj.nonzero_cnt; ++i)
        {
            el_new[i].k = obj.el[i].k;
            el_new[i].m = obj.el[i].m;
            el_new[i].n = obj.el[i].n;
        } 
        return SparseMatrix(el_new, obj.nonzero_cnt, obj.column_size, obj.row_size);
    }
    else if ((obj.nonzero_cnt == 0) && (nonzero_cnt != 0))
    {
        el_new = (Element*)malloc(nonzero_cnt*sizeof(Element));
        for (int i = 0; i < nonzero_cnt; ++i)
        {
            el_new[i].k = el[i].k;
            el_new[i].m = el[i].m;
            el_new[i].n = el[i].n;
        } 
        return SparseMatrix(el_new, nonzero_cnt , column_size, row_size);
    }
    else if ((obj.nonzero_cnt == 0) && (nonzero_cnt == 0))
    {
        //std::cout << "***" << std::endl;
        el_new = (Element*)malloc(sizeof(Element));
        el_new[0].k = 0;
        el_new[0].m = 0;
        el_new[0].n = 0;
        return SparseMatrix(el_new, nonzero_cnt , column_size, row_size);
    }
    int nonzero_cnt_new = 0;
    
    int flag = 0;
    for (int i = 0; i < nonzero_cnt; ++i)
    {
        flag = 0;
        for (int j = 0; j < obj.nonzero_cnt; ++j)
        {
            if ((el[i].k == obj.el[j].k) && (el[i].m == obj.el[j].m))
            {
                nonzero_cnt_new++;
                if (nonzero_cnt_new == 1)
                {
                    el_new = (Element*)malloc(sizeof(Element));
                }
                else
                {
                    el_new = (Element*)realloc(el_new, nonzero_cnt_new * sizeof(Element)); 
                }
                el_new[nonzero_cnt_new-1].k = el[i].k;
                el_new[nonzero_cnt_new-1].m = el[i].m;
                el_new[nonzero_cnt_new-1].n = el[i].n + obj.el[j].n;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            nonzero_cnt_new++;
            if (nonzero_cnt_new == 1)
            {
                el_new = (Element*)malloc(sizeof(Element));
            }
            else
            {
                el_new = (Element*)realloc(el_new, nonzero_cnt_new * sizeof(Element));  
            }
            el_new[nonzero_cnt_new-1].k = el[i].k;
            el_new[nonzero_cnt_new-1].m = el[i].m;
            el_new[nonzero_cnt_new-1].n = el[i].n;
        }
        
    }
    for (int j = 0; j < obj.nonzero_cnt; ++j)
    {
        flag = 0;
        for (int i = 0; i < nonzero_cnt; ++i)
        {
            if ((el[i].k == obj.el[j].k) && (el[i].m == obj.el[j].m))
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            nonzero_cnt_new++;
            if (nonzero_cnt_new == 1)
            {
                el_new = (Element*)malloc(sizeof(Element));
            }
            else
            {
                el_new = (Element*)realloc(el_new, nonzero_cnt_new * sizeof(Element)); 
            }
            el_new[nonzero_cnt_new-1].k = obj.el[j].k;
            el_new[nonzero_cnt_new-1].m = obj.el[j].m;
            el_new[nonzero_cnt_new-1].n = obj.el[j].n;
        }
    }
    if (nonzero_cnt_new == 0)
    {
        el_new = (Element*)malloc(sizeof(Element));
        el_new[0].k = 0;
        el_new[0].m = 0;
        el_new[0].n = 0;
    } 
    return SparseMatrix(el_new, nonzero_cnt_new, column_size, row_size); 
    
};

SparseMatrix SparseMatrix::operator*(const SparseMatrix& obj) const
{
    Element* el_new = NULL;
    if (nonzero_cnt == 0)
    {
        el_new = (Element*)malloc(sizeof(Element));
        el_new[0].k = 0;
        el_new[0].m = 0;
        el_new[0].n = 0;
        return SparseMatrix(el_new, nonzero_cnt, obj.column_size, row_size);
    };
    if (obj.nonzero_cnt == 0)
    {
        el_new = (Element*)malloc(sizeof(Element));
        el_new[0].k = 0;
        el_new[0].m = 0;
        el_new[0].n = 0;
        return SparseMatrix(el_new, obj.nonzero_cnt, obj.column_size, row_size);
    };
    int counter = 0;
    double res = 0;
    for (int g = 0; g < row_size; ++g)
    {
        for (int i = 0; i < obj.column_size; ++i) 
        {
            res = 0;
            for (int j = 0; j < column_size; ++j) 
            {
                double b = 0;
                for (int h = 0; h < obj.nonzero_cnt; ++h)
                {
                    if ((obj.el[h].k == j) && (obj.el[h].m == i))
                    {
                        b = obj.el[h].n;
                    }
                }
                res += get(g, j) * b;
            }
            if ((res > 0.0) || (res < 0.0))
            {
                counter++;
                if (counter == 1)
                {
                    el_new = (Element*)malloc(sizeof(Element));
                }
                else
                {
                    el_new = (Element*)realloc(el_new, counter * sizeof(Element));
                }
                el_new[counter-1].k = g;
                el_new[counter-1].m = i;
                el_new[counter-1].n = res;
            }
        }
    }
    if (counter == 0)
    {
        el_new = (Element*)malloc(sizeof(Element));
        el_new[0].k = 0;
        el_new[0].m = 0;
        el_new[0].n = 0;
    } 
    return SparseMatrix(el_new, counter, obj.column_size, row_size);
};

SparseMatrix::IndexArithmetic SparseMatrix::operator[](int a) 
{
    return IndexArithmetic(*this, a);
};

SparseMatrix::IndexArithmetic_const SparseMatrix::operator[](int a) const
{
    return IndexArithmetic_const(*this, a);
};

double& SparseMatrix::IndexArithmetic::operator[](int a)
{
    for (int i = 0; i < matrx.nonzero_cnt; ++i)
    {
        if ((matrx.el[i].k == our_row) && (matrx.el[i].m == a))
        {
            return matrx.el[i].n;
        }
    }
    if (matrx.nonzero_cnt == 0)
    {
        matrx.el[0].k = our_row;
        matrx.el[0].m = a;
        matrx.el[0].n = 0;
        ++matrx.nonzero_cnt;
        return matrx.el[0].n;
    }
    matrx.nonzero_cnt++;
    //std::cout << "matrx.nonzero_cnt = " << matrx.nonzero_cnt << std::endl;
    matrx.el = (Element*)realloc(matrx.el, matrx.nonzero_cnt*sizeof(Element));
    //std::cout << "$$$$$$$$$$" <<  std::endl;
    int indx = 0;
    while ((indx < matrx.nonzero_cnt - 1) && (matrx.el[indx].k < our_row)) { indx++; } // дошли до начала нужно строчки
    //std::cout << "######" <<  std::endl;
    while ((indx < matrx.nonzero_cnt - 1) && (matrx.el[indx].m < a) && (matrx.el[indx].k == our_row)) { indx++; }
    //std::cout << "@@@@@@@@@@@@" <<  std::endl;
    for (int i = matrx.nonzero_cnt - 1; i > indx; --i)
    {
        matrx.el[i].k = matrx.el[i-1].k;
        matrx.el[i].m = matrx.el[i-1].m;
        matrx.el[i].n = matrx.el[i-1].n;
    }
    //std::cout << "index = " << indx << std::endl;
    matrx.el[indx].k = our_row;
    matrx.el[indx].m = a;
    matrx.el[indx].n = 0;
    return matrx.el[indx].n; 
};

double SparseMatrix::IndexArithmetic_const::operator[](int a) const
{
    for (int i = 0; i < matrx.nonzero_cnt; ++i)
    {
        if ((matrx.el[i].k == our_row) && (matrx.el[i].m == a))
        {
            return matrx.el[i].n;
        }
    }
    return 0; 
};

SparseMatrix::AddressArithmetic_1 SparseMatrix::operator+(int i)
{
    return AddressArithmetic_1(*this, i);
};

SparseMatrix::AddressArithmetic_1::AddressArithmetic_2 SparseMatrix::AddressArithmetic_1::operator* ()
{
    return AddressArithmetic_2(*this);
};

double* SparseMatrix::AddressArithmetic_1::AddressArithmetic_2::operator+ (int j)
{
    double* p;
    if (matrx.nonzero_cnt == 0)
    {
        matrx.el[0].k = our_row;
        matrx.el[0].m = j;
        matrx.el[0].n = 0;
        matrx.nonzero_cnt++;
        p = &matrx.el[0].n;
        return p;
    }
    for (int i = 0; i < matrx.nonzero_cnt; ++i)
    {
        if ((matrx.el[i].k == our_row) && (matrx.el[i].m == j))
        {
            p = &matrx.el[i].n;
            return p;
        }
    }
    
    ++matrx.nonzero_cnt;
    matrx.el = (Element*)realloc(matrx.el, matrx.nonzero_cnt*sizeof(Element));
    int indx = 0;
    while ((indx < matrx.nonzero_cnt - 1) && (matrx.el[indx].k < our_row)) { indx++; } // дошли до начала нужно строчки
    while ((indx < matrx.nonzero_cnt - 1) && (matrx.el[indx].m < j) && (matrx.el[indx].k == our_row)) { indx++; }
    for (int i = matrx.nonzero_cnt - 1; i > indx; --i)
    {
        matrx.el[i].k = matrx.el[i-1].k;
        matrx.el[i].m = matrx.el[i-1].m;
        matrx.el[i].n = matrx.el[i-1].n;
    }
    matrx.el[indx].k = our_row;
    matrx.el[indx].m = j;
    matrx.el[indx].n = 0;
    p = &matrx.el[indx].n;
    return p; 
};

SparseMatrix::AddressArithmetic_1_const SparseMatrix::operator+(int i) const
{
    return AddressArithmetic_1_const(*this, i);
};

SparseMatrix::AddressArithmetic_1_const::AddressArithmetic_2_const SparseMatrix::AddressArithmetic_1_const::operator* () const
{
    return AddressArithmetic_2_const(*this);
};

double SparseMatrix::AddressArithmetic_1_const::AddressArithmetic_2_const::operator+ (int j) const
{
    for (int i = 0; i < matrx.nonzero_cnt; ++i)
    {
        if ((matrx.el[i].k == our_row) && (matrx.el[i].m == j))
        {
            return matrx.el[i].n;
        }
    }
    return 0;
};
