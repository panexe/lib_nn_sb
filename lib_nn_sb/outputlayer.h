#ifndef OUTPUTLAYER_H
#define OUTPUTLAYER_H

#include "layer.h"


class OutputLayer : public Layer
{


public:
    OutputLayer(unsigned int num_nodes, ACTIVATION activation);

    void init() override;

    Tensor getDeriv() override;


    Layer *getInputLayer() const override;
    void setInputLayer(Layer *value) override;
};

#endif // OUTPUTLAYER_H
