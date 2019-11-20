#ifndef TENSOR_H
#define TENSOR_H

#include <vector>

enum INIT{
    none,
    zeros,
    ones
};

class Tensor
{
    unsigned int rank;
    unsigned int rows;
    unsigned int cols;
    unsigned int layers;

    std::vector<double> values;

public:
    Tensor(unsigned int rows,unsigned int cols, unsigned int layers, INIT init = INIT::zeros);
    Tensor(unsigned int rows,unsigned int cols,INIT init= INIT::zeros);
    Tensor();
    Tensor(const Tensor& other);
    ~Tensor();

    void print();

    double get(const unsigned int&,const unsigned int&,const unsigned int&) const;
    double get(const unsigned int&,const unsigned int&) const;

    void set(const unsigned int&,const unsigned int&,const unsigned int&,const double&);
    void set(const unsigned int&,const unsigned int&, const double&);
    void setAll(const double&);

    static Tensor fromVector(const std::vector<double>,const unsigned int& axis=1);
    std::vector<double> toVector();

    static Tensor fromVectorList(const std::vector<Tensor> tensors);

    void map(double(*func)(double val));
    static Tensor map(Tensor tensor,double(*func)(double val));

    void randomize(const int& min,const int& max);
    static Tensor randomize(Tensor tensor,const int& min, const int& max);

    void transpose();
    static Tensor transpose(Tensor tensor);

    Tensor sum(const unsigned int& axis);
    static Tensor sum(Tensor tensor, const unsigned int& axis);

    /**********************************************************************************/
    /*                             SCALAR OPERATIONS                                  */
    /**********************************************************************************/

    void add(const double& val);
    void sub(const double& val);
    void multiply(const double& val);
    void divide(const double& val);

    static Tensor add(Tensor t,const double& val);
    static Tensor sub(Tensor t,const double& val);
    static Tensor multiply(Tensor t,const double& val);
    static Tensor divide(Tensor t,const double& val);

    /**********************************************************************************/
    /*                             MATRIX OPERATIONS                                  */
    /**********************************************************************************/

    void add(const Tensor& other);
    void sub(const Tensor& other);
    void multiply(const Tensor& other);
    void hadamard(const Tensor& other);
    void broadcast(const Tensor& other);

    static Tensor add(Tensor a, const Tensor& b);
    static Tensor sub(Tensor a, const Tensor& b);
    static Tensor multiply(Tensor a, const Tensor& b);
    static Tensor hadamard(Tensor a, const Tensor& b);
    static Tensor broadcast(Tensor a, const Tensor& b);


    /**********************************************************************************/
    /*                             OPERATOR OVERLOADS                                 */
    /**********************************************************************************/

    void operator=(const Tensor& other){
        this->rank = other.rank;
        this->rows = other.rows;
        this->cols = other.cols;
        this->layers = other.layers;
        this->values = other.values;
    }

    double operator()(unsigned int x, unsigned int y, unsigned int z){
        return this->get(x,y,z);
    }
    double operator()(unsigned int x, unsigned int y){
        return this->get(x,y);
    }

    Tensor operator+(const Tensor& other){
        Tensor ret(*this);
        ret.add(other);
        return ret;
    }
    Tensor operator-(const Tensor& other){
        Tensor ret(*this);
        ret.sub(other);
        return ret;
    }
    Tensor operator*(const Tensor& other){
        Tensor ret(*this);
        ret.multiply(other);
        return ret;
    }
    Tensor operator+(const double& val){
        Tensor ret(*this);
        ret.add(val);
        return ret;
    }
    Tensor operator-(const double& val){
        Tensor ret(*this);
        ret.sub(val);
        return ret;
    }
    Tensor operator*(const double& val){
        Tensor ret(*this);
        ret.multiply(val);
        return ret;
    }
    Tensor operator/(const double& val){
        Tensor ret(*this);
        ret.divide(val);
        return ret;
    }

    void operator+=(const Tensor& other){
        this->add(other);
    }
    void operator-=(const Tensor& other){
        this->sub(other);
    }
    void operator*=(const Tensor& other){
        this->multiply(other);
    }
    void operator+=(const double& val){
        this->add(val);
    }
    void operator-=(const double& val){
        this->sub(val);
    }
    void operator*=(const double& val){
        this->multiply(val);
    }
    void operator/=(const double& val){
        this->divide(val);
    }







    unsigned int getRank() const;
    void setRank(unsigned int value);
    unsigned int getRows() const;
    void setRows(unsigned int value);
    unsigned int getCols() const;
    void setCols(unsigned int value);
    unsigned int getLayers() const;
    void setLayers(unsigned int value);
};




#endif // TENSOR_H
