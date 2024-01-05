#ifndef HEATEQUATIONBARRE_HPP
#define HEATEQUATIONBARRE_HPP

#include <vector>
#include <set>
#include "heatEquationBase.h"



/**
 * \class {heatEquationBarre}
 * \brief {classe qui hérite de heatEquationBase pour l'équation de la chaleur pour une barre (objet à 1 dimension)}
 * 
 */
class heatEquationBarre : public heatEquationBase<1> {


    private:
    
        std::vector<double> x_i_ ; /*!<points du maillage x_i */
        std::vector<double> t_i_ ; /*!<points du maillage t_i */
        std::vector<double> source_chaleur_ ; /*!<source de chaleur F , plusieurs valeurs de F en fonction de x donc F même taille que x */
        std::vector<double> U_; /*!<solution de l'équation de la chaleur*/
        std::vector<double> A_; /*!<vecteur A inférieur de la matrice tridiagonale*/
        std::vector<double> B_; /*!<vecteur B de la matrice tridiagonale de la diagonale principale*/
        std::vector<double> C_; /*!<vecteur C supérieur de la matrice tridiagonale*/
        std::vector<double> D_; /*!<vecteur D tel que SU = D*/
            // |b0 c0 0 ||u0| |d0|
            // |a1 b1 c1||u1|=|d1|
            // |0  a2 b2||u2| |d2|




    public:

        /**
        * \brief Constructeur de la classe pour l'équation de la chaleur pour un objet à 1 dimension
        * \param nb_points_discretisation : nombre de points de discrétisation en espace et en temps
        * \param t_max : temps maximum
        * \param L : longueur de la barre
        * \param u0 : état initial de la température (quand temps = 0)
        * \param f : source de chaleur
        * \param lambda : conductivité thermique du matériau
        * \param p : masse volumique du matériau
        * \param c : chaleur massique du matériau
        * \param num_materiau : numéro du matériau
        */


        heatEquationBarre(int nb_points_discretisation, double t_max, double L, double u0, double f, std::vector<double> lambda, std::vector<double> p , std::vector<double> c, int num_materiau);

        /**
         * \brief Fonction qui calcule la source de chaleur en fonction de x
         * \param x : position dans la barre
         * \return la source de chaleur en fonction de x
         */

        double heatSource(double x);


        /**
        * \brief Fonction qui implémente l'algorithme de Thomas
        * \param A : vecteur A de la matrice tridiagonale
        * \param B : vecteur B de la matrice tridiagonale
        * \param C : vecteur C de la matrice tridiagonale
        * \param D : vecteur D tel que SU = D
        * \return le vecteur U tel que SU = D
        */
        std::vector<double> thomas_algorithm(std::vector<double> A, std::vector<double> B, std::vector<double> C, std::vector<double> D);


        /**
        * \brief Fonction qui implémente la méthode de Laasonen qui résout l'équation de la chaleur
        * \param at_time : temps auquel on veut la solution
        * \param num_materiau : numéro du matériau
        * \return la solution de l'équation de la chaleur à un temps donné
        */
        std::vector<double> laasonenSolve(double at_time, int num_materiau);

        /**
        * \brief Fonction qui retourne le maillage en temps
        * \return le maillage en temps
        */
        std::vector<double> getTi() const;


};

#endif