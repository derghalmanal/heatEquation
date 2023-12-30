/**
 * @file heatEquationBarre.cpp
 * @author Ania Polidori & Manal Derghal
 * @brief Implémentation de la classe pour l'équation de la chaleur pour un objet à 1 dimension
 * 
 */

#include <vector>
#include <set>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include "heatEquationBarre.h"



heatEquationBarre::heatEquationBarre(int nb_points_discretisation, double t_max, double L, double u0, double f, std::vector<double> lambda, std::vector<double> p, std::vector<double> c, int num_materiau)
    : heatEquationBase<1>(nb_points_discretisation, t_max, L, u0, f, lambda, p, c, num_materiau) {

    for(int i = 0; i < nb_points_discretisation_; i++) {
        x_i_.insert(i * h_);
        t_i_.insert(i * T_);
    }

    A_.assign(nb_points_discretisation_-1, -s_[num_materiau]);
    B_.assign(nb_points_discretisation_-1, 1 + 2 * s_[num_materiau]);
    C_.assign(nb_points_discretisation_-1, -s_[num_materiau]);

    A_.insert(A_.begin(), 0.0);
    B_.insert(B_.begin(), 1.0+s_[num_materiau]);
    C_.insert(C_.end(), 0.0);

    calcul_source_chaleur();

    D_.assign(nb_points_discretisation_, 0.0);
    for (int i = 0; i < nb_points_discretisation_; ++i) {
        if (i != nb_points_discretisation_ - 1) {
            D_[i] = u0_ + T_ * source_chaleur_[i] / (p_[num_materiau] * c_[num_materiau]);
        } else {
            D_[i] = u0_ + T_ * source_chaleur_[i] / (p_[num_materiau] * c_[num_materiau]) + s_[num_materiau] * u0_;
        }
    }
}


void heatEquationBarre::calcul_source_chaleur() {

    source_chaleur_.resize(nb_points_discretisation_);

    for (std::size_t i = 0; i < source_chaleur_.size(); i++) {
        if (i > (L_ / 10) && i < (2 * L_ / 10)) {
            source_chaleur_[i] = std::pow(f_, 2) * t_max_;
        } else if (i > (5 * L_ / 10) && i < (6 * L_ / 10)) {
            source_chaleur_[i] = std::pow(f_, 2) * (3.0 / 4.0);
        } else {
            source_chaleur_[i] = 0;
        }
    }
}


void heatEquationBarre::solve(int num_iterations) {
    for (int iteration = 0; iteration < num_iterations; ++iteration) {
        int n = nb_points_discretisation_ - 1;

        C_[0] /= B_[0];
        D_[0] /= B_[0];

        for (int i = 1; i < n; i++) {
            C_[i] /= B_[i] - A_[i] * C_[i - 1];
            D_[i] = (D_[i] - A_[i] * D_[i - 1]) / (B_[i] - A_[i] * C_[i - 1]);
        }

        D_[n] = (D_[n] - A_[n] * D_[n - 1]) / (B_[n] - A_[n] * C_[n - 1]);

        for (int i = n; i-- > 0;) {
            D_[i] -= C_[i] * D_[i + 1];
        }

    }
}




void heatEquationBarre::printSolution() const {

    std::cout << "solution : ";
    for (std::size_t i = 0; i < D_.size(); ++i) {
        std::cout << D_[i] << " ";
    }
    std::cout << std::endl;

}