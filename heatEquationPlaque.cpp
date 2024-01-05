#include "headers/matrix.h"
#include "headers/heatEquationPlaque.h"

heatEquationPlaque::heatEquationPlaque(int nb_points_discretisation, double t_max, double L, double u0, double f, std::vector<double> lambda, std::vector<double> p, std::vector<double> c, int num_materiau)
    : heatEquationBase<2>(nb_points_discretisation, t_max, L, u0, f, lambda, p, c, num_materiau) {

    for(int i = 0; i < nb_points_discretisation_+2; i++) {
        x_i_.push_back(i * h_);
        y_i_.push_back(i * h_);
        t_i_.push_back(i * T_);
    }

    U_ = std::vector<Matrix>(nb_points_discretisation_, Matrix(nb_points_discretisation_, 1));
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


std::vector<Matrix> heatEquationPlaque::solve_tridiagonal(std::vector<Matrix> const & lower_diagonal,
                                    std::vector<Matrix> const & diagonal,
                                    std::vector<Matrix> const & upper_diagonal,
                                    std::vector<Matrix> const & rhs)
{

            int n = nb_points_discretisation_;

            std::vector<Matrix> upper_diagonal_prime;
            std::vector<Matrix> rhs_prime;
            std::vector<Matrix> solution;

            upper_diagonal_prime.resize(n - 1);
            rhs_prime.resize(n);
            solution.resize(n);

            for(int i = 0; i < n - 1; i++){
                if(i == 0){
                    // C_0' = B_0.inv() * C_0
                    upper_diagonal_prime[0] = diagonal[0].inverse() * upper_diagonal[0];
                }
                else{
                    // C_i' = (B_i - A_{i-1} * C_{i-1}').inv() * C[i]
                    upper_diagonal_prime[i] = (diagonal[i] - lower_diagonal[i - 1] * upper_diagonal_prime[i - 1]).inverse()
                                              * upper_diagonal[i];
                }
            }


            // D_0' = B_0.inv() * D_0
            rhs_prime[0] = diagonal[0].inverse() * rhs[0];
            for(int i = 1; i < n; i++){
                // D_i' = (B_i.inv() - A_{i-1} * C_{i-1}').inv() * (D_i - A_{i-1} * D_{i-1}')
                rhs_prime[i] = (diagonal[i] - lower_diagonal[i - 1] * upper_diagonal_prime[i - 1]).inverse()
                               * (rhs[i] - lower_diagonal[i - 1] * rhs_prime[i - 1]);
            }

            // X_{n-1} = D_{n-1}'
            solution[solution.size() - 1] = rhs_prime.at(diagonal.size()-1);
            for(int i = n - 2; i >= 0; i--){
                // X_i = D_{n-1}' - C_i' * X_{i+1}
                solution[i] = rhs_prime[i] - upper_diagonal_prime[i] * solution[i+1];
            }

            return solution;
}



std::vector<Matrix> heatEquationPlaque::laasonenSolve(double at_time, int num_materiau) {
    int n = nb_points_discretisation_;
    double s = s_[num_materiau];

    std::vector<double> a(n - 1, -s);
    std::vector<double> b(n, 1.0 + (4.0 * s));
    std::vector<double> c(n - 1, -s);

    std::vector<Matrix> B , Lower, Upper;
    
    for (int i = 0; i < n; ++i) {
        Matrix Btemp = tridiagonal_form(a, b, c);
        Matrix Lower_temp = -s*Matrix::createIdentity(n);
        B.push_back(Btemp);
        Lower.push_back(Lower_temp);
        Upper.push_back(Lower_temp);
    }

    std::vector<Matrix> D = std::vector<Matrix>(n, Matrix(n, 1));

    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
            D[j](k, 0) = u0_;
            U_[j](k, 0) = u0_;
        }
    }

    if (at_time != 0.0) {
        for (double t = 0.0; t <= at_time; t += T_) {
            for (int j = 0; j < n; ++j) {
                D[0](j,0) = u0_ + (T_ * heatSource(x_i_[0], y_i_[j])) / (c_[num_materiau] * p_[num_materiau]) + s * u0_;
                D[n-1](j,0) = u0_ + (T_ * heatSource(x_i_[n - 1], y_i_[j])) / (c_[num_materiau] * p_[num_materiau]) + s * u0_;
            }

            for (int i = 1; i < n - 1; ++i) {
                D[i](0, 0) = u0_ + (T_ * heatSource(x_i_[i], y_i_[0])) / (c_[num_materiau] * p_[num_materiau]) + s * u0_;
                D[i](n - 1,0) = u0_ + (T_ * heatSource(x_i_[i], y_i_[n - 1])) / (c_[num_materiau] * p_[num_materiau]) + s * u0_;

                for (int j = 1; j < n - 1; ++j) {
                    D[i](j,0) = U_[i](j, 0) + (T_ * heatSource(x_i_[i], y_i_[j])) / (c_[num_materiau] * p_[num_materiau]);
                }
            }

            D[0](0, 0) = u0_ + (T_ * heatSource(x_i_[0], y_i_[0])) / (c_[num_materiau] * p_[num_materiau]) + 2 * s * u0_;
            D[0](n - 1,0) = u0_ + (T_ * heatSource(x_i_[0], y_i_[n - 1])) / (c_[num_materiau] * p_[num_materiau]) + 2 * s * u0_;
            D[n-1](0, 0) = u0_ + (T_ * heatSource(x_i_[n - 1], y_i_[0])) / (c_[num_materiau] * p_[num_materiau]) + 2 * s * u0_;
            D[n-1](n - 1, 0) = u0_ + (T_ * heatSource(x_i_[n - 1], y_i_[n - 1])) / (c_[num_materiau] * p_[num_materiau]) + 2 * s * u0_;

            U_ = solve_tridiagonal(Lower, B, Upper, D);
        }
    }
    return U_;
}