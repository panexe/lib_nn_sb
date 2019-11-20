#ifndef LAYER_H
#define LAYER_H

#include "tensor.h"
#include "activation.h"


enum LAYERTYPE{
    Dense
};

class Layer
{
protected:

    double dropout_prob;

    template<typename T>
    T dropout(T a,double prob);

    unsigned int num_nodes;
    unsigned int dimension;

    Tensor nodes;
    Tensor weights;
    Tensor bias;

    ACTIVATION activation;


    const LAYERTYPE type;

    Layer *inputLayer;
    Layer *outputLayer;



public:
    Layer(unsigned int num_nodes,ACTIVATION activation = ACTIVATION::sigmoid,double dropout_prob = 1,LAYERTYPE type = LAYERTYPE::Dense);
    virtual ~Layer();

    virtual void init() = 0;
    virtual Tensor calc_output(bool train_mode = true);

    void activate();
    virtual Tensor getDeriv();


    Tensor getNodes() const;
    void setNodes(const Tensor &value);

    Tensor dropout(Tensor a,double prob);


    unsigned int getNum_nodes() const;

    virtual Layer *getInputLayer() const;
    virtual void setInputLayer(Layer *value);
    virtual Layer *getOutputLayer() const;
    virtual void setOutputLayer(Layer *value);
    virtual Tensor getBias() const;
    virtual void setBias(const Tensor &value);
    Tensor getWeights() const;
    void setWeights(const Tensor &value);
    virtual unsigned int getDimension() const;
    virtual void setDimension(unsigned int value);
};

#endif // LAYER_H
