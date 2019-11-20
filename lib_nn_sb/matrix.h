#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <ostream>

class Matrix
{
    unsigned long rows;
    unsigned long cols;
    std::vector<double> values;

public:
    Matrix(unsigned long rows,unsigned long cols,bool initZero = true);
    Matrix();
    Matrix(const Matrix& m);

    void print();

    void setValues(const double& val);
    void setValue(const unsigned int& row,const unsigned int& col, const double& val);
    double getValue(const unsigned int& row, const unsigned int& col) const;

    void randomize(int min = 0,int max = 1);

    static Matrix fromVector(const std::vector<double>& input);
    std::vector<double> toVector();

    /**********************************************************************************/
    /*                              SCALAR OPERATIONS                                 */
    /**********************************************************************************/
    void add(const double& val);
    void sub(const double& val);
    void multiply(const double& val);
    void divide(const double& val);

    static Matrix add(const Matrix& a,const double& val);
    static Matrix sub(const Matrix& a,const double& val);
    static Matrix multiply(const Matrix& a,const double& val);
    static Matrix divide(const Matrix& a,const double& val);

    void map(double(*func)(const double& val));
    void map(double(*func)(double val));

    static Matrix map(const Matrix& a, double(*func)(const double& val));
    static Matrix map(const Matrix& a, double(*func)(double val));

    /**********************************************************************************/
    /*                              MATRIX OPERATIONS                                 */
    /**********************************************************************************/
    bool add(const Matrix& other);
    bool sub(const Matrix& other);
    bool multiply(const Matrix& other);
    bool hadamard(const Matrix& other);

    static Matrix add(const Matrix& a,const Matrix& b);
    static Matrix sub(const Matrix& a,const Matrix& b);
    static Matrix multiply(const Matrix& a,const Matrix& b);
    static Matrix hadamard(const Matrix& a, const Matrix& b);

    Matrix sum(int axis = 0);
    static Matrix sum(const Matrix& a, int axis = 0);

    void transpose();
    static Matrix transpose(const Matrix& a);

    /**********************************************************************************/
    /*                             OPERATOR OVERLOADS                                 */
    /**********************************************************************************/
    std::vector<double> operator[](const unsigned long& index) const;

    Matrix operator+(const double& val);
    Matrix operator-(const double& val);
    Matrix operator*(const double& val);
    Matrix operator/(const double& val);

    Matrix operator+=(const double& val);
    Matrix operator-=(const double& val);
    Matrix operator*=(const double& val);
    Matrix operator/=(const double& val);

    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);

    Matrix operator+=(const Matrix& other);
    Matrix operator-=(const Matrix& other);
    Matrix operator*=(const Matrix& other);

    friend Matrix operator-(double a,Matrix b);


    unsigned long getRows() const;
    unsigned long getCols() const;
};

Matrix operator-(double a, Matrix b);




#endif // MATRIX_H
