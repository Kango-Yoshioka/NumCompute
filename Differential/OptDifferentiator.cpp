//
// Created by kango on 2022/11/17.
//

#include <utility>

#include "OptDifferentiator.h"
#include "Differential.h"

namespace AGU::NumCompute::Differential {

/// For OptDifferentiator
    OptDifferentiator::OptDifferentiator() = default;

    OptDifferentiator::OptDifferentiator(const double &h, const Function &func) : m_h(h), m_func(func) {}

/**
 * 勾配計算（変数に制約がついている場合）
 * @param variables Variableインスタンスのリスト
 * @return 勾配
 */
    std::vector<double> OptDifferentiator::numericalGradientWithConstraint(const std::vector<Variable> &variables, const int &batchSize) {
        return Differential::numericalGradientWithConstraint(m_func, variables, m_h, batchSize);
    }

    double OptDifferentiator::getH() const {
        return m_h;
    }

    const Function &OptDifferentiator::getFunc() const {
        return m_func;
    }

} // Differential
