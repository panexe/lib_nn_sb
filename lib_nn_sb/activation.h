#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "cmath"
#include "tensor.h"


enum ACTIVATION{
    sigmoid = 0,
    tan_h = 1,
    relu = 2,
    softmax = 3
};

class Activation
{
    ACTIVATION actv;

    static double sigmoid(double x);
    static double sigmoid_d(double x);

    static double tan_h(double x);
    static double tan_h_d(double x);

    static double relu(double x);
    static double relu_d(double x);

public:
    typedef double (*FNP)(double);
    static FNP func(ACTIVATION x);
    static FNP deriv(ACTIVATION x);




    static double exp(const double& x);

    Activation();
    double (*(*f2)(double))(ACTIVATION a);
    double (*getFunc(void))(ACTIVATION a);
    double deriv(const double& x);

    static Tensor softmax(const Tensor& x);
    static Tensor softmax_d(const Tensor& x);



};

#endif // ACTIVATION_H
