

using namespace std;
#include <vector>
#include <stack>
#include <set>
#include <tuple>
#include <iostream>
#include "carte.h"
#include "point.h"

typedef std::tuple<int, int, int> TriangleIndices;


// Destructeur
Carte::~Carte()
{
    for(DemiCote* dc: d_tabDemiCotes){
        delete dc;
    }

    for(Sommet* s: d_tabSommets){
        delete s;
    }
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2
// dont precedent1 et precedent2 seront les demi-c�t�s pr�c�dents respectifs.
// On suppose precedent1 et precedent2 d�j� pr�sents dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(DemiCote* precedent1, DemiCote* precedent2)
{
    DemiCote* dc1 = ajouteDemiCote(precedent1, nullptr);
    DemiCote* dc2 = ajouteDemiCote(precedent2, dc1);
	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// precedent1 sera le demi-c�t� pr�c�dent de dc1. dc2 sera issu d�un
// nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p2.
// On suppose precedent1 d�j� pr�sent dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(DemiCote* precedent1, const Point& p2)
{
    DemiCote* dc1 = ajouteDemiCote(precedent1, nullptr);
    DemiCote* dc2 = ajouteDemiCote(p2, dc1);
	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// precedent2 sera le demi-c�t� pr�c�dent de dc2. dc1 sera issu d�un
// nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p1.
// On suppose precedent2 d�j� pr�sent dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(const Point& p1, DemiCote* precedent2)
{
    DemiCote* dc2 = ajouteDemiCote(precedent2, nullptr);
    DemiCote* dc1 = ajouteDemiCote(p1, dc2);
	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// dc1 et dc2 seront issus de deux nouveaux sommets (� cr�er) dont les
// coordonn�es sont celles des points p1 et p2 respectivement.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(const Point& p1, const Point& p2)
{
    DemiCote* dc1 = ajouteDemiCote(p1, nullptr);
    DemiCote* dc2 = ajouteDemiCote(p2, dc1);
	return dc1;
}

// Ajoute un nouveau demi-c�t� dans la carte dont precedent sera le demi-c�t�
// 	pr�c�dent et oppose sera le demi-c�t� oppos�.
// On suppose que le demi-c�t� precedent est d�j� pr�sent dans la carte.
// Le demi-c�t� oppose est soit d�j� pr�sent dans la carte soit nul (valeur
// par d�faut).
// Renvoie l�adresse du nouveau demi-c�t�.
DemiCote* Carte::ajouteDemiCote(DemiCote* precedent, DemiCote* oppose)
{
    DemiCote* dc = new DemiCote(precedent->suivant(), precedent, oppose, precedent->sommet(), d_tabDemiCotes.size());
    dc->coordonnees() = precedent->coordonnees();
    precedent->d_suivant = dc;
    dc->suivant()->d_precedent = dc;
    d_tabDemiCotes.push_back(dc);
    if(oppose != nullptr){
        oppose->d_oppose = dc;
    }
	return dc;
}

// Ajoute un nouveau demi-c�t� dans la carte qui sera issu d�un nouveau
// sommet (� cr�er) dont les coordonn�es sont celles du point p.
// oppose sera le demi-c�t� oppos� du nouveau demi-c�t�.
// oppose est soit d�j� pr�sent dans la carte soit nul (valeur par d�faut).
// Renvoie l�adresse du nouveau demi-c�t�.
DemiCote* Carte::ajouteDemiCote(const Point &p, DemiCote* oppose)
{
    DemiCote* dc = new DemiCote(nullptr, nullptr, oppose, nullptr, d_tabDemiCotes.size());
    d_tabDemiCotes.push_back(dc);
    Sommet* s = new Sommet(p, dc, d_tabSommets.size());
    d_tabSommets.push_back(s);
    dc->d_precedent = dc;
    dc->d_suivant = dc;
    dc->d_sommet = s;
    if(oppose != nullptr){
        oppose->d_oppose = dc;
    }
	return dc;
}

/*void Carte::flip(DemiCote *dc){
    DemiCote* dcOppose = dc->oppose();

    dc->precedent()->d_suivant = dc->suivant();
    dc->suivant()->d_precedent = dc->precedent();

    dc->coordonnees() = dc->suivant()->oppose()->coordonnees();
    dc->d_suivant = dc->suivant()->oppose()->suivant();
    dc->d_precedent = dc->suivant()->precedent();
    dc->d_sommet = dc->precedent()->sommet();

    dc->precedent()->d_suivant = dc;
    dc->suivant()->d_precedent = dc;

    dcOppose->precedent()->d_suivant = dcOppose->d_suivant;
    dcOppose->suivant()->d_precedent = dcOppose->d_precedent;

    dcOppose->coordonnees() = dcOppose->suivant()->oppose()->coordonnees();
    dcOppose->d_suivant =  dcOppose->suivant()->oppose()->suivant();
    dcOppose->d_precedent = dcOppose->suivant()->precedent();
    dc->d_sommet = dc->precedent()->sommet();

    dcOppose->precedent()->d_suivant = dcOppose;
    dcOppose->suivant()->d_precedent = dcOppose;
}*/
/**
 * Flip le DemiCote d et son opposé.
 * @param d {DemiCote} DemiCote d.
 */
void Carte::flip(DemiCote* d) {
    flipDemiCote(d);
    flipDemiCote(d->oppose());
}

/**
 * Flip le DemiCote d.
 * @param d {DemiCote} DemiCote d.
 */
void Carte::flipDemiCote(DemiCote* d) {
    auto demiCoteDepart = d->suivant()->oppose();

    if (d->d_sommet->demiCote() == d) {
        d->d_sommet->d_demiCote = d->suivant();
    }

    d->precedent()->d_suivant = d->suivant();
    d->suivant()->d_precedent = d->precedent();
    d->d_suivant = demiCoteDepart->suivant();
    d->d_precedent = demiCoteDepart;
    d->suivant()->d_precedent = d;
    d->precedent()->d_suivant = d;

    d->d_sommet = demiCoteDepart->sommet();
}

int estIllegal(DemiCote* dc){
    Point currentPoint = dc->precedent()->oppose()->coordonnees();
    Point a = dc->coordonnees();
    Point b = dc->suivant()->oppose()->coordonnees();
    Point c = dc->oppose()->coordonnees();

    return currentPoint.dansCercle(a, b, c);
}

void Carte::delaunay() {
    /*std::stack<DemiCote*> pile;
    //Marque les cotés exterieurs

    DemiCote* dcExt = this->demiCoteParticulier();
    std::cout << d_tabDemiCotes.size() << std::endl;

    do {
        dcExt->changeMarque(1);
        dcExt->oppose()->changeMarque(1);
        dcExt = dcExt->oppose()->suivant();
    } while(dcExt != this->demiCoteParticulier());
    for(auto dc: d_tabDemiCotes){

        if(dc->marque() != 1){
            dc->changeMarque(1);
            dc->oppose()->changeMarque(1);
            pile.push(dc);
        }
    }

    do{

        DemiCote* dc = pile.top();
        pile.pop();
        std::cout << pile.size() << std::endl;

        dc->changeMarque(0);
        dc->oppose()->changeMarque(0);

        if(estIllegal(dc) != -1){

            for (auto dcVoisin : { dc->oppose()->precedent(), dc->oppose()->suivant(), dc->precedent(), dc->suivant() }) {
                if (dcVoisin->marque() == 0) {
                    dcVoisin->changeMarque(1);
                    dcVoisin->oppose()->changeMarque(1);
                    pile.push(dcVoisin);
                }
            }
            flip(dc);
        }
    } while(!pile.empty());*/
    const int nbDemiCotes = this->nbDemiCotes();
    stack<DemiCote*> currentGlobal;

    // Marque les demi côtés exterieurs
    DemiCote* loopCote = this->demiCoteParticulier();
    do {
        loopCote->changeMarque(1);
        loopCote->oppose()->changeMarque(1);
        loopCote = loopCote->oppose()->suivant();
    } while (loopCote != this->demiCoteParticulier());

    // Ajoute les demi côtés non marqués à la pile
    for (int i = 0; i < nbDemiCotes; i++) {
        DemiCote* currentDemiCote = this->demiCote(i);
        if (currentDemiCote->marque() != 1) {
            currentDemiCote->changeMarque(1);
            currentDemiCote->oppose()->changeMarque(1);
            currentGlobal.push(this->demiCote(i));
        }
    }

    while (!currentGlobal.empty()) {
        DemiCote* demiCoteTraited = currentGlobal.top();
        currentGlobal.pop();
        demiCoteTraited->changeMarque(0);
        demiCoteTraited->oppose()->changeMarque(0);
        Sommet* first = demiCoteTraited->precedent()->oppose()->sommet();
        float insideCircle = first->coordonnees().dansCercle(demiCoteTraited->coordonnees(), demiCoteTraited->suivant()->oppose()->coordonnees(), demiCoteTraited->oppose()->coordonnees());

        if (insideCircle < 0) {
            for (auto neighbor : { demiCoteTraited->oppose()->precedent(), demiCoteTraited->oppose()->suivant(), demiCoteTraited->precedent(), demiCoteTraited->suivant() }) {
                if (neighbor->marque() == 0) {
                    neighbor->changeMarque(1);
                    neighbor->oppose()->changeMarque(1);
                    currentGlobal.push(neighbor);
                }
            }
            flip(demiCoteTraited);
        }
    }
}

std::set<TriangleIndices, TriangleCompare> Carte::getTriangles() {
    std::set<TriangleIndices, TriangleCompare> triangles;

    for (const DemiCote* dc : d_tabDemiCotes) {
        int index1 = dc->sommet()->index();
        int index2 = dc->suivant()->sommet()->index();
        int index3 = dc->suivant()->suivant()->sommet()->index();

        TriangleIndices triangle = std::make_tuple(index1, index2, index3);
        triangles.insert(triangle);
    }

    return triangles;
}
