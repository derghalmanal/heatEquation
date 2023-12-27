/**
 * @file heatEquationBarre.cpp
 * @author Ania Polidori & Manal Derghal
 * @brief Implémentation de la classe pour l'équation de la chaleur pour un objet à 1 dimension
 * 
 */


#include "./heatEquation.hpp"
#include <vector>
#include <set>
#include <stdexcept>
#include <cmath>


heatEquationBarre::heatEquationBarre(int nb_points_discretisation, double longueur, double t_max, double taille_intervalle, const std::set<double>& x_i, const std::set<double>& t_i)
    : heatEquationBase<1>(nb_points_discretisation, longueur, t_max, taille_intervalle), x_i_(x_i), t_i_(t_i){};



void heatEquationBarre::calcul_source_chaleur(const int & f){
    std::vector<double> F ; 
    double L = this->longueur_;
    for(std::size_t i = 0 ; i < this->source_chaleur_.size(); i++){
        if(i > (L/10) && i < (2*L/10)){
            F[i] = std::pow(f,2) * this->t_max_ ;
        }
        else if(i > (5*L/10) && i < (6*L/10)){
            F[i] = std::pow(f,2) * (3/4);
        }
        else{
            F[i] = 0 ; 
        }
    }
};