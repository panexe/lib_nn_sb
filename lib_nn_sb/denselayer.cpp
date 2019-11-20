#include "denselayer.h"
#include "iostream"

Layer *DenseLayer::getInputLayer() const
{
    return inputLayer;
}

void DenseLayer::setInputLayer(Layer *value)
{
    inputLayer = value;
}

Layer *DenseLayer::getOutputLayer() const
{
    return outputLayer;
}

void DenseLayer::setOutputLayer(Layer *value)
{
    outputLayer = value;
}

Tensor DenseLayer::getBias() const
{
    return bias;
}

void DenseLayer::setBias(const Tensor &value)
{
    bias = value;
}

DenseLayer::DenseLayer(unsigned int num_nodes_, ACTIVATION activation_, double dropout_prob_)
    : Layer (num_nodes_,activation_, dropout_prob_,LAYERTYPE::Dense)
{

}



DenseLayer::~DenseLayer()
{

}

void DenseLayer::init()
{
    if(outputLayer == nullptr){
        std::cerr << "No Output is set \n";
        return;
    }
    if(inputLayer == nullptr){
        std::cerr << "No Input is set \n";
        return;
    }

    this->weights = Tensor(outputLayer->getNum_nodes(),this->num_nodes);
    this->weights.randomize(-1,1);

    this->bias = Tensor(outputLayer->getNum_nodes(),1,INIT::ones);
    //this->bias.setAll(1);

    this->dimension = 1;

}
/* Return the output of this layer that the nodes of the next are set to
 * in train_mode the dropout functionality is possible
 */

Tensor DenseLayer::calc_output(bool train_mode)
{
    Tensor ret = this->weights * this->nodes;
    ret += this->bias;
    if(dropout_prob != 1.0 && train_mode){
        ret = dropout(ret,dropout_prob);
    }

    return ret;
}

Tensor DenseLayer::getDeriv()
{
    Tensor ret(this->nodes);
    ret.map(Activation::deriv(this->activation));
    return ret;
}

