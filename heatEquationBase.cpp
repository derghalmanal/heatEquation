/**
 * @file heatEquationBase.cpp
 * @author Ania Polidori & Manal Derghal
 * @brief Implémentation de la classe de base pour les équations de la chaleur
 * 
 */


#include "./heatEquation.hpp"
#include <vector>
#include <set>
#include <stdexcept>

template<std::size_t d>
heatEquationBase<d>::heatEquationBase(int nb_points_discretisation, double longueur, double t_max, double taille_intervalle){
    nb_points_discretisation_ = nb_points_discretisation;
    longueur_ = longueur;
    t_max_ = t_max;
    taille_intervalle_ = taille_intervalle;
};

template<std::size_t d>
void heatEquationBase<d>::initialize_u0(const std::vector<double>& u0){
    if (u0.size() == d) {
        u0_ = u0; // faut modifier et mettre u0 en delgré Kelvin 
    } else {
        throw std::invalid_argument("La taille du vecteur u0 ne correspond pas à la dimension d.");
    }
};