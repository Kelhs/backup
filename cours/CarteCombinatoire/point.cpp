#include <iostream>
#include "point.h"

// renvoie 1, -1 ou 0 selon que le point auquel la m�thode est appliqu�e est
// � gauche de, � droite de, ou sur la droite (ab) orient�e de a vers b.
int Point::aGauche(const Point &a, const Point &b) const
{
    float crossProduct = (b.x() - a.x()) * (this->y() - a.y()) - (b.y() - a.y()) * (this->x() - a.x());

    if (crossProduct > 0) {
        return 1; // Le point est à gauche de la ligne
    } else if (crossProduct < 0) {
        return -1; // Le point est à droite de la ligne
    } else {
        return 0; // Le point est sur la ligne
    }
}

int Point::dansCercle(const Point &a, const Point &b, const Point &c) const {
    double mathA = a.x() - x();
    double mathB = a.y() - y();
    double mathC = mathA * mathA + mathB * mathB;
    double mathD = b.x() - x();
    double mathE = b.y() - y();
    double mathF = mathD * mathD + mathE * mathE;
    double mathG = c.x() - x();
    double mathH = c.y() - y();
    double mathI = mathG * mathG + mathH * mathH;

    double resultat = mathA * (mathE * mathI - mathF * mathH) + mathB * (mathF * mathG - mathD * mathI) + mathC * (mathD * mathH - mathE * mathG);

    return (resultat > 0) ? 1 : ((resultat < 0) ? -1 : 0);
}
