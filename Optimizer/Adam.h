//
// Created by kango on 2022/11/16.
//

#ifndef CONSTRAINED_DIFFERENTIAL_ADAM_H
#define CONSTRAINED_DIFFERENTIAL_ADAM_H

#include <vector>
#include <cmath>
#include "Variable.h"
#include "Function.h"
#include "BaseOptimizer.h"

namespace AGU::NumCompute::Optimizer {
    class Adam : public BaseOptimizer{
    private:
        double m_b1, m_b2, m_eps;
        std::vector<double> ms, vs;
    public:
        Adam(const double &lr, const double &h, const std::vector<Variable> &variables,
             const Function &func, const double &convergenceCondition=1e-8, const int &batchSize=BaseOptimizer::DEFAULT_BATCH_SIZE, const double &b1=0.9, const double &b2=0.999, const double &eps=1e-8) : BaseOptimizer(
                lr, h, variables, func, convergenceCondition, batchSize), m_b1(b1), m_b2(b2), m_eps(eps) {
            ms = std::vector<double>(variables.size(), 0.0);
            vs = std::vector<double>(variables.size(), 0.0);
        }

        void updateVariables() override {
            for(unsigned int i = 0; i < m_variables.size(); i++) {
                if (m_gradient[i] == 0.0) {
                    continue;
                }
                ms[i] = m_b1 * ms[i] + (1 - m_b1) * m_gradient[i];
                vs[i] = m_b2 * vs[i] + (1 - m_b2) * m_gradient[i] * m_gradient[i];
                const double _m = ms[i] / (1 - pow(m_b1, m_iter));
                const double _v = vs[i] / (1 - pow(m_b2, m_iter));
                const double newData = m_variables[i].getData() - m_lr * _m / (sqrt(_v) + m_eps);
                m_variables[i].setData(newData);
            }
        }

    };

} // Optimizer


#endif //CONSTRAINED_DIFFERENTIAL_ADAM_H
