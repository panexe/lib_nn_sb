#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "activation.h"
#include "layer.h"
#include "inputlayer.h"
#include "outputlayer.h"
#include "denselayer.h"
#include "tensor.h"

class NeuralNetwork
{

    unsigned int input_size;
    unsigned int output_size;
    double lr;

    std::vector<Layer*> layers;

    static double sigmoid(const double& x);


public:

    static double sigmoid_d(const double& x);

    NeuralNetwork(unsigned int input_size);
    ~NeuralNetwork();

    void addLayer(unsigned int nodes, ACTIVATION activation = ACTIVATION::sigmoid);
    void addLayer(Layer *layer);
    void compile(unsigned int output_size, double lr = 0.01, ACTIVATION activation = ACTIVATION::sigmoid);

    Tensor feedForward(Tensor input);
    Tensor predict(Tensor input);
    void bp(Tensor x,Tensor y, bool quiet = true);
    void bp(std::vector<Tensor> x,std::vector<Tensor> y, bool quiet = true);


};

#endif // NEURALNETWORK_H
