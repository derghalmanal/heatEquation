#ifndef HEATEQUATIONANIMATION_H
#define HEATEQUATIONANIMATION_H


#include <SDL2/SDL.h>
#include "heatEquationBarre.h"


SDL_Window *initWindow();

SDL_Renderer *initRenderer(SDL_Window *window);

void animationBarre(SDL_Renderer *renderer, double u0, const std::vector<double> &solution);


#endif