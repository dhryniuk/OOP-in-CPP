#include<iostream>
#include<string.h>
#include<math.h>  

class matrix 
{
    friend std::ostream & operator<<(std::ostream &os, const matrix &M);
    friend std::istream & operator>>(std::istream &is, matrix &M);
private:
    int rows{0}, columns{0};
    double *array {nullptr};

public:
    matrix(int rows, int columns);
    ~matrix() {delete[] array;}
    matrix(const matrix &); //Copy constructor
    matrix(matrix &&); //Move constructor

    matrix & operator=(matrix &); //Assignment operator
    matrix & operator=(matrix &&); //Move operator
    double & element(int i, int j) const; //Returns matrix element from i'th row and j'th column
    matrix remove(int i, int j); //Removes i'th row and j'th column from matrix
    double determinant();
    matrix operator+(const matrix &M) const;
    matrix operator-(matrix &M);
    matrix operator*(const matrix &M) const;

    // Public setter and getters to access private data:
    void set_array_element(int i, double val);
    int get_rows();
    int get_columns();
};

matrix::matrix(int r, int c)
{
    rows = r;
    columns = c;
    array = new double[rows*columns];
    for(int i{0}; i<rows*columns; i++) array[i]=0.0;
}

// Copy constructor for deep copying:
matrix::matrix(const matrix &M)
{
    rows = M.rows;
    columns = M.columns;
    array = new double[rows*columns];
    for (int i{0}; i<=rows*columns; i++){
        array[i] = M.array[i];
    }
}

// Move constructor:
matrix::matrix(matrix &&M)
{
    rows = M.rows;
    columns = M.columns;
    array = M.array;
    M.rows = 0;
    M.columns = 0;
    M.array = nullptr;
}

// Assignment operator for deep copying:
matrix & matrix::operator=(matrix &M)
{
    if (&M == this) return *this;
    rows = M.rows;
    columns = M.columns;
    delete[] array; array=nullptr;
    array = new double[rows*columns];
    for(size_t i{0}; i<rows*columns; i++) array[i] = M.array[i];
    return *this;
}

// Move assignment operator:
matrix & matrix::operator=(matrix &&M)
{
    std::swap(rows, M.rows);
    std::swap(columns, M.columns);
    std::swap(array, M.array);
    return *this;
}

double & matrix::element(int i, int j) const
{
    int loc{0};
    loc = (j-1) + (i-1)*columns;
    return array[loc];
}

std::istream & operator>>(std::istream &is, matrix &M)
{
    int input1, rows, columns;
    double input2;

    std::cout << "Set number of rows: ";
    std::cin >> rows;
    std::cout << "Set number of columns: ";
    std::cin >> columns;

    // Re-declare matrix M with user-specified dimensions:
    M.rows = rows;
    M.columns = columns;
    M.array = new double[rows*columns];
    for(int i{0}; i<rows*columns; i++) M.array[i]=0.0;

    // Ask user to specify all matrix elements:
    std::cout << "Set values of matrix elements: [row][column]" << std::endl;
    for (int i{1}; i<=M.rows; i++)
    for (int j{1}; j<=M.columns; j++){
        std::cout << "[" << i << "]";
        std::cout << "[" << j << "]: ";
        std::cin >> input2;
        M.array[(j-1) + (i-1)*M.columns] = input2;
    }
    std::cout << '\n';
    return is;
}

std::ostream & operator<<(std::ostream &os, const matrix &M)
{
    // Find matrix element with most digits to appropriately format the matrix:
    int most_digits = std::to_string((int)M.array[0]).length(); 
    for (int k{0}; k<M.rows*M.columns; k++){
        if (std::to_string((int)M.array[k]).length() > most_digits){
            most_digits = std::to_string((int)M.array[k]).length();
        }
    }
    for (int i{1}; i<=M.rows; i++){
        os << "[";
        for (int j{1}; j<=M.columns; j++){
            os << std::string(most_digits+1 - 
            std::to_string((int)M.element(i,j)).length(), ' ') << M.element(i,j); 
        }
        os << " ] \n";
    }
    return os;
}

matrix matrix::operator+(const matrix &M) const
{
    matrix N(rows, columns);
    if (M.rows!=rows || M.columns!=columns){
        std::cout << "ERROR: DIMENSIONS OF MATRICES DO NOT MATCH" << std::endl;
    } else{
        std::cout << "(Operation is possible)" << std::endl;
        for (int i{0}; i<=M.rows*M.columns; i++){
            N.array[i] = array[i] + M.array[i];
        }
    }
    return N;
}

matrix matrix::operator-(matrix &M)
{
    matrix N(rows, columns);
    if (M.rows!=rows || M.columns!=columns){
        std::cout << "ERROR: DIMENSIONS OF MATRICES DO NOT MATCH" << std::endl;
    } else{
        std::cout << "(Operation is possible)" << std::endl;
        for (int i{1}; i<=M.rows; i++)
        for (int j{1}; j<=M.columns; j++){
            N.element(i,j) = element(i,j) - M.element(i,j);
        }
    }
    return N;
}

matrix matrix::operator*(const matrix &M) const
{
    matrix N(rows, M.columns);
    if (columns!=M.rows){
        std::cout << "ERROR: DIMENSIONS OF MATRICES DO NOT MATCH" << std::endl;
    } else{
        std::cout << "(Operation is possible)" << std::endl;
        for (int i{1}; i<=rows; i++)
        for (int j{1}; j<=M.columns; j++)
        for (int k{1}; k<=M.rows; k++){
            N.array[(j-1) + (i-1)*columns] += element(i,k)*M.element(k,j);
        }
    }
    return N;
}

matrix matrix::remove(int i, int j)
{
    matrix N(rows-1, columns-1);
    int l{0}; 
    for (int k{0}; k<rows*columns; k++){
        // Find matrix elements outside row i and column j:
        if (k%rows != j-1 && (k<(i-1)*columns || k>=i*columns)){
            N.array[l] = array[k];
            l++;
        }
    }
    return N;
}

double matrix::determinant() 
{
    double det{0};
    if (rows==2 && columns==2){
        return element(1,1)*element(2,2) - element(1,2)*element(2,1);
    } else if (rows==columns){
        for (int col{1}; col<=columns; col++){
            det += pow(-1,1+col)*element(1,col)*remove(1,col).determinant();
        }
        return det;
    } else{
        std::cout << "MATRIX NEEDS TO BE A SQUARE MATRIX";
        return 0;
    }
}

void matrix::set_array_element(int i, double val) 
{
    array[i] = val;
}

int matrix::get_rows() 
{
    return rows;
}

int matrix::get_columns() 
{
    return columns;
}