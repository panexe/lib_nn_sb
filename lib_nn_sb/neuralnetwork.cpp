#include "neuralnetwork.h"
#include <cmath>
#include <iostream>


double NeuralNetwork::sigmoid(const double &x)
{
    return 1 / (1 + exp(-x));
}

double NeuralNetwork::sigmoid_d(const double &x)
{
    return x * (1-x);
}



NeuralNetwork::NeuralNetwork(unsigned int input_size_):input_size(input_size_)
{
    this->layers.push_back(new InputLayer(input_size));

}

NeuralNetwork::~NeuralNetwork()
{
    for(unsigned int i = 0; i < this->layers.size();i++){
        delete this->layers[i];
    }

}

void NeuralNetwork::addLayer(unsigned int nodes, ACTIVATION activation)
{
    if(nodes != 0){
        this->layers.push_back(new DenseLayer(nodes,activation));
        return;
    }
    std::cerr << "0 isnt a valid amount of nodes ";

}

void NeuralNetwork::addLayer(Layer* layer)
{
    this->layers.push_back(layer);

}

void NeuralNetwork::compile(unsigned int output_size, double lr_, ACTIVATION activation)
{
    // INITS ALL LAYERS AND SETS THE OPTIMIZING OPTIONS / TODO: ADAM and RmsPROP

    this->lr = lr_;
    this->output_size = output_size;

    // ADD THE OUTPUT LAYER
    this->layers.push_back(new OutputLayer(output_size,activation));

    // CONNECT ALL LAYERS TO THE ONE BEFORE AND AFTER
    // THEN CALL THE INIT FUNCTION

    this->layers[0]->setOutputLayer(this->layers[1]);
    this->layers[0]->init();

    unsigned int i;
    for(i = 1; i <this->layers.size()-1;i++){
        layers[i]->setInputLayer(layers[i-1]);
        layers[i]->setOutputLayer(layers[i+1]);
        layers[i]->init();
    }
    layers[i]->setInputLayer(layers[i-1]);
    layers[i]->init();

}

Tensor NeuralNetwork::feedForward(Tensor input)
{
    // CHECK INPUT DIMS
    if(input.getCols() != 1 || input.getRows() != this->input_size ){
        std::cerr << "The input-size is wrong !\n";
        return Tensor(0,0);
    }

    this->layers[0]->setNodes(input);

    unsigned int i;
    for(i = 1; i < this->layers.size();i++){
        this->layers[i]->setNodes(layers[i-1]->calc_output());
        this->layers[i]->activate();

    }
    return this->layers[i-1]->getNodes();

}

Tensor NeuralNetwork::predict(Tensor input)
{
    // CHECK INPUT DIMS
    if(input.getCols() != 1 || input.getRows() != this->input_size ){
        std::cerr << "The input-size is wrong !\n";
        return Tensor(0,0);
    }

    this->layers[0]->setNodes(input);

    unsigned int i;
    for(i = 1; i < this->layers.size();i++){
        this->layers[i]->setNodes(layers[i-1]->calc_output(false));
        this->layers[i]->activate();

    }
    return this->layers[i-1]->getNodes();
}



void NeuralNetwork::bp(Tensor x, Tensor y, bool quiet)
{
    if(x.getCols() != 1 || x.getRows() != this->input_size){
        std::cerr << "The input Matrix doesnt match the net ! \n";
        return;
    }
    if(y.getCols() != 1 || y.getRows() != this->output_size){
        std::cerr << "The output Matrix doesnt match the net ! \n";
        return;
    }


    // FEED FORWARD
    this->feedForward(x);


    unsigned long long i = this->layers.size()-1;

    // CALC THE ERROR (MSE) (deriv)
    Tensor error = layers[i]->getNodes() - y;

    // PRINT THE MSE TO THE CONSOLE
    //if(!quiet)
        //std::cout << "Error : " << 0.5*(error.sum().toVector()[0])*(error.sum().toVector()[0]) << std::endl;


    // CALCULATIONS FOR THE OUTPUT LAYER:
    Tensor deriv = layers[i]->getDeriv();
    Tensor delta = Tensor::hadamard(error,deriv);


    Tensor delta_weight = delta * Tensor::transpose(this->layers[i-1]->getNodes());

    // APPLY GRADIENT TO THE WEIGHTS AND BIAS
    this->layers[i-1]->setWeights(this->layers[i-1]->getWeights() - delta_weight * lr);
    this->layers[i-1]->setBias(this->layers[i-1]->getBias() - delta * lr);

    i--;
    for(;i > 0;i--){
        // GET THE DERIV OF THE CURRENT LAYER
        deriv = layers[i]->getDeriv();
        delta = Tensor::transpose(layers[i]->getWeights()) * delta;
        delta.hadamard(deriv);
        delta_weight = delta * Tensor::transpose(this->layers[i-1]->getNodes());

        this->layers[i-1]->setWeights(this->layers[i-1]->getWeights() - delta_weight * lr);
        this->layers[i-1]->setBias(this->layers[i-1]->getBias() - delta * lr);


    }


}

void NeuralNetwork::bp(std::vector<Tensor> x, std::vector<Tensor> y, bool quiet)
{
    // just checking the first objects, its quiet possible that there are dimension errors
    // in other Matrices, but this should be taken care of before the bp

    if(x[0].getCols() != 1 || x[0].getRows() != this->input_size){
        std::cerr << "The input Matrix doesnt match the net ! \n";
        return;
    }
    if(y[0].getCols() != 1 || y[0].getRows() != this->output_size){
        std::cerr << "The output Matrix doesnt match the net ! \n";
        return;
    }
    if(x.size() != y.size()){
        std::cerr << "The amount of data in x doesnt macht the amount in y !\n";
    }

    Tensor error(y[0].getRows(),y[0].getCols());

    unsigned int a;
    for(a = 0; a < x.size();a++){
        this->feedForward(x[a]);
        error += layers[layers.size()-1]->getNodes() - y[a];

    }
    error /= x.size();


    unsigned long long i = this->layers.size()-1;


    // PRINT THE MSE TO THE CONSOLE
    //if(!quiet)
        //std::cout << "Error : " << 0.5*(error.sum().toVector()[0])*(error.sum().toVector()[0]) << std::endl;


    // CALCULATIONS FOR THE OUTPUT LAYER:
    Tensor deriv = layers[i]->getDeriv();
    Tensor delta = Tensor::hadamard(error,deriv);


    Tensor delta_weight = delta * Tensor::transpose(this->layers[i-1]->getNodes());

    // APPLY GRADIENT TO THE WEIGHTS AND BIAS
    this->layers[i-1]->setWeights(this->layers[i-1]->getWeights() - delta_weight * lr);
    this->layers[i-1]->setBias(this->layers[i-1]->getBias() - delta * lr);

    i--;
    for(;i > 0;i--){
        // GET THE DERIV OF THE CURRENT LAYER
        deriv = layers[i]->getDeriv();
        delta = Tensor::transpose(layers[i]->getWeights()) * delta;
        delta.hadamard(deriv);
        delta_weight = delta * Tensor::transpose(this->layers[i-1]->getNodes());

        this->layers[i-1]->setWeights(this->layers[i-1]->getWeights() - delta_weight * lr);
        this->layers[i-1]->setBias(this->layers[i-1]->getBias() - delta * lr);


    }

}
