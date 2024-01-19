//
// Created by kango on 2022/11/16.
//

#include <iostream>
#include <algorithm>
#include "Variable.h"

namespace AGU::NumCompute {
    Variable::Variable(const double &_data, const double &_min, const double &_max) {
        if (_min > _max) {
            std::cerr << "(in Variable constructor) _min is greater than _max. invalid error.csv" << std::endl;
            exit(EXIT_FAILURE);
        }
        m_min = _min;
        m_max = _max;

        if (!isWithinRange(_data)) {
            std::cerr << "(in Variable constructor) initial _data is out of range of constraint. invalid error.csv"
                      << std::endl;
            exit(EXIT_FAILURE);
        }
        m_data = _data;
    };

    double Variable::getData() const {
        return m_data;
    }

    double Variable::getMax() const {
        return m_max;
    }

    double Variable::getMin() const {
        return m_min;
    }

    void Variable::setData(const double &_data) {
        setDataWithinRange(_data);
    }

    void Variable::setMax(const double &_max) {
        m_max = _max;
    }

    void Variable::setMin(const double &_min) {
        m_min = _min;
    }

/**
 * dataの値が制約の範囲外にある場合clampする
 */
    void Variable::setDataWithinRange(const double &_data) {
        m_data = std::clamp(_data, m_min, m_max);
    }

/**
 * 引数の値がVariableインスタンスの制約の範囲内にあるかを真偽値で返す
 * @param value 値
 * @return 真偽値
 */
    bool Variable::isWithinRange(const double &value) const {
        return value >= m_min && m_max >= value;
    }

/**
 * Variableリストのvalのみのリストを返す
 * @param variables
 * @return values list in variables
 */
    std::vector<double> Variable::getVariableValues(const std::vector<Variable> &variables) {
        std::vector<double> values(variables.size(), 0.0);
        for (int i = 0; i < variables.size(); i++) {
            values[i] = variables[i].getData();
        }
        return values;
    }
}
