 #include "convolutionallayer.h"

void ConvolutionalLayer::init()
{
    this->dimension = this->num_filers;
    unsigned int i;
    for (i=0;i<this->num_filers;i++) {
        filters.push_back(Tensor(filter_size,filter_size,inputLayer->getDimension()));
    }
}

Tensor ConvolutionalLayer::calc_output(bool)
{
    // TODO implement tensor from tensorlist
    // TODO impement sum over axis in tensor

    std::vector<Tensor> ret;
    unsigned int i;
    for (i=0; i<this->num_filers; i++) {
        Tensor add = Tensor::broadcast(this->nodes,this->filters[i]);
        add.sum(2);
        ret.push_back(add);
    }


}
