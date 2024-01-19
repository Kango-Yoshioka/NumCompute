//
// Created by kango on 2022/11/13.
//

#ifndef CONSTRAINED_DIFFERENTIAL_DIFFERENTIAL_H
#define CONSTRAINED_DIFFERENTIAL_DIFFERENTIAL_H

#include <functional>
#include "Variable.h"
#include "Function.h"

namespace AGU::NumCompute::Differential {

    double forwardDifference(const Function &func, const std::vector<Variable> &fVariables,
                             const std::vector<Variable> &variables, const double &h);

    double centralDifference(const Function &func, const std::vector<Variable> &fVariables,
                             const std::vector<Variable> &bVariables, const double &h);

    double backwardDifference(const Function &func, const std::vector<Variable> &variables,
                              const std::vector<Variable> &bVariables, const double &h);

    std::vector<Variable>
    getForwardVariables(const std::vector<Variable> &variables, const double &h, const int &forwardIdx);

    std::vector<Variable>
    getBackwardVariables(const std::vector<Variable> &variables, const double &h, const int &backwardIdx);

    std::vector<double> numericalGradient(const Function &func, const std::vector<Variable> &variables, const double &h=1e-4);

    std::vector<double> numericalGradientWithConstraint(const Function &func, const std::vector<Variable> &variables, const double &h, const int &batchSize);

} // Differential

#endif //CONSTRAINED_DIFFERENTIAL_DIFFERENTIAL_H
