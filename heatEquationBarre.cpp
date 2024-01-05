/**
 * @file heatEquationBarre.cpp
 * @author Ania Polidori & Manal Derghal
 * @brief Implémentation de la classe pour l'équation de la chaleur pour un objet à 1 dimension
 * 
 */
#include "headers/heatEquationBarre.h"



heatEquationBarre::heatEquationBarre(int nb_points_discretisation, double t_max, double L, double u0, double f, std::vector<double> lambda, std::vector<double> p, std::vector<double> c, int num_materiau)
    : heatEquationBase<1>(nb_points_discretisation, t_max, L, u0, f, lambda, p, c, num_materiau) {

    for(int i = 0; i < nb_points_discretisation_+2; i++) {
        x_i_.push_back(i * h_);
        t_i_.push_back(i * T_);
    }

}


double heatEquationBarre::heatSource(double x) {
    if (x >= L_ / 10.0 && x <= 2.0 * L_ / 10.0) {
        return t_max_ * pow(f_,2);
    } else if (x >= 5.0 * L_ / 10.0 && x <= 6.0 * L_ / 10.0) {
        return 3.0 * t_max_ * pow(f_,2)/4.0;
    } else {
        return 0.0;
    }
}



std::vector<double> heatEquationBarre::thomas_algorithm(std::vector<double> A, std::vector<double> B, std::vector<double> C, std::vector<double> D) {


    int n = nb_points_discretisation_ - 1;

    C[0] /= B[0];
    D[0] /= B[0];

    for (int i = 1; i < n; i++) {
        C[i] /= B[i] - A[i] * C[i - 1];
        D[i] = (D[i] - A[i] * D[i - 1]) / (B[i] - A[i] * C[i - 1]);
    }

    D[n] = (D[n] - A[n] * D[n - 1]) / (B[n] - A[n] * C[n - 1]);

    for (int i = n; i-- > 0;) {
         D[i] -= C[i] * D[i + 1];
    }

    return D;

}

std::vector<double> heatEquationBarre::laasonenSolve(double at_time, int num_materiau) {

    A_.assign(nb_points_discretisation_ - 1, -s_[num_materiau]);
    B_.assign(nb_points_discretisation_, 1 + 2 * s_[num_materiau]);
    C_.assign(nb_points_discretisation_ - 1, -s_[num_materiau]);
    D_.assign(nb_points_discretisation_, u0_);
    U_.assign(nb_points_discretisation_, u0_);


    A_.insert(A_.begin(), 0.0);
    C_.insert(C_.end(), 0.0);

    if (at_time != 0) {
        for (double i = 0; i < at_time; i+=T_) {

            D_[0] = u0_ + (s_[num_materiau] * u0_) + (T_ * heatSource(x_i_[0]) / (p_[num_materiau] * c_[num_materiau]));

            for (int j = 1; j < nb_points_discretisation_-1; j++) {
                D_[j] = U_[j] + (T_ * heatSource(x_i_[j]) / (p_[num_materiau] * c_[num_materiau]));
            }
            D_[nb_points_discretisation_ - 1] = u0_ + (s_[num_materiau] * u0_) + (T_ * heatSource(x_i_[nb_points_discretisation_ - 1]) / (p_[num_materiau] * c_[num_materiau]));

            U_ = thomas_algorithm(A_, B_, C_, D_);
        }
    }

    A_.clear();
    B_.clear();
    C_.clear();

    return U_;
}



std::vector<double> heatEquationBarre::getTi() const {
    return t_i_;
}