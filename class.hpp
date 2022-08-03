#define ACCUR 0.0001
struct Element 
{
    int k; 
    int m; 
    double n; 
};


class SparseMatrix 
{
public:
    Element* el; 
    int row_size; 
    int column_size;
    int nonzero_cnt;
//public:
     
    double accuracy;
    
    class IndexArithmetic
    {
    public:
        IndexArithmetic(SparseMatrix& m, int i) : matrx(m), our_row(i) {} ///////////////////////////////////////////////////////////////////////////////
        double& operator [] (int j);
    private:
        SparseMatrix& matrx; ///////////////////////////////////////////////////////////////////////////////////////////////////////
        int      our_row;
    };
    
    class IndexArithmetic_const
    {
    public:
        IndexArithmetic_const(const SparseMatrix& m, int i) : matrx(m), our_row(i) {}
        double operator [] (int j) const;
    private:
        const SparseMatrix& matrx;
        int      our_row;
    };
    
    
    class AddressArithmetic_1
    {
    public:
        class AddressArithmetic_2
        {
        public:
            AddressArithmetic_2(AddressArithmetic_1& m) : matrx(m.matrx), our_row(m.our_row) {}
            double* operator+ (int j);
        private:
            SparseMatrix& matrx;
            int      our_row;
        };
        
        AddressArithmetic_1(SparseMatrix& m, int i) : matrx(m), our_row(i) {}
        AddressArithmetic_2 operator* ();
    private:
        SparseMatrix& matrx;
        int      our_row;
    };
    
    class AddressArithmetic_1_const
    {
    public:
        class AddressArithmetic_2_const
        {
        public:
            AddressArithmetic_2_const(const AddressArithmetic_1_const& m) : matrx(m.matrx), our_row(m.our_row) {}
            double operator+ (int j) const;
        private:
            const SparseMatrix& matrx;
            int      our_row;
        };
        
        AddressArithmetic_1_const(const SparseMatrix& m, int i) : matrx(m), our_row(i) {}
        AddressArithmetic_2_const operator* ()const;
    private:
        const SparseMatrix& matrx;
        int      our_row;
    };

    SparseMatrix (int a, int b);
    SparseMatrix (Element*, int, int, int);
    ~SparseMatrix ();
    
    double get(int i, int j) const;
    void set(int, int, double);
    
    int num_rows();
    int num_columns();
    
    bool operator==(const SparseMatrix& obj) const;
    bool operator!=(const SparseMatrix& obj) const;
    
    SparseMatrix operator+(const SparseMatrix& obj) const;
    SparseMatrix operator*(const SparseMatrix& obj) const;
    
    IndexArithmetic operator[] (int i);
    IndexArithmetic_const operator[] (int i) const;
    
    AddressArithmetic_1 operator+(int i);
    AddressArithmetic_1_const operator+(int i) const;
};
