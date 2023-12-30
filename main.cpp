#include <iostream>
#include <vector>
#include "heatEquationBarre.h"


int main() {

    // Paramètres nécessaires pour le constructeur
    int n = 10;
    double t_max = 16.0;
    double L = 1.0;
    double u0 = 13.0;
    double f = 80.0;
    int num_materiau = 0;
    std::vector<double> lambda = {389.0, 80.2, 1.2, 0.1};
    std::vector<double> p = {8940.0, 7874.0, 2530.0, 1040.0};
    std::vector<double> c = {380.0, 440.0, 840.0, 1200.0};


    // Création de l'instance de la classe avec les paramètres
    heatEquationBarre barre(n, t_max, L, u0, f, lambda, p, c, num_materiau);

    barre.solve(3);

    std::cout << "Pour t=3: " << std::endl;

    barre.printSolution();

    return 0;
}

