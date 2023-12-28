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


std::vector<std::vector<double>> heatEquationBarre::solutionEquation(double lambda, double p, double c) const{
    double T = this->t_max_ / (this->nb_points_discretisation_ + 1);
    double h = this->longueur_ / (this->nb_points_discretisation_+1);
    double s = (lambda*T)/(p*c*std::pow(h,2));
    int N = this->nb_points_discretisation_ ;


    // on note l'équation S * U^(j) = D^(j)
    std::vector<std::vector<double>> matS(N , std::vector<double>(N, 0.0));
    std::vector<double> D(N); 

    // initialisation de la matrice S et des valeurs de D^(1) grâce aux valeurs de U^(0) = u0
    for(int i = 0 ; i < N ; i++){
        matS[i][i] = 1 + (2*s);
        if (i > 0) {
            matS[i][i - 1] = -s ;
        }
        if (i < N - 1) {
            matS[i][i + 1] = -s ;
        }

        D[i] = u0_[i] + (T*this->source_chaleur_[i])/(p*c);

    }
    matS[0][0] = 1 + s ;
    D[N] = u0_[N] + (T*this->source_chaleur_[N])/(p*c) * s*u0_[N];

    
    // on change les coefficients diagonaux 
    std::vector<std::vector<double>> newMat(N, std::vector<double>(N, 0.0)); // nouvelle matrice des coefficients 

    for(int i = 0 ; i < N ; i++){
        newMat[i][i] = 1; // diagonale en 1
        
        // nouvelles valeurs pour la diagonale supérieure
        newMat[i][i+1] = matS[i][i+1] / (matS[i][i] - (newMat[i-1][i] * matS[i+1][i]));
        newMat[0][1] = matS[0][1] / matS[0][0] ;
    }

    // nouvelles valeurs de U^(j) et D^(j) pour chaque valeurs de j

    std::vector<std::vector<double>> solution(N) ; // on créé la matrice où l'on stock les U^(j)
    solution[0] = u0_ ; 
    std::vector<double> newD(N); // quand on change les valeurs de D 

    for(int j = 1 ; j < N+1 ; j++){
        // mise à jour des valeurs de D
        newD[0] = D[0] / newMat[0][0];
        for(int k = 1 ; k < N ; k++){
            newD[k] = (D[k] - newD[k-1] * matS[k+1][k]) / (matS[k][k] - newMat[k-1][k] * matS[k+1][k]);
        }

        // mise à jour des valeurs de U 
        for(int i = N ; i >= 1 ; --i){
            solution[i][j] = newD[i] - (newMat[i][i+1] * solution[i+1][j]) ;
        }

        D = newD ; 
    }

    return(solution);






}