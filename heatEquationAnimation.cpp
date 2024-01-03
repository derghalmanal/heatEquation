#include "heatEquationAnimation.h"
#include "heatEquationBarre.h"
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
                                                                           640, /*!< largeur de la fenêtre*/
                                                                           480, /*!<hauteur de la fenêtre*/
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



void animationBarre(SDL_Renderer *renderer, const heatEquationBarre &barre, const std::vector<double> &solution)  {
    // Récupérer les données nécessaires de la barre
    std::vector<double> xi = barre.getXi();

    // Définir les propriétés du rectangle représentant la barre
    SDL_Rect rect;
    rect.w = 2;  // Largeur du rectangle
    rect.h = 50; // Hauteur du rectangle

    // Dessiner la barre en fonction de la température
    for (size_t i = 0; i < solution.size(); ++i) {
        rect.x = static_cast<int>(xi[i]); // Position en x basée sur les coordonnées de la barre
        rect.y = 400 - static_cast<int>(solution[i]); // Position en y basée sur la température

        // Choisir la couleur en fonction de la température
        if (solution[i] < 200) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Bleu
        } else if (solution[i] < 400) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Vert
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
        }

        // Remplir le rectangle avec la couleur définie
        SDL_RenderFillRect(renderer, &rect);

    }
}


