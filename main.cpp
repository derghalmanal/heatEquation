#include <iostream>
#include <vector>
#include "heatEquationBarre.h"


int main() {

    // Paramètres nécessaires pour le constructeur
    int nb_points_discretisation = 1001;
    double t_max = 16.0;
    double L = 1.0;
    double u0 = 13.0;
    double f = 80.0;
    std::vector<double> lambda = {389.0, 80.2, 1.2, 0.1};
    std::vector<double> p = {8940.0, 7874.0, 2530.0, 1040.0};
    std::vector<double> c = {380.0, 440.0, 840.0, 1200.0};

    // Création de l'instance de la classe avec les paramètres
    heatEquationBarre barre(nb_points_discretisation, t_max, L, u0, f, lambda, p, c);



    // Assuming you have already populated source_chaleur_ vector
    // with appropriate values based on your problem.
    // ...

    barre.initialize_matrice(0);

    // Solve the system
    barre.solve();

    // Print the solution
    for (int i = 0; i < nb_points_discretisation; ++i) {
        std::cout << barre.get_U()[i] << " ";
    }

    return 0;
}