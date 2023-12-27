#ifndef HEATEQUATION_H
#define HEATEQUATION_H

#include <vector>
#include <set>

class heatEquationBase {
    private: 
        int nb_points_discretisation_ ; 
        double longueur_ ; // longueur L de l'objet
        double t_max_ ; //  
        double source_chaleur_ ; // valeur F de la source de chaleur 
};

class heatEquationBarre : public heatEquationBase {
    private: 
        double taille_intervalle_ ; // taille i de l'intervalle du maillage 
        std::vector<double> u0_ ; 
        std::set<double> x_i_ ; // points du maillage x_i 
        std::set<double> t_i_ ; // points du maillage t_i 


    public: 
        // constructeur valué 
        heatEquationBarre(double longueur, double taille_intervalle, double t_max, int nb_points_discretisation, const std::set<double>& x_i, const std::set<double>& t_i);

        // fonction d'initialisation de u_0 
        void initialize_u_0(const std::vector<double>& u0);

        // fonction de calcul de F en fonction de la valeur de f 
        void calcul_source_chaleur(const int & f);


        // calcul de l'équation en fonction des valeurs de lambda, p et c 
         std::vector<std::vector<double>> solutionEquation(double lambda, double p, double c) const; 

};

#endif