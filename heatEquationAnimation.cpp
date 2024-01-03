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



void animationBarre(SDL_Renderer *renderer, const heatEquationBarre &barre) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Couleur de fond (blanc)
    SDL_RenderClear(renderer);

    // Récupération des données nécessaires
    std::vector<double> xi = barre.getXi();
    std::vector<double> solution = barre.getSolution();
    double maxTemperature = *std::max_element(solution.begin(), solution.end());
    double minTemperature = *std::min_element(solution.begin(), solution.end());

    // Dessin de la barre en fonction des températures
    for (std::size_t i = 0; i < xi.size(); ++i) {
        double val = solution[i];
        double qte = (val - minTemperature) / (maxTemperature - minTemperature);  // Échelle entre 0 et 1

        SDL_Rect rect;
        rect.x = static_cast<int>(xi[i] * 640);  // Ajustez la position en fonction de votre échelle
        rect.y = 200;
        rect.w = 2;  // Largeur de chaque section de la barre
        rect.h = static_cast<int>(50 * qte);  // Hauteur en fonction de la température

        // Choix des couleurs en fonction de qte
        SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(255 * qte), 0, static_cast<Uint8>(255 * (1 - qte)), 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}