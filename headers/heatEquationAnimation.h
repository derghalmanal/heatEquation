#ifndef HEATEQUATIONANIMATION_H
#define HEATEQUATIONANIMATION_H


#include <SDL2/SDL.h>
#include "heatEquationBarre.h"


/**
 * @brief Fonction qui initialise une fenêtre SDL
 * 
 * @return SDL_Window* 
 */
SDL_Window *initWindow();


/**
 * @brief Fonction qui initialise un rendu pour une fenêtre SDL
 * 
 * @param window : fenêtre SDL
 * @return SDL_Renderer* 
 */
SDL_Renderer *initRenderer(SDL_Window *window);


/**
 * @brief Fonction qui joue l'animation de l'équation de la chaleur sur un certain temps
 * 
 * @param renderer : rendu SDL où l'animation est joué
 * @param u0 : température initiale
 * @param solution : matrice qui contient toutes les solutions de l'équation de la chaleur 
 */
void animationBarre(SDL_Renderer *renderer, double u0, const std::vector<std::vector<double>> &solution);


#endif