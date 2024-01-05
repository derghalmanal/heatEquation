#include <iostream>
#include <vector>
#include "headers/heatEquationBarre.h"
#include "headers/heatEquationPlaque.h"
#include "headers/heatEquationAnimation.h"
#include "headers/data.h"
using namespace Data;

int main() {
    demanderNumeroMateriau();
    demanderObjet();

    if (choix_objet == 0) {
        heatEquationBarre barre(n, t_max, L, u0, f, lambda, p, c, num_materiau);

        Matrix solution = Matrix(t_max, n);
        for (double i = 0.0; i <= t_max; i += pas) {
            std::vector<double> tempsSolution = barre.laasonenSolve(i, num_materiau);
            std::cout << "Solution à t = " << i << " : " << std::endl;
            for (std::size_t j = 0; j < tempsSolution.size(); ++j) {
                std::cout << tempsSolution[j] << " ";
                solution(i, j) = tempsSolution[j];
            }
            std::cout << std::endl;
        }

        HeatEquationAnimation animation;
        SDL_Window *window = animation.initWindow();
        SDL_Renderer *renderer = animation.initRenderer(window);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        animation.animationBarre(u0, solution);

        // Libération des ressources SDL
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);


    } else if (choix_objet == 1) {
        heatEquationPlaque plaque(m, t_max, L, u0, f, lambda, p, c, num_materiau);
        // Utilisez un vector pour stocker les solutions à chaque instant
        std::vector<std::vector<Matrix>> allSolutions;

        for (double i = 0.0; i <= t_max; i += pas) {
            std::vector<Matrix> solution = plaque.laasonenSolve(i, num_materiau);
            allSolutions.push_back(solution);

            std::cout << "Solution à t = " << i << " : " << std::endl;
            for (std::size_t j = 0; j < solution.size(); ++j) {
                std::cout << "Solution à x = " << j << " : " << std::endl;
                std::cout << solution[j].reshape(1, m) << std::endl;
            }
        }

        HeatEquationAnimation animation;
        SDL_Window *window = animation.initWindow();
        SDL_Renderer *renderer = animation.initRenderer(window);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        animation.animationPlaque(u0, allSolutions);

        // Libération des ressources SDL
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

    return 0;
}
