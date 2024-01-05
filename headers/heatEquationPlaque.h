#ifndef HEATEQUATIONPLAQUE_HPP
#define HEATEQUATIONPLAQUE_HPP

#include <vector>

#include "heatEquationBase.h"
#include "matrix.h"


/**
 * \class {heatEquationPlaque}
 * \brief {classe qui hérite de heatEquationBase pour l'équation de la chaleur pour une plaque (objet à 2 dimensions)}
 * 
 */
class heatEquationPlaque : public heatEquationBase<2> {

    private :

        std::vector<double> x_i_ ; /*!<points du maillage x_i */
        std::vector<double> y_i_ ; /*!<points du maillage y_i */
        std::vector<double> t_i_ ; /*!<points du maillage t_i */
        std::vector<double> source_chaleur_ ; /*!<source de chaleur F , plusieurs valeurs de F en fonction de x donc F même taille que x */
        Matrix U_; /*!<matrice U qui contient les valeurs de la solution à chaque pas de temps */
            // |B C 0||u1|=|d1|
            // |A B C||u2| |d2|
            // |0 A B||u3| |d3|

    public:

        /**
         * \brief Constructeur de la classe heatEquationPlaque
         * \param nb_points_discretisation : nombre de points de discrétisation de la barre
         * \param t_max : temps maximal de la simulation
         * \param L : longueur de la barre
         * \param u0 : température initiale de la barre
         * \param f : source de chaleur
         * \param lambda : vecteur des conductivités thermiques
         * \param p : vecteur des densités
         * \param c : vecteur des capacités thermiques
         * \param num_materiau : numéro du matériau de la barre
        */

        heatEquationPlaque(int nb_points_discretisation, double t_max, double L, double u0, double f, std::vector<double> lambda, std::vector<double> p , std::vector<double> c, int num_materiau);

        /**
         * \brief Fonction qui calcule la source de chaleur en fonction de x et y
         * \param x : position dans la barre
         * \param y : position dans la barre
         * \return la valeur de la source de chaleur en fonction de x et y
         */

        double heatSource(double x, double y);

        /**
        * \brief Méthode qui retourne Bi, la matrice dans la diagonale principale
        * \param a : vecteur des valeurs de la diagonale inférieure de B
        * \param b : vecteur des valeurs de la diagonale principale de B
        * \param c : vecteur des valeurs de la diagonale supérieure de B
        * \return la matrice Bi
        */

        Matrix tridiagonal_form(const std::vector<double>& a, const std::vector<double>& b, const std::vector<double>& c);

        /**
        * \brief Méthode qui effectue l'algorithme de Thomas pour résoudre un système tridiagonal lorsque on
        * a un système avec des matrices par blocs
        * \param B : vecteur des matrices B_i de la diagonale principale
        * \param D : matrice D de la partie droite du système SU = D
        * \return la matrice U de la solution du système SU = D
        */

        Matrix block_thomas_algorithm(std::vector<Matrix> B, Matrix D);

        /**
        * \brief Méthode qui calcule la matrice de solution U à chaque pas de temps pour retourner la solution
        * au temps at_time 
        * \param at_time : temps auquel on veut la solution
        * \param num_materiau : numéro du matériau de la barre pour lequel on veut la solution
        * \return la matrice U de la solution au temps at_time
        */

        Matrix laasonenSolve(double at_time, int num_materiau);

        /**
        * \brief Méthode qui renvoie T_i, le vecteur des points du maillage en temps
        * \return le vecteur des points du maillage en temps
        */

        std::vector<double> getTi() const {return t_i_;};

        









};

#endif