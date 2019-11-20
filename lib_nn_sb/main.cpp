#include <iostream>
#include "neuralnetwork.h"
#include "util.h"

using namespace std;

int main()
{

    //return 0;






    /*
    Matrix mat1(4,4);
    mat1.randomize(-10,10);
    Matrix mat2(mat1);

    mat1 = Matrix::hadamard(mat1,1-mat1);
    mat2 = Matrix::map(mat2,NeuralNetwork::sigmoid_d);

    mat1.print();
    mat2.print();
    return 0;
    */

    //util::read_idx("./data/train-images-idx3-ubyte");

    // XOR PROBLEM
    std::vector<double> vals0{0,0};
    std::vector<double> vals1{0,1};
    std::vector<double> vals2{1,0};
    std::vector<double> vals3{1,1};
    std::vector<double> result0{0};
    std::vector<double> result1{1};

    // NETWORK
    NeuralNetwork nn(2);
    nn.addLayer(new DenseLayer(3,ACTIVATION::tan_h,1));
    nn.compile(1,0.1);

    /*
    std::vector<Matrix> x_data;
    x_data.push_back(Matrix::fromVector(vals0));
    x_data.push_back(Matrix::fromVector(vals1));
    x_data.push_back(Matrix::fromVector(vals2));
    x_data.push_back(Matrix::fromVector(vals3));

    std::vector<Matrix> y_data;
    y_data.push_back(Matrix::fromVector(result0));
    y_data.push_back(Matrix::fromVector(result1));
    y_data.push_back(Matrix::fromVector(result1));
    y_data.push_back(Matrix::fromVector(result0));
    */




    Tensor
    res =nn.predict(Tensor::fromVector(vals0));
    res.print();
    res =nn.predict(Tensor::fromVector(vals1));
    res.print();
    res =nn.predict(Tensor::fromVector(vals2));
    res.print();
    res =nn.predict(Tensor::fromVector(vals3));
    res.print();

    //return 0;

    for(int i = 0; i < 10000;i++){
        nn.bp(Tensor::fromVector(vals0),Tensor::fromVector(result0));
        nn.bp(Tensor::fromVector(vals1),Tensor::fromVector(result1));
        nn.bp(Tensor::fromVector(vals2),Tensor::fromVector(result1));
        nn.bp(Tensor::fromVector(vals3),Tensor::fromVector(result0));

    }
    res =nn.predict(Tensor::fromVector(vals0));
    res.print();
    res =nn.predict(Tensor::fromVector(vals1));
    res.print();
    res =nn.predict(Tensor::fromVector(vals2));
    res.print();
    res =nn.predict(Tensor::fromVector(vals3));
    res.print();


    return 0;
}
