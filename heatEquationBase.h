#ifndef HEATEQUATIONBASE_H
#define HEATEQUATIONBASE_H

#include <vector>
#include <cmath>


/**
 * @class heatEquationBase
 * @brief classe de base pour les équations de la chaleur
 * elle gère les informations qu'on retrouvera pour l'équation de la chaleur peu importe le cas
 * 
 */
template<std::size_t d>
class heatEquationBase {

    protected: 
        int nb_points_discretisation_ ; /*!<Nombre de points de discrétisation en espace et en temps*/
        double h_; /*!<pas de discrétisation en espace*/
        double T_; /*!<pas de discrétisation en temps*/
        double t_max_ ; /*!<temps maximum*/
        double L_ ; /*!<longueur de la barre*/
        double u0_ ; /*!<état initial de la température (quand temps = 0)*/
        double f_ ; /*!<source de chaleur*/

        std::vector<double> lambda_ ; /*!<conductivité thermique du matériau*/
        std::vector<double> p_; /*!<masse volumique du matériau*/
        std::vector<double> c_; /*!<chaleur massique du matériau*/
        std::vector<double> s_; /*!<paramètre de stabilité*/
        int num_materiau_ ; /*!<numéro du matériau*/
    public: 


    heatEquationBase(int nb_points_discretisation, double t_max, double L, double u0, double f,
                    std::vector<double> lambda, std::vector<double> p, std::vector<double> c, int num_materiau)
        : nb_points_discretisation_(nb_points_discretisation), t_max_(t_max), L_(L), lambda_(lambda), p_(p), c_(c), num_materiau_(num_materiau) {

        u0_ = u0 + 273.15;
        f_ = f + 273.15;
        h_ = L_ / (nb_points_discretisation_ + 1);
        T_ = t_max_ / (nb_points_discretisation_ + 1);

        //verifie que p[i] != 0, c[i] != 0
        for (int i = 0; i < nb_points_discretisation_; i++) {
            if (p_[i] == 0 || c_[i] == 0) {
                throw "p[i] and c[i] must be non-zero";
            }
        }

        s_.resize(nb_points_discretisation_);
        for (int i = 0; i < nb_points_discretisation_; i++) {
            s_[i] = (lambda_[i] * T_) / (p_[i] * c_[i] * std::pow(h_, 2));
        }

    }

};

#endif