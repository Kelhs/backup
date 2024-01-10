#include "affichage.h"
#include "point.h"
#include "carte.h"
#include <SDL2/SDL.h>



// trace un segment entre deux points a et b
void segment(const Point &a, const Point &b, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { a.x() - 2, a.y() - 2, 4, 4 };
    SDL_RenderFillRect(renderer, &rect);
    SDL_Rect rect2 = { b.x() - 2, b.y() - 2, 4, 4 };
    SDL_RenderFillRect(renderer, &rect2);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawLine(renderer, a.x(), a.y(), b.x(), b.y());
}

// trace la carte C dans une fen�tre graphique
void trace(const Carte &C,  SDL_Renderer* renderer)
{
    for(int i = 0; i < C.nbDemiCotes(); i++){
        segment(C.demiCote(i)->coordonnees(), C.demiCote(i)->oppose()->coordonnees(), renderer);
    }
}


