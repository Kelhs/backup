//
// Created by kelvin on 17/11/23.
//

#include "triangulation.h"
#include "point.h"
#include "carte.h"


void triangulation(vector<Point> &T, Carte &C){

    DemiCote* dc = C.ajouteCote(T[0], T[1]);
    for(int i = 2; i < T.size(); i++){
        while(T[i].aGauche(dc->coordonnees(), dc->oppose()->coordonnees()) != 1){
            dc = C.ajouteCote(dc->oppose(), T[i]);
        }
        while(T[i].aGauche(dc->coordonnees(), dc->oppose()->coordonnees()) == 1){
            dc = C.ajouteCote(dc, T[i]);
        }
    }

}
