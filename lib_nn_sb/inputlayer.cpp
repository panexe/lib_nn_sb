#include "inputlayer.h"

Layer *InputLayer::getOutputLayer() const
{
    return outputLayer;
}

void InputLayer::setOutputLayer(Layer *value)
{
    outputLayer = value;
}

Tensor InputLayer::getBias() const
{
    return bias;
}

void InputLayer::setBias(const Tensor &value)
{
    bias = value;
}

InputLayer::InputLayer(unsigned int num_nodes_,ACTIVATION activation_, double dropout_prob_):Layer(num_nodes_,activation_,dropout_prob_,LAYERTYPE::Dense)
{

}

InputLayer::~InputLayer()
{

}

void InputLayer::init()
{
    this->weights = Tensor(this->outputLayer->getNum_nodes(),this->num_nodes);
    this->weights.randomize(-1,1);

    this->bias = Tensor(this->outputLayer->getNum_nodes(),1);
    this->bias.setAll(1);

    this->dimension = 1;

}

Tensor InputLayer::calc_output(bool train_mode)
{
    Tensor ret = this->weights * this->nodes;
    ret += this->bias;
    if(dropout_prob != 1.0 && train_mode){
        ret = dropout(ret,dropout_prob);
    }
    return ret;

}

Tensor InputLayer::getDeriv()
{
    Tensor ret(this->nodes);
    ret.map(Activation::deriv(this->activation));
    return ret;
}





