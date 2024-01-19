//
// Created by kango on 2022/11/16.
//

#ifndef CONSTRAINED_DIFFERENTIAL_BASEOPTIMIZER_H
#define CONSTRAINED_DIFFERENTIAL_BASEOPTIMIZER_H

#include "Variable.h"
#include "Function.h"
#include "OptDifferentiator.h"
#include "Status.h"

namespace AGU::NumCompute::Optimizer {

    class BaseOptimizer {
    protected:
        unsigned int m_iter; // 累積のステップ数(0スタート)
        int m_batchSize;
        double m_lr, m_convergenceCondition;
        std::vector<Variable> m_variables;
        std::vector<Variable> m_averageVariables;
        std::vector<double> m_gradient;
        Differential::OptDifferentiator m_optDifferentiator;
        static const int DEFAULT_BATCH_SIZE = -1;
    public:
        BaseOptimizer(const double &lr, const double &h, const std::vector<Variable> &variables, const Function &func, const double &convergenceCondition = 1e-8, const int &batchSize = DEFAULT_BATCH_SIZE);

        [[nodiscard]] double getH() const;

        [[nodiscard]] unsigned int getIter() const;

        [[nodiscard]] std::vector<Variable> getVariables() const;

        [[nodiscard]] const std::vector<Variable> &getAverageVariables() const;

        [[nodiscard]] const std::vector<double> &getGradient() const;

        [[nodiscard]] Optimizer::Status getStatus() const;

        void calcGradient();

        void incrementIter(unsigned int val = 1);

        /**
 * 純粋仮想関数\n
 * 継承先のクラスで必ず実装する\n
 * 最適化手法に基づき、変数を更新する
 */
        std::vector<double> step();

        virtual void updateVariables() = 0;

        [[nodiscard]] bool isConverge(const std::vector<double> &relativeRateOfChanges) const;

        Optimizer::Status optimize(const std::function<void(const Optimizer::Status &)> &displayFunc = [](
                const Optimizer::Status &) -> void {});
    };

} // Optimizer

#endif //CONSTRAINED_DIFFERENTIAL_BASEOPTIMIZER_H
