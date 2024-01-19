//
// Created by kango on 2022/11/16.
//

#include <iostream>
#include "Differential.h"
#include <vector>
#include <random>
#include <algorithm>

namespace AGU::NumCompute::Differential {

/**
 * 前方差分による微分
 * @param func 関数
 * @param fVariables 変数の値を前方に増加させた値のリスト
 * @param variables 変数値のリスト
 * @param h 変化幅
 * @return 微分値
 */
    double forwardDifference(const Function &func, const std::vector<Variable> &fVariables,
                             const std::vector<Variable> &variables, const double &h) {
        return (func(fVariables) - func(variables)) / h;
    }

/**
 * 中心差分による微分
 * @param func 関数
 * @param fVariables 変数の値を前方に増加させた値のリスト
 * @param bVariables 変数の値を後方に減少させた値のリスト
 * @param h 変化幅
 * @return 微分値
 */
    double centralDifference(const Function &func, const std::vector<Variable> &fVariables,
                             const std::vector<Variable> &bVariables, const double &h) {
        return (func(fVariables) - func(bVariables)) / (2 * h);
    }

/**
 * 後方差分による微分
 * @param func 関数
 * @param variables 変数値のリスト
 * @param bVariables 変数の値を後方に減少させた値のリスト
 * @param h 変化幅
 * @return 微分値
 */
    double backwardDifference(const Function &func, const std::vector<Variable> &variables,
                              const std::vector<Variable> &bVariables, const double &h) {
        return (func(variables) - func(bVariables)) / h;
    }

/**
 * 指定したインデックスの値を前方に増加させた値のリストを返す
 * @param variables Variableインスタンスの配列
 * @param h 変化幅
 * @param forwardIdx 前方に増加させたい値のインデックス
 * @return 指定したインデックスの値を前方に増加させた値のリスト
 */
    std::vector<Variable>
    getForwardVariables(const std::vector<Variable> &variables, const double &h, const int &forwardIdx) {
        std::vector<Variable> fVariables = variables;
        fVariables[forwardIdx].setData(fVariables[forwardIdx].getData() + h);
        return fVariables;
    }

/**
 * 指定したインデックスの値を後方に減少させた値のリストを返す
 * @param variables Variableインスタンスの配列
 * @param h 変化幅
 * @param backwardIdx 後方に減少させたい値のインデックス
 * @return 指定したインデックスの値を後方に減少させた値のリスト
 */
    std::vector<Variable> getBackwardVariables(const std::vector<Variable> &variables, const double &h, const int &backwardIdx) {
        std::vector<Variable> bVariables = variables;
        bVariables[backwardIdx].setData(bVariables[backwardIdx].getData() - h);
        return bVariables;
    }

/**
 * 勾配計算
 * @param func 関数
 * @param variables Variableインスタンスのリスト
 * @return 勾配
 */
    std::vector<double> numericalGradient(const Function &func, const std::vector<Variable> &variables, const double &h) {
        std::vector<double> gradient(variables.size(), 0.0);

        for (int i = 0; i < variables.size(); i++) {
            /// central difference
            std::vector<Variable> fVariables = Differential::getForwardVariables(variables, h, i);
            std::vector<Variable> bVariables = Differential::getBackwardVariables(variables, h, i);
            gradient[i] = Differential::centralDifference(func, fVariables, bVariables, h);
        }
        return gradient;
    }


    /**
     * ランダムにインデックスを取得する
     * @param arraySize 配列のサイズ
     * @param numIndices 取得したいインデックスの数
     * @return ランダムに取得したインデックスのリスト
     */
    std::vector<int> getRandomIndices(int arraySize, int numIndices) {
        // ベクターを初期化し、0からarraySize - 1までのインデックスを格納
        std::vector<int> indices(arraySize);
        for (int i = 0; i < arraySize; ++i) {
            indices[i] = i;
        }

        // ランダムエンジンを初期化
        std::random_device rd;
        std::mt19937 g(rd());

        // ベクターをシャッフル
        std::shuffle(indices.begin(), indices.end(), g);

        // 指定された数のインデックスだけを新しいベクターにコピー
        std::vector<int> result(indices.begin(), indices.begin() + numIndices);

        return result;
    }

/**
 * 勾配計算（変数に制約がついている場合）
 * @param func 関数
 * @param variables Variableインスタンスのリスト
 * @return 勾配
 */
    std::vector<double> numericalGradientWithConstraint(const Function &func, const std::vector<Variable> &variables, const double &h, const int &batchSize) {
        std::vector<double> gradient(variables.size(), 0.0);
        // randomIndicesには，batchSize個のインデックスが格納される
        std::vector<int> randomIndices = getRandomIndices(variables.size(), batchSize);
        for (const auto &i : randomIndices) {
            /// constraint check
            if (variables[i].getData() - h < variables[i].getMin()) {
                /// forward difference
                std::vector<Variable> fVariables = Differential::getForwardVariables(variables, h, i);
                gradient[i] = Differential::forwardDifference(func, fVariables, variables, h);
            } else if (variables[i].getData() + h > variables[i].getMax()) {
                /// backward difference
                std::vector<Variable> bVariables = Differential::getBackwardVariables(variables, h, i);
                gradient[i] = Differential::backwardDifference(func, variables, bVariables, h);
            } else {
                /// central difference
                std::vector<Variable> fVariables = Differential::getForwardVariables(variables, h, i);
                std::vector<Variable> bVariables = Differential::getBackwardVariables(variables, h, i);
                gradient[i] = Differential::centralDifference(func, fVariables, bVariables, h);
            }
        }
        return gradient;
    }
} // Differential