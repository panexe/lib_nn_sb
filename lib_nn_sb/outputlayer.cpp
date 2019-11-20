#include "outputlayer.h"
#include "iostream"


Layer *OutputLayer::getInputLayer() const
{
    return inputLayer;
}

void OutputLayer::setInputLayer(Layer *value)
{
    inputLayer = value;
}

OutputLayer::OutputLayer(unsigned int num_nodes, ACTIVATION activation): Layer(num_nodes, activation)
{
}

void OutputLayer::init()
{
    std::cout << "Output layer init call \n";
}

Tensor OutputLayer::getDeriv()
{
    Tensor ret(this->nodes);
    ret.map(Activation::deriv(this->activation));
    return ret;
}
