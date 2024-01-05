#ifndef HEATEQUATIONANIMATION_H
#define HEATEQUATIONANIMATION_H

#include <SDL2/SDL.h>
#include "heatEquationBarre.h"
#include "matrix.h"

/**
 * \class {heatEquationAnimation}
 * \brief {classe permettant de créer une animation de la solution de l'équation de la chaleur}
 * 
 */

class HeatEquationAnimation {

    private:
    SDL_Window *window; /* la fenetre */
    SDL_Renderer *renderer; /* le rendu */

    
    public:

        /**
         * \brief constructeur de la classe HeatEquationAnimation
        */
        HeatEquationAnimation();

        /**
         * \brief destructeur de la classe HeatEquationAnimation
        */
        ~HeatEquationAnimation();

        /**
         * \brief méthode permettant d'initialiser la fenêtre et le rendu
         * \return la fenêtre
        */
        SDL_Window *initWindow();

        /**
         * \brief méthode permettant d'initialiser le rendu
         * \param window la fenêtre
         * \return le rendu
        */
        SDL_Renderer *initRenderer(SDL_Window *window);

        /**
         * \brief méthode permettant de simuler l'animation de la solution de l'équation de la chaleur pour une barre
         * \param u0 la condition initiale
         * \param solution la solution de l'équation de la chaleur pour chaque instant t
        */
        void animationBarre(double u0, const Matrix &solution);

        /**
         * \brief méthode permettant de simuler l'animation de la solution de l'équation de la chaleur pour une plaque
         * \param u0 la condition initiale
         * \param solution la solution de l'équation de la chaleur pour chaque instant t
        */
        void animationPlaque(double u0, const std::vector<std::vector<Matrix>> &solution);

};

#endif
