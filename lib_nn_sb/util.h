#ifndef UTIL_H
#define UTIL_H

#include "tensor.h"
#include <string>

class util
{
public:
    util();

    static Tensor read_idx(std::string file);

};

#endif // UTIL_H
