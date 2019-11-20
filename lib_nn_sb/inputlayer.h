#ifndef INPUTLAYER_H
#define INPUTLAYER_H

#include "layer.h"

class InputLayer : public Layer
{



public:
    InputLayer(unsigned int num_nodes,ACTIVATION activation = ACTIVATION::sigmoid, double dropout_prob = 1);
    ~InputLayer() override;

    void init() override;
    Tensor calc_output(bool train_mode = true) override;

    Tensor getDeriv() override;


    Layer *getOutputLayer() const override;
    void setOutputLayer(Layer *value) override;
    Tensor getBias() const override;
    void setBias(const Tensor &value) override;
};

#endif // INPUTLAYER_H
