#include "headers/heatEquationAnimation.h"
#include "headers/heatEquationBarre.h"
#include <algorithm>

HeatEquationAnimation::HeatEquationAnimation() : window(nullptr), renderer(nullptr) {}

HeatEquationAnimation::~HeatEquationAnimation() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

SDL_Window *HeatEquationAnimation::initWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stdout, "Échec de l'initialisation de SDL (%s)\n", SDL_GetError());
        return nullptr;
    }

    window = SDL_CreateWindow("Représentation de l'équation de la chaleur", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 1200, 500, SDL_WINDOW_SHOWN);

    if (!window) {
        SDL_Quit();
        fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
    }

    return window;
}

SDL_Renderer *HeatEquationAnimation::initRenderer(SDL_Window *window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        fprintf(stdout, "Échec de création du renderer (%s)\n", SDL_GetError());
    }

    return renderer;
}

void HeatEquationAnimation::animationBarre(double u0, const Matrix &solution) {
    SDL_Rect rect;
    rect.w = 1;
    rect.h = 50;
    rect.y = 250;

    std::vector<double> maxS(solution.rows(), 0.0);

    for (int i = 0; i < solution.rows(); i++) {
        const auto rowVector = solution.getRow(i);
        maxS[i] = *std::max_element(rowVector.begin(), rowVector.end());
    }

    auto maxSolution = *std::max_element(maxS.begin(), maxS.end());
    maxSolution = maxSolution - 273.15;

    for (int i = 0; i < solution.rows(); i++) {
        for (int j = 0; j < solution.cols(); j++) {
            rect.x = j + 100;
            double cls = solution(i, j) - 273.15;
            double normalizedQty = (cls - u0) / (maxSolution - u0);

            Uint8 r = static_cast<Uint8>(std::min(255.0, normalizedQty * 255));
            Uint8 g = 0;
            Uint8 b = static_cast<Uint8>(std::min(255.0, (1.0 - normalizedQty) * 255));

            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
}

void HeatEquationAnimation::animationPlaque(double u0, const std::vector<std::vector<Matrix>> &solutions) {
    SDL_Rect rect;
    rect.w = 50;  // Largeur du rectangle
    rect.h = 50;  // Hauteur du rectangle

    std::vector<double> maxS(solutions.size(), 0.0);

    for (size_t t = 0; t < solutions.size(); t++) {
        const auto &solution = solutions[t]; // le vecteur des solutions
        double max = Matrix::max(solution);   // Utilisez la méthode maxInVector
        maxS[t] = max;
    }

    auto maxSolution = *std::max_element(maxS.begin(), maxS.end());
    maxSolution = maxSolution - 273.15;

    for (size_t time = 0; time < solutions.size(); time++) {
        const auto &solution = solutions[time]; // le vecteur des solutions

        for (size_t row = 0; row < solution.size(); row++) {
            for (int col = 0; col < solution[row].rows(); col++) {
                rect.x = row * 50 + 200;  // Position en x basée sur l'indice de ligne
                rect.y = col * 50 + (500 - solution[row].rows() * 50) / 2;  // Centrer verticalement

                double cls = solution[row](col, 0) - 273.15;
                double normalizedQty = (cls - u0) / (maxSolution - u0);

                Uint8 r = static_cast<Uint8>(std::min(255.0, normalizedQty * 255));
                Uint8 g = 0;
                Uint8 b = static_cast<Uint8>(std::min(255.0, (1.0 - normalizedQty) * 255));

                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(50);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
    }

    // Ajoutez une pause finale avant de terminer l'animation
    SDL_Delay(500);
}

