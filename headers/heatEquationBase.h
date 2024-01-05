#ifndef HEATEQUATIONBASE_H
#define HEATEQUATIONBASE_H

#include <vector>
#include <cmath>


/**
 * \class {heatEquationBase}
 * \brief {classe de base pour les équations de la chaleur
 * elle gère les informations qu'on retrouvera pour l'équation de la chaleur peu importe le cas}
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
        std::vector<double> s_; /*!<paramètre de stabilité, s = lambda * T / (p * c * h^2)*/
        int num_materiau_ ; /*!<numéro du matériau sur lequeal on travaille, donc 0 c'est le premier matériau, 1 le deuxième etc...*/

    public: 

    /**
     * \brief Constructeur de la classe heatEquationBase
     * 
     * \param nb_points_discretisation nombre de points de discrétisation en espace et en temps
     * \param t_max temps maximum
     * \param L longueur de la barre
     * \param u0 état initial de la température (quand temps = 0)
     * \param f source de chaleur
     * \param lambda conductivité thermique du matériau
     * \param p masse volumique du matériau
     * \param c chaleur massique du matériau
     * \param num_materiau numéro du matériau sur lequeal on travaille, donc 0 c'est le premier matériau, 1 le deuxième etc...
     */

    heatEquationBase(int nb_points_discretisation, double t_max, double L, double u0, double f,
                    std::vector<double> lambda, std::vector<double> p, std::vector<double> c, int num_materiau)
        : nb_points_discretisation_(nb_points_discretisation), t_max_(t_max), L_(L), lambda_(lambda), p_(p), c_(c), num_materiau_(num_materiau) {

        u0_ = u0 + 273.15;
        f_ = f + 273.15;
        h_ = L_ / (nb_points_discretisation_ + 1);
        T_ = t_max_ / (nb_points_discretisation_ + 1);

        s_.resize(lambda_.size());
        for (size_t i = 0; i < lambda.size(); i++) {
            s_[i] = (lambda_[i] * T_) / (p_[i] * c_[i] * std::pow(h_, 2));
        }
    }


};

#endif