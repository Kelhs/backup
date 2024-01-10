//
// Created by kelvin on 08/11/23.
//

#include "main.h"
#include "point.h"
#include "polygone.h"
#include "affichage.h"
#include "enveloppe.h"
#include <random>
#include <algorithm>
#include <iostream>


#include <SDL2/SDL.h>

bool Xcompare(const Point& p1, const Point& p2) {
    return p1.x() < p2.x();
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Algo géo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1900, 1100, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    for(int i = 0; i < 20; i++){
        std::vector<Point> points;
        srand((unsigned) time(NULL));
        int n = 3 + (rand() % 1000);
        for(int i = 0; i < n; i++){
            int x = 100 + (rand() % 1700);
            int y = 100 + (rand() % 900);
            points.push_back(Point(x, y));
        }
        std::sort(points.begin(), points.end(), Xcompare);

        Polygone p;

        enveloppe(points, p);
        Sommet* s = p.premier();

        if (s == nullptr) {
            std::cout << "Le polygone est vide.\n";
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        for(const Point& p : points){
            SDL_Rect rect = { p.x() - 2, p.y() - 2, 4, 4 };
            SDL_RenderFillRect(renderer, &rect);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        trace(p, renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(1500);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
