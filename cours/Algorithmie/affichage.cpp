#include "affichage.h"
#include "point.h"
#include "polygone.h"
#include <SDL2/SDL.h>


// trace un segment entre deux points a et b
void segment(const Point &a, const Point &b, SDL_Renderer* renderer)
{
    SDL_RenderDrawLine(renderer, a.x(), a.y(), b.x(), b.y());
}


// trace le polygone P dans une fenêtre graphique
void trace(const Polygone &P, SDL_Renderer* renderer)
{
    
    Sommet* s = P.premier();

    do{
        if(s != nullptr && s->suivant() != nullptr){
            segment(s->coordonnees(), s->suivant()->coordonnees(), renderer);
        }
        s = s->suivant();
    }
    while(s != P.premier());
    
}




