#include "matrix.h"
#include <ctime>
#include <cstdio>
#include <iostream>
#include <random>



unsigned long Matrix::getRows() const
{
    return rows;
}

unsigned long Matrix::getCols() const
{
    return cols;
}

Matrix::Matrix(unsigned long rows_, unsigned long cols_, bool initZero): rows(rows_),cols(cols_)
{
    this->values.reserve(this->rows*this->cols);


    // Inits the vector with 0s
    if(initZero){
        for (unsigned int i = 0;i<this->rows * this->cols;i++) {
            this->values.emplace_back(0);


        }
    }

    srand(time(NULL));
}

Matrix::Matrix():rows(0),cols(0)
{

}

Matrix::Matrix(const Matrix &m): rows(m.rows),cols(m.cols)
{
    this->values = m.values;

}


void Matrix::print()
{
    printf("Matrix (%lux%lu): \n",this->rows,this->cols);
    for(unsigned int i = 0; i < this->rows;i++){
        for (unsigned int j = 0; j < this->cols; j++) {
            printf("%-10.2f", (*this)[i][j]);
        }
        printf("\n");
    }
}


void Matrix::setValues(const double &val)
{
    // Set all Cells in the Matrix to val
    for (unsigned int i = 0; i < this->rows * this->cols; i++) {
        this->values[i] = val;

    }
}

void Matrix::setValue(const unsigned int &row, const unsigned int &col, const double &val)
{
    this->values[col + row * this->cols] = val;
}

double Matrix::getValue(const unsigned int &row, const unsigned int &col) const
{
    return this->values[col + row * this->cols];
}

void Matrix::randomize(int min, int max)
{

    for(unsigned int i = 0; i < this->values.size();i++){
        this->values[i] = min + static_cast<double>(rand()) /( static_cast<double>(RAND_MAX/(max-min)));
    }
}

Matrix Matrix::fromVector(const std::vector<double> &input)
{
    Matrix ret(input.size(),1);
    ret.values = input;
    return ret;
}

std::vector<double> Matrix::toVector()
{
    return this->values;
}

/**********************************************************************************/
/*                              SCALAR OPERATIONS                                 */
/**********************************************************************************/

void Matrix::add(const double &val)
{
    for(unsigned int i = 0; i < this->values.size();i++){
        values[i] += val;
    }
}

void Matrix::sub(const double &val)
{
    for(unsigned int i = 0; i < this->values.size();i++){
        values[i] -= val;
    }
}

void Matrix::multiply(const double &val)
{
    for(unsigned int i = 0; i < this->values.size();i++){
        values[i] *= val;
    }
}

void Matrix::divide(const double &val)
{
    for(unsigned int i = 0; i < this->values.size();i++){
        values[i] /= val;
    }
}

Matrix Matrix::add(const Matrix &a, const double &val)
{
    Matrix ret(a.rows,a.cols);
    for(unsigned int i = 0; i < a.values.size();i++){
        ret.values[i] = a.values[i] + val;
    }
    return ret;
}

Matrix Matrix::sub(const Matrix &a, const double &val)
{
    Matrix ret(a.rows,a.cols);
    for(unsigned int i = 0; i < a.values.size();i++){
        ret.values[i] = a.values[i] - val;
    }
    return ret;
}

Matrix Matrix::multiply(const Matrix &a, const double &val)
{
    Matrix ret(a.rows,a.cols);
    for(unsigned int i = 0; i < a.values.size();i++){
        ret.values[i] = a.values[i] * val;
    }
    return ret;
}

Matrix Matrix::divide(const Matrix &a, const double &val)
{
    Matrix ret(a.rows,a.cols);
    for(unsigned int i = 0; i < a.values.size();i++){
        ret.values[i] = a.values[i] / val;
    }
    return ret;
}



void Matrix::map(double (*func)(const double &))
{
    // Uses a function pointer.
    // Operates the function on each element of the matrix.

    for(unsigned int i = 0; i < this->values.size();i++){
        this->values[i] = func(this->values[i]);
    }
}

void Matrix::map(double (*func)(double))
{
    for(unsigned int i = 0; i < this->values.size();i++){
        this->values[i] = func(this->values[i]);
    }
}

Matrix Matrix::map(const Matrix &a, double (*func)(const double &))
{
    Matrix ret(a.rows,a.cols);
    for(unsigned int i = 0; i < a.values.size();i++){
        ret.values[i] = func(a.values[i]);
    }
    return ret;
}

Matrix Matrix::map(const Matrix &a, double (*func)(double))
{
    Matrix ret(a.rows,a.cols);
    for(unsigned int i = 0; i < a.values.size();i++){
        ret.values[i] = func(a.values[i]);
    }
    return ret;
}

/**********************************************************************************/
/*                              MATRIX OPERATIONS                                 */
/**********************************************************************************/

bool Matrix::add(const Matrix &other)
{
    if (this->rows != other.rows || this->cols != other.cols){
        std::cerr << "The Dimension dont match !\n";
        return false;
    }

    for (unsigned int i = 0;i < this->values.size(); i++) {
        this->values[i] += other.values[i];
    }
    return true;
}

bool Matrix::sub(const Matrix &other)
{
    if (this->rows != other.rows || this->cols != other.cols){
        std::cerr << "The Dimension dont match !\n";
        return false;
    }

    for (unsigned int i = 0;i < this->values.size(); i++) {
        this->values[i] -= other.values[i];
    }
    return true;
}


/* These methods are intendet for use with small matrices.
 * They dont scale very well. For better performance with
 * bigger ones, loop-tilling and transposing before multiplying
 * should be used.
 */

bool Matrix::multiply(const Matrix &other)
{
    if(this->cols != other.rows){
        std::cerr << "The Dimensions dont match up ! \n";
        return false;
    }

    Matrix res(this->rows,other.cols, true);

    for (unsigned int row = 0;row < res.rows ; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            double val = 0;
            for(unsigned int k = 0; k < this->cols;k++){
                val += this->getValue(row,k) * other.getValue(k,col);
            }
            res.setValue(row,col,val);

        }

    }
    *this = res;
    return true;

}

bool Matrix::hadamard(const Matrix &other)
{
    if (this->rows != other.rows || this->cols != other.cols){
        std::cerr << "The Dimension dont match !\n";
        return false;
    }

    for (unsigned int i = 0;i < this->values.size(); i++) {
        this->values[i] *= other.values[i];
    }
    return true;

}

Matrix Matrix::add(const Matrix &a, const Matrix &b)
{
    if(a.rows != b.rows || a.cols != b.cols){
        std::cerr << "The Dimensions dont match ! \n";
        return Matrix(0,0,false);
    }
    Matrix ret(a.rows,a.cols);

    for(unsigned int i = 0; i < ret.values.size();i++){
        ret.values[i] = a.values[i] + b.values[i];
    }

    return ret;

}

Matrix Matrix::sub(const Matrix &a, const Matrix &b)
{
    if(a.rows != b.rows || a.cols != b.cols){
        std::cerr << "The Dimensions dont match ! \n";
        return Matrix(0,0,false);
    }
    Matrix ret(a.rows,a.cols);

    for(unsigned int i = 0; i < ret.values.size();i++){
        ret.values[i] = a.values[i] - b.values[i];
    }

    return ret;
}

Matrix Matrix::multiply(const Matrix &a, const Matrix &b)
{
    if(b.rows != a.cols){
        std::cerr << "The Dimensions dont match ! \n";
        return Matrix(0,0,false);
    }

    Matrix res(a.rows,b.cols, true);

    for (unsigned int row = 0;row < res.rows ; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            double val = 0;
            for(unsigned int k = 0; k < a.cols;k++){
                val += a.getValue(row,k) * b.getValue(k,col);
            }
            res.setValue(row,col,val);

        }

    }

    return res;


}

Matrix Matrix::hadamard(const Matrix &a, const Matrix &b)
{
    if(a.rows != b.rows || a.cols != b.cols){
        std::cerr << "The dimensions dont match ! \n";
        return a;
    }

    Matrix ret(a.rows,a.cols);
    for (unsigned int i = 0; i < a.values.size(); i++) {
        ret.values[i] = a.values[i] * b.values[i];

    }
    return ret;

}

Matrix Matrix::sum(int axis)
{
    // Returns the sum of a Matrix on a given axis

    if(axis == 0){
        Matrix ret(this->rows,1);
        for(unsigned int i = 0; i < this->rows;i++){
            double sum = 0;
            for (unsigned int j = 0;j < this->cols; j++) {
                sum += this->getValue(i,j);
            }
            ret.setValue(i,0,sum);
        }
        return ret;


    }else if (axis == 1) {
        Matrix ret(1,this->cols);
        for (unsigned int i = 0; i < this->cols; i++) {
            double sum = 0;
            for (unsigned int j = 0; j < this->rows; j++) {
                sum += this->getValue(j,i);
            }
            ret.setValue(0,i,sum);
        }
        return ret;

    }else {
        return *this;

    }

}

Matrix Matrix::sum(const Matrix &a, int axis)
{
    // Returns the sum of a Matrix on a given axis

    if(axis == 0){
        Matrix ret(a.rows,1);
        for(unsigned int i = 0; i < a.rows;i++){
            double sum = 0;
            for (unsigned int j = 0;j < a.cols; j++) {
                sum += a.getValue(i,j);
            }
            ret.setValue(i,0,sum);
        }
        return ret;


    }else if (axis == 1) {
        Matrix ret(1,a.cols);
        for (unsigned int i = 0; i < a.cols; i++) {
            double sum = 0;
            for (unsigned int j = 0; j < a.rows; j++) {
                sum += a.getValue(j,i);
            }
            ret.setValue(0,i,sum);
        }
        return ret;

    }else {
        return a;

    }




}

void Matrix::transpose()
{
    Matrix res(this->cols,this->rows,true);
    for (unsigned int n = 0;n < this->values.size();n++) {
        unsigned int i = n/this->rows;
        unsigned int j = n%this->rows;
        res.values[n] = this->values[this->cols * j +i];

    }
    *this = res;


}

Matrix Matrix::transpose(const Matrix &a)
{
    Matrix res(a.cols,a.rows,true);
    for (unsigned int n = 0;n < a.values.size();n++) {
        unsigned int i = n/a.rows;
        unsigned int j = n%a.rows;
        res.values[n] = a.values[a.cols * j +i];

    }
    return res;

}

/**********************************************************************************/
/*                             OPERATOR OVERLOADS                                 */
/**********************************************************************************/

std::vector<double> Matrix::operator[](const unsigned long &index) const
{
    if(index > this->rows){
        std::cerr << "Index out of range";
        return this->values;
    }
    std::vector<double> ret;
    for(unsigned int i = 0; i < this->cols; i++){
        ret.push_back(getValue(index,i));
    }
    return ret;
}

Matrix Matrix::operator+(const double &val)
{
    Matrix ret(*this);
    ret.add(val);
    return ret;
}

Matrix Matrix::operator-(const double &val)
{
    Matrix ret(*this);
    ret.sub(val);
    return ret;
}

Matrix Matrix::operator*(const double &val)
{
    Matrix ret(*this);
    ret.multiply(val);
    return ret;
}

Matrix Matrix::operator/(const double &val)
{
    Matrix ret(*this);
    ret.divide(val);
    return ret;
}

Matrix Matrix::operator+=(const double &val)
{
    this->add(val);
    return *this;
}

Matrix Matrix::operator-=(const double &val)
{
    this->sub(val);
    return *this;
}

Matrix Matrix::operator*=(const double &val)
{
    this->multiply(val);
    return *this;
}

Matrix Matrix::operator/=(const double &val)
{
    this->divide(val);
    return *this;
}

Matrix Matrix::operator+(const Matrix &other)
{
    Matrix ret(*this);
    ret.add(other);
    return ret;
}

Matrix Matrix::operator-(const Matrix &other)
{
    Matrix ret(*this);
    ret.sub(other);
    return ret;
}

Matrix Matrix::operator*(const Matrix &other)
{
    Matrix ret(*this);
    ret.multiply(other);
    return ret;
}

Matrix Matrix::operator+=(const Matrix &other)
{
    this->add(other);
    return *this;
}

Matrix Matrix::operator-=(const Matrix &other)
{
    this->sub(other);
    return *this;
}

Matrix Matrix::operator*=(const Matrix &other)
{
    this->multiply(other);
    return *this;
}







Matrix operator-(double a, Matrix b)
{
    for (unsigned int i = 0; i < b.values.size(); i++) {
        b.values[i] = a - b.values[i];

    }
    return b;
}
