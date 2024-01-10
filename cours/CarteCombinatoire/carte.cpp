

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

void Carte::flip(DemiCote* d) {
    flipDemiCote(d);
    flipDemiCote(d->oppose());
}

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

void Carte::delaunay() {
    stack<DemiCote*> pile;

    // Initialisation des côtés externes
    DemiCote* dcPart = this->demiCoteParticulier();
    do {
        dcPart->changeMarque(1);
        dcPart->oppose()->changeMarque(1);
        dcPart = dcPart->oppose()->suivant();
    } while (dcPart != this->demiCoteParticulier());

    // Ajout des côtés non externes à la pile
    for (int i = 0; i < this->nbDemiCotes(); i++) {
        DemiCote* dc = this->demiCote(i);
        if (dc->marque() != 1) {
            dc->changeMarque(1);
            dc->oppose()->changeMarque(1);
            pile.push(this->demiCote(i));
        }
    }
    //Tant que la pile n'est pas vide
    while (!pile.empty()) {
        //Récupère le premier demi côté de la pile
        DemiCote* currentDc = pile.top();
        //Enlève le demi côté de la pile
        pile.pop();
        //Supprime la marque du demi coté et de son opposé
        currentDc->changeMarque(0);
        currentDc->oppose()->changeMarque(0);

        //Verifie si le point du coté precedent/opposé au demi coté courrant est dans le cercle
        if (currentDc->precedent()->oppose()->sommet()->coordonnees().dansCercle(currentDc->coordonnees(), currentDc->suivant()->oppose()->coordonnees(), currentDc->oppose()->coordonnees()) < 0) {
            //Ajoute les cotés adjacent au point traité à la pile car leur etat a pu changer
            for (auto nearDc : { currentDc->oppose()->precedent(), currentDc->oppose()->suivant(), currentDc->precedent(), currentDc->suivant() }) {
                if (nearDc->marque() == 0) {
                    nearDc->changeMarque(1);
                    nearDc->oppose()->changeMarque(1);
                    pile.push(nearDc);
                }
            }
            //effectu le flip
            flip(currentDc);
        }
    }
}

std::set<TriangleIndices, TriangleCompare> Carte::getTriangles() {
    std::set<TriangleIndices, TriangleCompare> triangles;

    for (const DemiCote* dc : d_tabDemiCotes) {
        int index1 = dc->sommet()->index();
        int index2 = dc->precedent()->oppose()->sommet()->index();
        int index3 = dc->precedent()->oppose()->precedent()->oppose()->sommet()->index();

        TriangleIndices triangle = std::make_tuple(index1, index2, index3);
        triangles.insert(triangle);
    }

    return triangles;
}
