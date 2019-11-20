#ifndef DENSELAYER_H
#define DENSELAYER_H

#include "layer.h"


class DenseLayer : public Layer
{




public:
    DenseLayer(unsigned int num_nodes, ACTIVATION activation, double dropout_prob = 1);
    ~DenseLayer() override;

    void init() override;
    Tensor calc_output(bool train_mode = true) override;

    Tensor getDeriv() override;



    Layer *getInputLayer() const override;
    void setInputLayer(Layer *value) override;
    Layer *getOutputLayer() const override;
    void setOutputLayer(Layer *value) override;
    Tensor getBias() const override;
    void setBias(const Tensor &value) override;
};

#endif // DENSELAYER_H
