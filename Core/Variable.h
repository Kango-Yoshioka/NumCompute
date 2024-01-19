//
// Created by kango on 2022/11/16.
//

#ifndef CONSTRAINED_DIFFERENTIAL_VARIABLE_H
#define CONSTRAINED_DIFFERENTIAL_VARIABLE_H

#include <cfloat>
#include <vector>

namespace AGU::NumCompute {
    class Variable {
    private:
        double m_data = 0.0;
        double m_min = -DBL_MAX;
        double m_max = DBL_MAX;
    public:
        explicit Variable(const double &_data, const double &_min = -DBL_MAX, const double &_max = DBL_MAX);

        Variable() = default;

        [[nodiscard]] double getData() const;

        [[nodiscard]] double getMax() const;

        [[nodiscard]] double getMin() const;

        void setData(const double &_data);

        void setMax(const double &_max);

        void setMin(const double &_min);

        void setDataWithinRange(const double &_data);

        [[nodiscard]] bool isWithinRange(const double &value) const;

        static std::vector<double> getVariableValues(const std::vector<Variable> &variables);
    };
}

#endif //CONSTRAINED_DIFFERENTIAL_VARIABLE_H
