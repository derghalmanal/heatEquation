#include <vector>
#include <set>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include "heatEquationBarre.h"



heatEquationBarre::heatEquationBarre(int nb_points_discretisation, double t_max, double L, double u0, double f, std::vector<double> lambda, std::vector<double> p, std::vector<double> c)
    : heatEquationBase<1>(nb_points_discretisation, t_max, L, u0, f, lambda, p, c) {

        for(int i = 0; i < nb_points_discretisation_; i++){
            x_i_.insert(i * h_);
            t_i_.insert(i * T_);
        }
}





void heatEquationBarre::initialize_matrice(int num_materiau) {
    int n = source_chaleur_.size();
    double s = s_[num_materiau];
    double rho = p_[num_materiau];
    double c = c_[num_materiau]; 

    // Initialize the tridiagonal coefficients
    A_.resize(n, -s);
    B_.resize(n, 1 + 2 * s);
    C_.resize(n, -s);

    A_[0] = 0.0;
    B_[0] = 1 + s;
    C_[n - 1] = 0.0;

    // Set the initial conditions for the solution vector U_
    U_.resize(n, 0.0); // Assuming you have a function for initial conditions

    // (You may need to adjust these based on your problem)
    for (int i = 0; i < n; ++i) {
        U_[i] = u0_;  // You need to define this function based on your problem
    }

    // Initialize the right-hand side vector D_
    D_.resize(n, 0.0);
    for (int i = 0; i < n; ++i) {
        D_[i] = (T_ * source_chaleur_[i] / (rho * c)) + U_[i];
    }
    D_[n - 1] += s * U_[0];


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


void heatEquationBarre::solve() {
    int n = nb_points_discretisation_ - 1;

    // Forward elimination
    for (int i = 1; i < n; i++) {
        C_[i] /= B_[i] - A_[i] * C_[i - 1];
        D_[i] = (D_[i] - A_[i] * D_[i - 1]) / (B_[i] - A_[i] * C_[i - 1]);
    }

    D_[n] = (D_[n] - A_[n] * D_[n - 1]) / (B_[n] - A_[n] * C_[n - 1]);

    // Backwards substitution
    U_[n] = D_[n];
    for (int i = n - 1; i >= 0; i--) {
        U_[i] = D_[i] - C_[i] * U_[i + 1];
    }
}


std::vector<double> heatEquationBarre::get_U() const {
    return U_;
}
