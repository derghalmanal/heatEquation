#include <iostream>
#include <vector>
#include <algorithm>
#include "headers/heatEquationBarre.h"
#include "headers/heatEquationAnimation.h"



int main() {

    // Paramètres nécessaires pour le constructeur
    int n = 1001;
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

    std::vector<double> t_i = barre.getTi();

    std::cout << "t_i : ";
    for (size_t i = 0; i < t_i.size(); ++i) {
        std::cout << t_i[i] << " ";
    }
    std::cout << std::endl;

    double pas = t_max / 100.0;

    // Initialisation de la fenêtre et du renderer SDL
    SDL_Window *window = initWindow();
    SDL_Renderer *renderer = initRenderer(window);

    // Durée entre chaque frame de l'animation en millisecondes
    int frameDelay = 160;  // Vous pouvez ajuster cela en fonction de votre préférence

    for (double i = 0.0; i <= t_max; i += pas) {
        std::vector<double> solution = barre.laasonenSolve(i, num_materiau);
        std::cout << "Solution à t = " << i << " : ";
        for (std::size_t j = 0; j < solution.size(); ++j) {
            std::cout << solution[j] << " ";
        } 
        std::cout << std::endl;

        // Affichage de la barre en SDL
        animationBarre(renderer, u0, solution);

        // Actualisation de la fenêtre SDL
        SDL_RenderPresent(renderer);

        // Pause entre les frames
        SDL_Delay(frameDelay);

        // Effacement de la fenêtre pour la prochaine frame
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

    }

    // Libération des ressources SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
