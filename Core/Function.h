//
// Created by kango on 2022/11/16.
//

#ifndef CONSTRAINED_DIFFERENTIAL_FUNCTION_H
#define CONSTRAINED_DIFFERENTIAL_FUNCTION_H

#include <functional>
#include "Variable.h"

namespace AGU::NumCompute {
    using Function = std::function<double(const std::vector<Variable> &)>;
}


#endif //CONSTRAINED_DIFFERENTIAL_FUNCTION_H
