//
// Created by kango on 2023/10/21.
//

#ifndef AGUINVERSEVOLUMERENDERING_2023_RADAM_H
#define AGUINVERSEVOLUMERENDERING_2023_RADAM_H


#include <vector>
#include <cmath>
#include "Variable.h"
#include "Function.h"
#include "BaseOptimizer.h"

namespace AGU::NumCompute::Optimizer {

    class RAdam : public BaseOptimizer{
    private:
        double m_b1, m_b2, m_eps, m_weight_decay, m_rho_inf;
        std::vector<double> ms, vs;
    public:
        RAdam(const double &lr, const double &h, const std::vector<Variable> &variables,
              const Function &func, const double &convergenceCondition=1e-8, const double &b1=0.9, const double &b2=0.999, const double &eps=1e-8, const double &weight_decay=0.0) : BaseOptimizer(
                lr, h, variables, func, convergenceCondition), m_b1(b1), m_b2(b2), m_eps(eps), m_weight_decay(weight_decay) {
            ms = std::vector<double>(variables.size(), 0.0);
            vs = std::vector<double>(variables.size(), 0.0);
            m_rho_inf = 2.0 / (1.0 - m_b2) - 1.0;
        }

        void updateVariables() override {
            for(unsigned int i = 0; i < m_variables.size(); i++) {
                if(m_weight_decay != 0.0) {
                    m_gradient[i] = m_gradient[i] + m_weight_decay * m_variables[i].getData();
                }
                ms[i] = m_b1 * ms[i] + (1 - m_b1) * m_gradient[i];
                vs[i] = m_b2 * vs[i] + (1 - m_b2) * m_gradient[i] * m_gradient[i];
                const double _m = ms[i] / (1 - pow(m_b1, m_iter));
                const double rho = m_rho_inf - 2 * getIter() * pow(m_b2, getIter()) / (1 - pow(m_b2, getIter()));
                if(rho > 5.0) {
                    const double l = sqrt((1 - pow(m_b2, getIter())) / (sqrt(vs[i]) + m_eps));
                    const double r = sqrt((rho - 4) * (rho - 2) * m_rho_inf / ((m_rho_inf - 4) * (m_rho_inf - 2) * rho));
                    const double newData = m_variables[i].getData() - m_lr * _m * r * l;
                    m_variables[i].setData(newData);
                } else {
                    const double newData = m_variables[i].getData() - m_lr * _m;
                    m_variables[i].setData(newData);
                }
            }
        }
    };

} // Optimizer


#endif //AGUINVERSEVOLUMERENDERING_2023_RADAM_H
