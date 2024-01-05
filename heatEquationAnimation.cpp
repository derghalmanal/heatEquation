#include "headers/heatEquationAnimation.h"
#include "headers/heatEquationBarre.h"
#include <algorithm>


SDL_Window *initWindow(){

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de SDL (%s)\n",SDL_GetError());
        return nullptr; 
    }

    /* Création de la fenêtre */
    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Représentation de l'équation de la chaleur",SDL_WINDOWPOS_CENTERED, /*!< position en X, pour que la fenêtre soit toujours centrée sur l'écran */
                                                                           SDL_WINDOWPOS_CENTERED, /*!< position en Y, pour que la fenêtre soit toujours centrée sur l'écran */
                                                                           1200, /*!< largeur de la fenêtre*/
                                                                           500, /*!<hauteur de la fenêtre*/
                                                                           SDL_WINDOW_SHOWN);

    if(!window)
    {
        SDL_Quit();
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }

    return window;
}



SDL_Renderer *initRenderer(SDL_Window *window){
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    if(!renderer){
        SDL_DestroyWindow(window);
        SDL_Quit();
        fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
    }

    return renderer;

}



void animationBarre(SDL_Renderer *renderer, double u0, const std::vector<double> &solution)  {

// Définir les propriétés du rectangle représentant la barre
    SDL_Rect rect;
    rect.w = 1;  // Largeur du rectangle
    rect.h = 50; // Hauteur du rectangle
    rect.y = 250; // Position en y basée sur la température
    // Dessiner la barre en fonction de la température
    for (size_t i = 0; i < solution.size(); ++i) {
        rect.x = i + 100; // Position en x basée sur les coordonnées de la barre
        // remise en degré celsius 
        double cls = solution[i] - 273.15 ;

        // Choisir la couleur en fonction de la température
        /*
        if (cls = u0) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Bleu
        } else if (cls < 20) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Vert
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
        }
        */
        auto maxSolution = *std::max_element(solution.begin(), solution.end());
        // Calculer la couleur en fonction de la température
        double qte = (cls - u0) / (maxSolution - u0);

        SDL_SetRenderDrawColor(renderer, 0, 0 + qte * 255, 255 - qte * 255, 255);

        // Remplir la section du rectangle avec la couleur définie
        SDL_RenderFillRect(renderer, &rect);
    }

    
}


