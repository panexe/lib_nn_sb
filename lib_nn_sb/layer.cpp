#include "layer.h"
#include "iostream"

Tensor Layer::getNodes() const
{
    return nodes;
}

void Layer::setNodes(const Tensor &value)
{
    nodes = value;
}

unsigned int Layer::getNum_nodes() const
{
    return num_nodes;
}

Layer *Layer::getInputLayer() const
{
    return inputLayer;
}

void Layer::setInputLayer(Layer *value)
{
    inputLayer = value;
}

Layer *Layer::getOutputLayer() const
{
    return outputLayer;
}

void Layer::setOutputLayer(Layer *value)
{
    outputLayer = value;
}

Tensor Layer::getBias() const
{
    return bias;
}

void Layer::setBias(const Tensor &value)
{
    bias = value;
}

Tensor Layer::getWeights() const
{
    return weights;
}

void Layer::setWeights(const Tensor &value)
{
    weights = value;
}

Layer::Layer(unsigned int num_nodes_,ACTIVATION activation_,double dropout_prob_, LAYERTYPE type_)
    : dropout_prob(dropout_prob_),num_nodes(num_nodes_),activation(activation_),type(type_)
{


}


Tensor Layer::dropout(Tensor a,double prob)
{
    Tensor ret(a.getRows(),a.getCols());
    ret.randomize(0,1);
    unsigned int i =0;
    for(i = 0; i < ret.getRows();i++){
        if(ret(i,0) > prob){
            ret.set(i,0,0);
        }else{
            ret.set(i,0,a(i,0));
        }
    }
    return ret;

}


unsigned int Layer::getDimension() const
{
    return dimension;
}

void Layer::setDimension(unsigned int value)
{
    dimension = value;
}

Layer::~Layer()
{

}

Tensor Layer::calc_output(bool train_mode)
{

}

void Layer::init()
{

}


void Layer::activate()
{
    this->nodes.map(Activation::func(this->activation));
}

Tensor Layer::getDeriv()
{

}

