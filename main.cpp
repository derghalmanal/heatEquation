#include <iostream>
#include <vector>
#include <algorithm>
#include "headers/heatEquationBarre.h"
#include "headers/heatEquationPlaque.h"
#include "headers/heatEquationAnimation.h"
#include "headers/data.h"
using namespace Data;



int main() {

    demanderNumeroMateriau();
    demanderObjet();
    
    if (choix_objet == 0){

        heatEquationBarre barre(n, t_max, L, u0, f, lambda, p, c, num_materiau);

        SDL_Window *window = initWindow();
        SDL_Renderer *renderer = initRenderer(window);

/*
        // Durée entre chaque frame de l'animation en millisecondes
        int frameDelay = 160;

    
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
        */

        std::vector<std::vector<double>> solution ;  // stocke les solutions dans une matrice 
        for(double i = 0.0 ; i <= t_max ; i += pas){
            std::vector<double> tempsSolution = barre.laasonenSolve(i, num_materiau) ; // solution au ième temps 
            solution.push_back(tempsSolution) ; // ajoute ce vecteur à la matrice de solution 

        }

        animationBarre(renderer, u0, solution);


        // Libération des ressources SDL
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    
    } else if (choix_objet == 1){

        heatEquationPlaque plaque(m, t_max, L, u0, f, lambda, p, c, num_materiau);

        for (double i = 0.0; i <= t_max; i += pas) {
            std::vector<Matrix> solution = plaque.laasonenSolve(i, num_materiau);
            std::cout << "Solution à t = " << i << " : " << std::endl;
            for (std::size_t j = 0; j < solution.size(); ++j) {
                std::cout << "Solution à x = " << j << " : " << std::endl;
                std::cout << solution[j].reshape(1, m) << std::endl;
            }
        }
    }

    return 0;
}
