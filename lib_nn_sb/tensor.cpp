#include "tensor.h"
#include <iostream>

unsigned int Tensor::getRank() const
{
    return rank;
}

void Tensor::setRank(unsigned int value)
{
    rank = value;
}

unsigned int Tensor::getRows() const
{
    return rows;
}

void Tensor::setRows(unsigned int value)
{
    rows = value;
}

unsigned int Tensor::getCols() const
{
    return cols;
}

void Tensor::setCols(unsigned int value)
{
    cols = value;
}

unsigned int Tensor::getLayers() const
{
    return layers;
}

void Tensor::setLayers(unsigned int value)
{
    layers = value;
}

Tensor::Tensor(unsigned int rows_,unsigned int cols_, unsigned int layers_, INIT init)
    :rows(rows_),cols(cols_),layers(layers_),rank(3)
{
    this->values.reserve(rows*cols*layers);

    if(init==INIT::none)
        return;

    if(init == INIT::zeros){
        unsigned int i;
        for (i=0; i<rows*cols; i++) {
            this->values.emplace_back(0);
        }
        return;
    }
    if(init == INIT::ones){
        unsigned int i;
        for (i=0; i<rows*cols; i++) {
            this->values.emplace_back(1);
        }
        return;
    }

}

Tensor::Tensor(unsigned int rows_, unsigned int cols_, INIT init)
    :rows(rows_),cols(cols_),layers(0),rank(2)
{
    this->values.reserve(rows*cols);
    if(init==INIT::none)
        return;

    if(init == INIT::zeros){
        unsigned int i;
        for (i=0; i<rows*cols; i++) {
            this->values.emplace_back(0);
        }
        return;
    }
    if(init == INIT::ones){
        unsigned int i;
        for (i=0; i<rows*cols; i++) {
            this->values.emplace_back(1);
        }
        return;
    }

}

Tensor::Tensor(const Tensor& other){
    this->rank = other.rank;
    this->rows = other.rows;
    this->cols = other.cols;
    this->layers = other.layers;
    this->values = other.values;
}

Tensor::Tensor(){
    this->rank = 0;
    this->rows = 0;
    this->cols = 0;
    this->layers = 0;
}

Tensor::~Tensor(){

}

void Tensor::print()
{
    if(this->rank == 3)
        return;

    printf("Matrix (%dx%d): \n",this->rows,this->cols);
    for(unsigned int i = 0; i < this->rows;i++){
        for (unsigned int j = 0; j < this->cols; j++) {
            printf("%-10.2f", (*this)(i,j));
        }
        printf("\n");
    }
}

double Tensor::get(const unsigned int& x,const unsigned int& y,const unsigned int& z) const{
    if(this->rank != 3){
        std::cerr << "Arguments dont match tensor dimensions! \n";
        return 0;
    }
    if(x > rows || y > cols || z > layers){
        std::cerr << "Index out of bounds! \n";
        return 0;
    }
    return this->values[(x * cols + y) * layers + z];
}

double Tensor::get(const unsigned int& x,const unsigned int& y) const{
    if(this->rank != 2){
        std::cerr << "Arguments dont match tensor dimensions! \n";
        return 0;
    }
    if(x > rows || y > cols){
        std::cerr << "Index out of bounds! \n";
        return 0;
    }
    return values[cols * x + y];
}

void Tensor::set(const unsigned int &x, const unsigned int &y, const unsigned int &z, const double &val)
{
    if(this->rank != 3){
        std::cerr << "Arguments dont match tensor dimensions! \n";
        return;
    }
    if(y > cols || x > rows || z > layers){
        std::cerr << "Index out of bounds! \n";
        return;
    }
    this->values[(x * cols + y) * layers + z] = val;
    // old : (x + cols * (y + layers * z))
    // (i * cols + j) * layers + k
}

void Tensor::set(const unsigned int &x, const unsigned int &y, const double &val)
{
    if(this->rank != 2){
        std::cerr << "Arguments dont match tensor dimensions! \n";
        return;
    }
    if(y > cols || x > rows){
        std::cerr << "Index out of bounds! \n";
        return;
    }
    values[cols * x + y] = val;
}

void Tensor::setAll(const double & val)
{
    unsigned int i;
    for(i=0; i<this->values.size(); i++){
        this->values[i] =val;
    }
}

Tensor Tensor::fromVector(const std::vector<double> vector, const unsigned int &axis)
{
    if(axis==1){
        Tensor ret(vector.size(),1);
        ret.values = vector;
        return ret;
    }
    if(axis==0){
        Tensor ret(1,vector.size());
        ret.values = vector;
        return ret;
    }
    std::cerr << "Not a valid axis for a Tensor of rank 2! \n";
    return Tensor(0,0);
}

std::vector<double> Tensor::toVector()
{
    return this->values;
}

Tensor Tensor::fromVectorList(const std::vector<Tensor> tensors)
{
    unsigned int num_layers = 0;
    for (unsigned int i = 0; i<tensors.size(); i++) {
        num_layers += tensors[i].layers;
    }

    // NOT TESTED
    Tensor res(tensors[0].rows,tensors[0].cols,num_layers);

    unsigned int i;
    for (i=0; i<tensors.size(); i++) {
        if(i<tensors.size()-1)
            if(tensors[i].rows != tensors[i+1].rows || tensors[i].cols != tensors[i+1].cols){
                std::cerr << "All Tensors must have the same width and height! \n";
                return Tensor(0,0);
            }

        unsigned int a,b,c;
        for (c=0; c<tensors[i].layers; c++) {
            for (a=0; a<res.rows; a++) {
                for (b=0; b<res.rows; b++) {
                    res.set(a,b,i,tensors[i].get(a,b,c));
                }
            }
        }
    }

    return res;


}

void Tensor::map(double (*func)(double))
{
    unsigned int i;
    for (i=0; i<this->values.size(); i++) {
        this->values[i] = func(this->values[i]);
    }
}

Tensor Tensor::map(Tensor tensor, double (*func)(double))
{
    unsigned int i;
    for (i=0; i<tensor.values.size(); i++) {
        tensor.values[i] = func(tensor.values[i]);
    }
    return tensor;
}

void Tensor::randomize(const int &min, const int &max)
{
    srand(time(NULL));
    unsigned int i;
    for (i=0; i<this->values.size(); i++){
        this->values[i] = min + static_cast<double>(rand()) /( static_cast<double>(RAND_MAX/(max-min)));
    }
}

Tensor Tensor::randomize(Tensor tensor, const int &min, const int &max)
{
    srand(time(NULL));
    unsigned int i;
    for (i=0; i<tensor.values.size(); i++){
        tensor.values[i] = min + static_cast<double>(rand()) /( static_cast<double>(RAND_MAX/(max-min)));
    }
    return tensor;
}

void Tensor::transpose()
{
    if(rank==3){
        std::cerr << "Cannot transpose 3D Tensors! \n";
        return;
    }
    Tensor res(this->cols,this->rows);
    for (unsigned int n = 0;n < this->values.size();n++) {
        unsigned int i = n/this->rows;
        unsigned int j = n%this->rows;
        res.values[n] = this->values[this->cols * j +i];
    }
    *this = res;

}

Tensor Tensor::transpose(Tensor tensor)
{
    if(tensor.rank == 3){
        std::cerr << "Cannot transpose 3D Tensors! \n";
        return tensor;
    }
    Tensor res(tensor.cols,tensor.rows);
    for (unsigned int n = 0;n < tensor.values.size();n++) {
        unsigned int i = n/tensor.rows;
        unsigned int j = n%tensor.rows;
        res.values[n] = tensor.values[tensor.cols * j +i];
    }
    return res;
}

Tensor Tensor::sum(const unsigned int &axis)
{
    // TODO
    if(axis == 0){
        if(this->rank == 2){
            Tensor res(1,this->cols);
            unsigned int i,j;
            for (i=0; i<this->cols; i++) {
                double sum = 0;
                for (j=0; j<this->rows; j++) {
                    sum += this->get(i,j);
                }
                res.set(1,j,sum);
            }
        }

    }
    if(axis == 1){

    }
    if(axis == 2){

    }
}

Tensor Tensor::sum(Tensor tensor, const unsigned int &axis)
{
    // TODO
}


/**********************************************************************************/
/*                             SCALAR OPERATIONS                                  */
/**********************************************************************************/

void Tensor::add(const double &val)
{
    unsigned int i;
    for (i=0; i<this->values.size(); i++){
        this->values[i] += val;
    }
}

void Tensor::sub(const double &val)
{
    unsigned int i;
    for (i=0; i<this->values.size(); i++){
        this->values[i] -= val;
    }
}

void Tensor::multiply(const double &val)
{
    unsigned int i;
    for (i=0; i<this->values.size(); i++){
        this->values[i] *= val;
    }
}

void Tensor::divide(const double &val)
{
    unsigned int i;
    for (i=0; i<this->values.size(); i++){
        this->values[i] /= val;
    }
}

Tensor Tensor::add(Tensor t, const double &val)
{
    unsigned int i;
    for (i=0; i<t.values.size(); i++){
        t.values[i] += val;
    }
    return t;
}

Tensor Tensor::sub(Tensor t, const double &val)
{
    unsigned int i;
    for (i=0; i<t.values.size(); i++){
        t.values[i] -= val;
    }
    return t;
}

Tensor Tensor::multiply(Tensor t, const double &val)
{
    unsigned int i;
    for (i=0; i<t.values.size(); i++){
        t.values[i] *= val;
    }
    return t;
}

Tensor Tensor::divide(Tensor t, const double &val)
{
    unsigned int i;
    for (i=0; i<t.values.size(); i++){
        t.values[i] /= val;
    }
    return t;
}

/**********************************************************************************/
/*                             TENSOR OPERATIONS                                  */
/**********************************************************************************/

void Tensor::add(const Tensor &other)
{
    if(this->rank != other.rank){
        std::cerr << "Cant add Tensors of different dimensions! \n";
        return;
    }
    if(this->cols != other.cols || this->rows != other.rows || this->layers != other.layers){
        std::cerr << "Cant add Tensors of different size! \n";
        return;
    }

    unsigned int i;
    for (i=0; i<this->values.size(); i++) {
        this->values[i] += other.values[i];
    }
}

void Tensor::sub(const Tensor &other)
{
    if(this->rank != other.rank){
        std::cerr << "Cant subtract Tensors of different dimensions! \n";
        return;
    }
    if(this->cols != other.cols || this->rows != other.rows || this->layers != other.layers){
        std::cerr << "Cant subtract Tensors of different size! \n";
        return;
    }

    unsigned int i;
    for (i=0; i<this->values.size(); i++) {
        this->values[i] -= other.values[i];
    }
}

void Tensor::multiply(const Tensor &other)
{
    if(this->rank != 2 || other.rank != 2){
        std::cerr << "Multiplication is only available for 2D-Tensors!\n";
        return;
    }
    if(this->cols != other.rows){
        std::cerr << "The Dimensions dont match up ! \n";
        return;
    }

    Tensor res(this->rows,other.cols);
    unsigned int row,col,k;
    for (row=0; row<res.rows; row++) {
        for (col=0; col<res.cols; col++) {
            double val = 0;
            for(k=0; k<this->cols; k++){
                val += this->get(row,k) *  other.get(k,col);
            }
            res.set(row,col,val);

        }
    }
    *this = res;

}

void Tensor::hadamard(const Tensor &other)
{
    if(this->rank != other.rank){
        std::cerr << "Cant hadamard Tensors of different dimensions! \n";
        return;
    }
    if(this->cols != other.cols || this->rows != other.rows || this->layers != other.layers){
        std::cerr << "Cant hadamard Tensors of different size! \n";
        return;
    }

    unsigned int i;
    for (i=0; i<this->values.size(); i++) {
        this->values[i] *= other.values[i];
    }
}

void Tensor::broadcast(const Tensor &other)
{
    if(this->rank != other.rank){
        std::cerr << "Cant broadcast Tensors of different dimensions! \n";
        return;
    }
    if(this->rank == 3){
        if(this->layers != other.layers){
            std::cerr << "The amount of layers has to be the same to broadcast! \n";
            return;
        }
        if(other.rows >= this->rows || other.cols >= this->cols){
            std::cerr << "The broadcast Tensor has to be smaller than this! \n";
            return;
        }
        // calc size of the outputs
        unsigned int new_rows = this->rows - other.rows +1;
        unsigned int new_cols = this->cols - other.cols +1;

        Tensor ret(new_rows,new_cols,other.layers);

        unsigned int i,j,k,x,y;
        for (k=0;k<ret.layers;k++) {
            for (i=0;i<new_rows;i++) {
                for (j=0;j<new_cols;j++) {
                    double sum = 0;
                    for (x=0;x<other.rows;x++) {
                        for (y=0;y<other.cols;y++) {
                            sum += this->get(i+x,j+y,k) * other.get(x,y,k);
                        }
                    }
                    ret.set(i,j,k,sum);
                }
            }
        }
        *this = ret;
        return;


    }
    if(this->rank == 2){
        if(other.rows >= this->rows || other.cols >= this->cols){
            std::cerr << "The second Matrix has to be smaller than this !\n";
            return;
        }

        unsigned int new_rows = this->rows - other.rows +1;
        unsigned int new_cols = this->cols - other.cols +1;

        Tensor res(new_rows,new_cols);

        unsigned int i,j;
        for (i=0; i<new_rows; i++) {
            for (j=0; j<new_cols; j++) {
                double sum = 0;
                unsigned int a,b;
                for (a=0; a<other.rows; a++) {
                    for (b=0; b<other.cols; b++) {
                        sum += this->get(i+a,j+b) * other.get(a,b);
                    }
                }
                res.set(i,j,sum);
            }
        }
        *this = res;
    }


}

Tensor Tensor::add(Tensor a, const Tensor &b)
{
    a.add(b);
    return a;
}

Tensor Tensor::sub(Tensor a, const Tensor &b)
{
    a.sub(b);
    return a;
}

Tensor Tensor::multiply(Tensor a, const Tensor &b)
{
    a.multiply(b);
    return a;
}

Tensor Tensor::hadamard(Tensor a, const Tensor &b)
{
    a.hadamard(b);
    return a;
}

Tensor Tensor::broadcast(Tensor a, const Tensor &b)
{
    a.broadcast(b);
    return a;
}


