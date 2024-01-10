#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "point.h"
#include "polygone.h"
#include <SDL2/SDL.h>


// trace un segment entre deux points a et b
void segment(const Point & a, const Point & b, SDL_Renderer* renderer);

// trace le polygone P dans une fen�tre graphique
void trace(const Polygone &P, SDL_Renderer* renderer);

#endif
