//
// Created by kango on 2022/11/16.
//

#ifndef CONSTRAINED_DIFFERENTIAL_SGD_H
#define CONSTRAINED_DIFFERENTIAL_SGD_H

#include "BaseOptimizer.h"

namespace AGU::NumCompute::Optimizer {

    class SGD : public BaseOptimizer {
    public:
        SGD(const double &lr, const double &h, const std::vector<Variable> &variables, const Function &func, const double &convergenceCondition=1e-8, const int &batch_size=DEFAULT_BATCH_SIZE) : BaseOptimizer(lr, h, variables, func, convergenceCondition, batch_size) {}

        void updateVariables() override {
            for(unsigned int i = 0; i < m_variables.size(); i++) {
                const double newData = m_variables[i].getData() - m_lr * m_gradient[i];
                m_variables[i].setData(newData);
            }
        }
    };

} // Optimizer

#endif //CONSTRAINED_DIFFERENTIAL_SGD_H
