#ifndef HEATEQUATIONBARRE_HPP
#define HEATEQUATIONBARRE_HPP

#include <vector>
#include <set>
#include "heatEquationBase.h"



/**
 * @class heatEquationBarre
 * @brief classe qui hérite de heatEquationBase
 * pour l'équation de la chaleur pour une barre (objet à 1 dimension)
 * 
 */
class heatEquationBarre : public heatEquationBase<1> {


    private: 
        std::set<double> x_i_ ; /*!<points du maillage x_i */
        std::set<double> t_i_ ; /*!<points du maillage t_i */
        std::vector<double> source_chaleur_ ; /*!<source de chaleur F , plusieurs valeurs de F en fonction de x donc F même taille que x */
        std::vector<double> A_; /*!<vecteur A de la matrice tridiagonale*/
        std::vector<double> B_; /*!<vecteur B de la matrice tridiagonale*/
        std::vector<double> C_; /*!<vecteur C de la matrice tridiagonale*/
        std::vector<double> D_; /*!<vecteur D de la matrice tridiagonale*/
            // |b0 c0 0 ||u0| |d0|
            // |a1 b1 c1||u1|=|d1|
            // |0  a2 b2||u2| |d2|




    public: 


        heatEquationBarre(int nb_points_discretisation, double t_max, double L, double u0, double f, std::vector<double> lambda, std::vector<double> p , std::vector<double> c, int num_materiau);

        /**
         * @brief Fonction de calcul d'ajouts de chaleur en fonction d'une valeur f
         * 
         * @param f : une valeur de température
         */
        void calcul_source_chaleur();

        void solve(int num_iterations);

        void printSolution() const;

        std::vector<double> getSolution() const;
};

#endif