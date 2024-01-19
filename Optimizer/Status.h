//
// Created by kango on 2022/11/20.
//

#ifndef AGUVOLUMERENDERING_STATUS_H
#define AGUVOLUMERENDERING_STATUS_H

#include "Variable.h"

namespace AGU::NumCompute::Optimizer {
    class Status {
    private:
        unsigned int m_iter = 0;
        std::vector<Variable> m_variables;
        std::vector<Variable> m_averageVariables;
        std::vector<double> m_gradient;
    public:
        Status(const unsigned int &iter, std::vector<Variable> variables, std::vector<Variable> averageVariables, std::vector<double> gradient)
        : m_iter(iter), m_variables(std::move(variables)), m_averageVariables(std::move(averageVariables)), m_gradient(std::move(gradient)) {}

        [[nodiscard]] unsigned int getIter() const;

        [[nodiscard]] const std::vector<Variable> &getVariables() const;

        [[nodiscard]] const std::vector<Variable> &getAverageVariables() const;

        [[nodiscard]] const std::vector<double> &getGradient() const;
    };

} // Optimizer

#endif //AGUVOLUMERENDERING_STATUS_H
