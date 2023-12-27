/**
 * @file heatEquation.hpp
 * @brief contient la déclaration des classes heatEquationBase, heatEquationBarre, heatEquationPlaque
 * @author Ania Polidori & Manal Derghal
*/


#ifndef HEATEQUATION_H
#define HEATEQUATION_H

#include <vector>
#include <set>

/**
 * @class heatEquationBase
 * @brief classe de base pour les équations de la chaleur
 * elle gère les informations qu'on retrouvera pour l'équation de la chaleur peu importe le cas
 * 
 */
class heatEquationBase {
    private: 
        int nb_points_discretisation_ ; /*!<Nombre de points de discrétisation en espace et en temps*/
        double longueur_ ; /*!<longueur L de l'objet */
        double t_max_ ; /*!<temps maximum*/
        double source_chaleur_ ; /*!<source de chaleur F */
};

/**
 * @class heatEquationBarre
 * @brief classe qui hérite de heatEquationBase
 * pour l'équation de la chaleur pour une barre (objet à 1 dimension)
 * 
 */
class heatEquationBarre : public heatEquationBase {
    private: 
        double taille_intervalle_ ; /*!<taille i de l'intervalle du maillage*/ 
        std::vector<double> u0_ ; /*!<état initial de la température (quand temps = 0 , constante en x)*/
        std::set<double> x_i_ ; /*!<points du maillage x_i */
        std::set<double> t_i_ ; /*!<points du maillage t_i */


    public: 
        /**
         * @brief Constructeur pour un nouveau objet heatEquationBarre
         * 
         * @param longueur
         * @param taille_intervalle 
         * @param t_max 
         * @param nb_points_discretisation 
         * @param x_i 
         * @param t_i 
         */
        heatEquationBarre(double longueur, double taille_intervalle, double t_max, int nb_points_discretisation, const std::set<double>& x_i, const std::set<double>& t_i);


        /**
         * @brief Fonction d'initialisation de l'état initial u0
         * 
         * @param u0 
         */
        void initialize_u_0(const std::vector<double>& u0);


        /**
         * @brief Fonction de calcul d'ajouts de chaleur en fonction d'une valeur f
         * 
         * @param f : une valeur de température
         */
        void calcul_source_chaleur(const int & f);


        /**
         * @brief Calcul de l'équation de la chaleur en foncton des valeurs de lambda, p et c
         * Ces trois paramètres sont pris en fonction du matériau pour lequel on veut calculer l'équation
         * 
         * @param lambda : conductivité thermique du matériau
         * @param p : masse volumique du matériau
         * @param c : chaleur massique du matériau
         * @return 
         */
         std::vector<std::vector<double>> solutionEquation(double lambda, double p, double c) const; 

};

#endif