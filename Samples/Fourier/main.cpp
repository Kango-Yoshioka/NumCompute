//
// Created by kango on 2024/01/19.
//

#include <iostream>
#include <fstream>

#include "NumCompute.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/** targetをstd::functionで表現 */
std::function<double(const double &)> target = [](const double &x) {
    if (0.25 <= x && x < 0.75) {
        return 1.0;
    } else {
        return 0.0;
    }
};


double fourier(const double &x, const int &n, const double &a0, const std::vector<double> &a,
               const std::vector<double> &b) {
    double sum = a0;
    for (int i = 0; i < n; ++i) {
        sum += a[i] * std::cos((i + 1) * M_PI * x) + b[i] * std::sin((i + 1) * M_PI * x);
    }
    return sum;
}

void optimize_fourier(const int &n, const double &lr, const double &h, const double &convergenceCondition){
    std::vector<AGU::NumCompute::Variable> variables;
    variables.emplace_back(0.0);
    for (int i = 0; i < n; ++i) {
        variables.emplace_back(0.0);
        variables.emplace_back(0.0);
    }

    AGU::NumCompute::Function func = [&](const std::vector<AGU::NumCompute::Variable> &variables) {
        double sum = 0.0;
        const double a0 = variables[0].getData();
        std::vector<double> a;
        std::vector<double> b;
        for(int i = 0; i < n; ++i) {
            a.emplace_back(variables[i+1].getData());
            b.emplace_back(variables[i+n+1].getData());
        }

        for (double x = 0.0; x < 1.0; x += 0.01) {
            sum += std::pow(target(x) - fourier(x, n, a0, a, b), 2);
        }

        return sum;
    };

    AGU::NumCompute::Optimizer::Adam optimizer(lr, h, variables, func, convergenceCondition);
    const auto result = optimizer.optimize();

    std::ofstream ofs("result.csv");
    ofs << "x, target, fourier" << std::endl;

    std::cout << "result:\t" << result.getIter() << "steps" << std::endl;
    for(const auto &v : result.getVariables()) {
        std::cout << v.getData() << ", ";
    }
    std::cout << std::endl;

    const double a0 = result.getVariables()[0].getData();
    std::vector<double> a;
    std::vector<double> b;
    for(int i = 0; i < n; ++i) {
        a.emplace_back(result.getVariables()[i+1].getData());
        b.emplace_back(result.getVariables()[i+n+1].getData());
    }

    for(double x = 0.0; x < 1.0; x += 0.01) {
        ofs << x << ", " << target(x) << ", " << fourier(x, n, a0, a, b) << std::endl;
    }

    ofs.close();
}

int main() {
    optimize_fourier(20, 0.01, 0.01, 1e-2);
    return 0;
}
