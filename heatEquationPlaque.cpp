#include "headers/matrix.h"
#include "headers/heatEquationPlaque.h"

heatEquationPlaque::heatEquationPlaque(int nb_points_discretisation, double t_max, double L, double u0, double f, std::vector<double> lambda, std::vector<double> p, std::vector<double> c, int num_materiau)
    : heatEquationBase<2>(nb_points_discretisation, t_max, L, u0, f, lambda, p, c, num_materiau) {

    for(int i = 0; i < nb_points_discretisation_+2; i++) {
        x_i_.push_back(i * h_);
        y_i_.push_back(i * h_);
        t_i_.push_back(i * T_);
    }

    U_ = Matrix(nb_points_discretisation_, nb_points_discretisation_);

}

// Heat source function
double heatEquationPlaque::heatSource(double x, double y) {
    double L6 = L_ / 6.0;
    double twoL6 = 2.0 * L_ / 6.0;
    double fourL6 = 4.0 * L_ / 6.0;
    double fiveL6 = 5.0 * L_ / 6.0;

    if ((x >= L6 && x <= twoL6 && y >= L6 && y <= twoL6) ||
        (x >= fourL6 && x <= fiveL6 && y >= L6 && y <= twoL6) ||
        (x >= L6 && x <= twoL6 && y >= fourL6 && y <= fiveL6) ||
        (x >= fourL6 && x <= fiveL6 && y >= fourL6 && y <= fiveL6)) {
        return t_max_ * pow(f_, 2);
    } else {
        return 0.0;
    }
}




Matrix heatEquationPlaque::tridiagonal_form(const std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& c) {
    int n = b.size();

    Matrix X(n, n);
    for (int i = 0; i < n; ++i) {
        X(i, i) = b[i];
        if (i < n - 1) {
            X(i, i + 1) = c[i];
            X(i + 1, i) = a[i];
        }
    }

    return X;
}


Matrix heatEquationPlaque::block_thomas_algorithm(std::vector<Matrix> B, Matrix D) {
    int k = B.size();  // number of blocks
    int n = B[0].rows();  // size of blocks
    std::vector<Matrix> W(k, Matrix(n, n));
    Matrix X(k, n);

    for (int i = 1; i < k; ++i) {
        W[i] = B[i - 1].inverse();
        B[i] = B[i] - W[i];
        D.block_assign(i, 0, 1, n, D.block(i, 0, 1, n) - D.block(i - 1, 0, 1, n) * W[i]);
    }

    X.block_assign(k - 1, 0, 1, n,(B[k - 1].inverse() * D.block(k - 1, 0, 1, n).transpose()).transpose());
    for (int i = k - 2; i >= 0; --i) {
        X.block_assign(i, 0, 1, n,(B[i].inverse() * (D.block(i, 0, 1, n) - X.block(i + 1, 0, 1, n)).transpose()).transpose());
    }

    return X;
}



Matrix heatEquationPlaque::laasonenSolve(double at_time, int num_materiau) {
    int n = nb_points_discretisation_;
    double s = s_[num_materiau];

    std::vector<double> a(n - 1, -s);
    std::vector<double> b(n, 1.0 + (4.0 * s));
    std::vector<double> c(n - 1, -s);

    std::vector<Matrix> B;
    for (int i = 0; i < n; ++i) {
        Matrix Btemp = tridiagonal_form(a, b, c) / (-s);
        B.push_back(Btemp);
    }

    Matrix D(n, n);

    // Initialize D with u0_
    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
            D(j, k) = u0_;
            U_(j, k) = u0_;
        }
    }

    if (at_time != 0.0) {
        for (double t = 0.0; t <= at_time; t += T_) {
            for (int j = 0; j < n; ++j) {
                D(0, j) = u0_ + (T_ * heatSource(x_i_[0], y_i_[j])) / (c_[num_materiau] * p_[num_materiau]) + s * u0_;
                D(n - 1, j) = u0_ + (T_ * heatSource(x_i_[n - 1], y_i_[j])) / (c_[num_materiau] * p_[num_materiau]) + s * u0_;
            }

            for (int i = 1; i < n - 1; ++i) {
                D(i, 0) = u0_ + (T_ * heatSource(x_i_[i], y_i_[0])) / (c_[num_materiau] * p_[num_materiau]) + s * u0_;
                D(i, n - 1) = u0_ + (T_ * heatSource(x_i_[i], y_i_[n - 1])) / (c_[num_materiau] * p_[num_materiau]) + s * u0_;

                for (int j = 1; j < n - 1; ++j) {
                    D(i, j) = U_(i, j) + (T_ * heatSource(x_i_[i], y_i_[j])) / (c_[num_materiau] * p_[num_materiau]);
                }
            }

            D(0, 0) = u0_ + (T_ * heatSource(x_i_[0], y_i_[0])) / (c_[num_materiau] * p_[num_materiau]) + 2 * s * u0_;
            D(0, n - 1) = u0_ + (T_ * heatSource(x_i_[0], y_i_[n - 1])) / (c_[num_materiau] * p_[num_materiau]) + 2 * s * u0_;
            D(n - 1, 0) = u0_ + (T_ * heatSource(x_i_[n - 1], y_i_[0])) / (c_[num_materiau] * p_[num_materiau]) + 2 * s * u0_;
            D(n - 1, n - 1) = u0_ + (T_ * heatSource(x_i_[n - 1], y_i_[n - 1])) / (c_[num_materiau] * p_[num_materiau]) + 2 * s * u0_;

            U_ = block_thomas_algorithm(B, D / (-s));
        }
    }

    return U_;
}