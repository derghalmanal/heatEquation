#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <vector>

namespace Data {

    constexpr int n = 1001; // Nombre de points de discrétisation pour la barre
    constexpr int m = 10; // Nombre de points de discrétisation pour la plaque
    constexpr double t_max = 16.0; // Temps maximal de simulation
    constexpr double L = 1.0; // Longueur de la barre
    constexpr double u0 = 13.0; // Température initiale de la barre
    constexpr double f = 80.0; // Température de la plaque
    double pas = t_max / 100.0; // Pas de temps de la simulation
    int num_materiau = 0; // Numéro du matériau choisi
    int choix_objet = 0; // Numéro de l'objet choisi
    const std::vector<double> lambda = {389.0, 80.2, 1.2, 0.1}; // Conductivité thermique des matériaux
    const std::vector<double> p = {8940.0, 7874.0, 2530.0, 1040.0}; // Masse volumique des matériaux
    const std::vector<double> c = {380.0, 440.0, 840.0, 1200.0}; // Chaleur spécifique des matériaux

    /**
     * \brief Demande à l'utilisateur de choisir un matériau parmi les 4 disponibles.
    */

    void demanderNumeroMateriau() {
        std::cout << "Choisissez un matériau (0) Cuivre, (1) Fer, (2) Verre, (3) Polystyrene : ";
        std::cin >> num_materiau;

        // Vérifier si l'entrée utilisateur est valide (entre 0 et 3 inclus)
        if (num_materiau < 0 || num_materiau > 3) {
            std::cerr << "Choix de matériau invalide. Utilisation du matériau par défaut (0)." << std::endl;
            num_materiau = 0;
        }
    }

    /**
     * \brief Demande à l'utilisateur de choisir un objet parmi la barre et la plaque.
    */

    void demanderObjet() {
        std::cout << "Choisissez un objet (0) Barre, (1) Plaque : ";
        std::cin >> choix_objet;

        // Vérifier si l'entrée utilisateur est valide (entre 0 et 3 inclus)
        if (num_materiau < 0 || num_materiau > 1) {
            std::cerr << "Choix d'objet invalide. Utilisation de la barre par défaut (0)." << std::endl;
            choix_objet = 0;
        }
    }
}

#endif
