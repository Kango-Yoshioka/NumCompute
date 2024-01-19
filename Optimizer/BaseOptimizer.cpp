//
// Created by kango on 2022/11/16.
//

#include <cmath>
#include <iostream>
#include "BaseOptimizer.h"
#include "Status.h"

namespace AGU::NumCompute::Optimizer {
    BaseOptimizer::BaseOptimizer(const double &lr, const double &h, const std::vector<Variable> &variables,
                                 const Function &func, const double &convergenceCondition, const int &batchSize) : m_lr(lr), m_variables(variables),
                                                                                             m_convergenceCondition(convergenceCondition){
        m_iter = 0;
        m_averageVariables = variables;
        m_optDifferentiator = Differential::OptDifferentiator(h, func);
        m_gradient = std::vector<double>(variables.size(), 0.0);
        if(batchSize == DEFAULT_BATCH_SIZE) {
            m_batchSize = variables.size();
        } else {
            m_batchSize = batchSize;
        }
    }

    double BaseOptimizer::getH() const {
        return m_optDifferentiator.getH();
    }

    unsigned int BaseOptimizer::getIter() const {
        return m_iter;
    }

    std::vector<Variable> BaseOptimizer::getVariables() const {
        return m_variables;
    }

    const std::vector<Variable> &BaseOptimizer::getAverageVariables() const {
        return m_averageVariables;
    }

    const std::vector<double> &BaseOptimizer::getGradient() const {
        return m_gradient;
    }

    Optimizer::Status BaseOptimizer::getStatus() const {
        return Optimizer::Status{m_iter, m_variables, m_averageVariables, m_gradient};
    }

    void BaseOptimizer::calcGradient() {
        m_gradient = m_optDifferentiator.numericalGradientWithConstraint(m_variables, m_batchSize);
    }

    void BaseOptimizer::incrementIter(unsigned int val) {
        BaseOptimizer::m_iter += val;
    }

    std::vector<double> BaseOptimizer::step() {
        incrementIter();
        updateVariables();

        std::vector<double> relativeRateOfChanges(m_averageVariables.size(), DBL_MAX);
        for(int i = 0; i < m_averageVariables.size(); i++) {
            const double beforeAverageData = m_averageVariables[i].getData();
            double afterAverageData;
            const int shiftSize = 20;
            const double alpha = 2.0 / (shiftSize + 1);
            if(m_iter < shiftSize) {
              afterAverageData = (m_iter * m_averageVariables[i].getData() + m_variables[i].getData()) / (getIter() + 1);
            } else {
              afterAverageData = (1 - alpha) * beforeAverageData + alpha * m_variables[i].getData();
            }
            m_averageVariables[i].setData(afterAverageData);
            relativeRateOfChanges[i] = fabs(afterAverageData - beforeAverageData) / fabs(beforeAverageData);
        }
        return relativeRateOfChanges;
    }

    /**
     * 平均値の相対変化率が収束条件を下回っているか調べる
     * @param relativeRateOfChanges 相対変化率のリスト
     * @return bool
     */
    bool BaseOptimizer::isConverge(const std::vector<double> &relativeRateOfChanges) const {
        for(double relativeRateOfChange : relativeRateOfChanges) {
            if(relativeRateOfChange >= m_convergenceCondition) return false;
        }
        return true;
    }

    Optimizer::Status BaseOptimizer::optimize(const std::function<void(const Optimizer::Status&)>& displayFunc) {
        /// m_averageVariables reInit;
        m_averageVariables = m_variables;
        std::vector<double> relativeRateOfChanges(m_averageVariables.size(), DBL_MAX);
        while(!BaseOptimizer::isConverge(relativeRateOfChanges)) {
            Optimizer::Status status(m_iter, m_variables, m_averageVariables, m_gradient);
            displayFunc(status);
            calcGradient();
            relativeRateOfChanges = step();
        }
        const auto result = Status(m_iter, m_variables, m_averageVariables, m_gradient);
        displayFunc(result);
        std::cout << "\n\n-- Optimize finished" << std::endl;
        return Status(m_iter, m_variables, m_averageVariables, m_gradient);
    }

} // Optimizer