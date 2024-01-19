//
// Created by kango on 2022/11/20.
//

#include "Status.h"

namespace AGU::NumCompute::Optimizer {
    unsigned int Status::getIter() const {
        return m_iter;
    }

    const std::vector<Variable> &Status::getVariables() const {
        return m_variables;
    }

    const std::vector<Variable> &Status::getAverageVariables() const {
        return m_averageVariables;
    }

    const std::vector<double> &Status::getGradient() const {
        return m_gradient;
    }
} // Optimizer