//
// Created by kango on 2022/11/17.
//

#ifndef CONSTRAINED_DIFFERENTIAL_OPTDIFFERENTIATOR_H
#define CONSTRAINED_DIFFERENTIAL_OPTDIFFERENTIATOR_H

#include "Function.h"

namespace AGU::NumCompute::Differential {

    /**
     * Optimizer用の微分器
     */
    class OptDifferentiator {
    private:
        double m_h{};
        Function m_func;
    public:
        OptDifferentiator();

        OptDifferentiator(const double &h, const Function &func);

        std::vector<double> numericalGradientWithConstraint(const std::vector<Variable> &variables, const int &batchSize);

        double getH() const;

        const Function &getFunc() const;
    };

} // Differential

#endif //CONSTRAINED_DIFFERENTIAL_OPTDIFFERENTIATOR_H
