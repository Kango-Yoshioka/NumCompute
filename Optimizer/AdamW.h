//
// Created by kango on 2023/10/21.
//

#ifndef AGUINVERSEVOLUMERENDERING_2023_ADAMW_H
#define AGUINVERSEVOLUMERENDERING_2023_ADAMW_H


#include <vector>
#include "BaseOptimizer.h"

namespace AGU::NumCompute::Optimizer {
    class AdamW : public BaseOptimizer {
    private:
        double m_b2, m_eps, m_weight_decay;
        std::vector<double> ms, vs;
    public:
        AdamW(const double &lr, const double &h, const std::vector<Variable> &variables,
              const Function &func, const double &convergenceCondition=1e-8, const double &b2=0.999, const double &eps=1e-8, const double &weight_decay=1e-2) : BaseOptimizer(
                lr, h, variables, func, convergenceCondition), m_b2(b2), m_eps(eps), m_weight_decay(weight_decay) {
            ms = std::vector<double>(variables.size(), 0.0);
            vs = std::vector<double>(variables.size(), 0.0);
        }

        void updateVariables() override {
            for(unsigned int i = 0; i < m_variables.size(); i++) {
                m_gradient[i] = m_gradient[i] + m_weight_decay * m_variables[i].getData();
                ms[i] = m_b2 * ms[i] + (1 - m_b2) * m_gradient[i];
                vs[i] = m_b2 * vs[i] + (1 - m_b2) * m_gradient[i] * m_gradient[i];
                const double _m = ms[i] / (1 - pow(m_b2, m_iter));
                const double _v = vs[i] / (1 - pow(m_b2, m_iter));
                const double schedule = 1.0;
                const double newData = m_variables[i].getData() - schedule * (m_lr * _m / (sqrt(_v) + m_eps) + m_weight_decay * m_variables[i].getData());
                m_variables[i].setData(newData);
            }
        }
    };
}
#endif //AGUINVERSEVOLUMERENDERING_2023_ADAMW_H
