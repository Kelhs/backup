#include "enveloppe.h"
#include "point.h"
#include "polygone.h"

#include <vector>
#include <iostream>

using namespace std;


// Construit dans le polygone P l’enveloppe convexe des trois points a,b,c. On suppose P initialement vide.
// La fonction renvoie l’adresse du sommet de coordonnées c.
Sommet* enveloppe(const Point &a, const Point &b, const Point &c, Polygone &P)
{
	Sommet* s_a = P.ajouteSommet(a);
	if(b.aGauche(c, a)){
		Sommet* s_b = P.ajouteSommet(b, s_a);
		Sommet* s_c = P.ajouteSommet(c, s_b);
		return s_c;
	} else {
		Sommet* s_c = P.ajouteSommet(c, s_a);
		Sommet* s_b = P.ajouteSommet(b, s_c);
		return s_b;
	}
}


// Construit dans le polygone P l’enveloppe convexe de l'ensemble de points donné dans T.
// On suppose P initialement vide.
void enveloppe(vector<Point> &T, Polygone &P)
{
    int n = T.size();


    if (n < 3) {
        return;
    }

    int pointLePlusAGauche = 0;
    for (int i = 1; i < n; ++i) {
        if (T[i].x() < T[pointLePlusAGauche].x()) {
            pointLePlusAGauche = i;
        }
    }

    int pointCourant = pointLePlusAGauche;

    Sommet* dernierSommet = nullptr;

    do {

        dernierSommet = P.ajouteSommet(T[pointCourant],dernierSommet);

        int prochainPoint = (pointCourant + 1) % n;

        for (int i = 0; i < n; ++i) {
            if (T[pointCourant].aGauche(T[i], T[prochainPoint]) == 1) {
                prochainPoint = i;
            }
        }

        pointCourant = prochainPoint;

    } while (pointCourant != pointLePlusAGauche);
}



