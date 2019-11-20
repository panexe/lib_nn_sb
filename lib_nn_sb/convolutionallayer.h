#ifndef CONVOLUTIONALLAYER_H
#define CONVOLUTIONALLAYER_H

#include "layer.h"
#include "tensor.h"


class ConvolutionalLayer : public Layer
{
    std::vector<Tensor> filters;
    unsigned int filter_size;
    unsigned int num_filers;


public:
    ConvolutionalLayer(unsigned int num_filters=1,unsigned int filter_size = 3);

    void init() override;

    Tensor calc_output(bool) override;
};

#endif // CONVOLUTIONALLAYER_H
