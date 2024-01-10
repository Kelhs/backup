#include "polygone.h"
#include "point.h"

using namespace std;

// Impl�mentation des m�thodes de la classe Polygone

// destructeur
Polygone::~Polygone()
{
}

// Ajoute un nouveau sommet au polygone. Les coordonn�es du sommet � ajouter sont celles du point p.
// sommetPrecedent est soit un pointeur sur l�un des sommets d�j� pr�sents dans le polygone, 
// soit un pointeur nul si le polygone est vide.
// Dans le premier cas, le nouveau sommet devient le successeur du sommet d�adresse sommetPrecedent.
// Dans le deuxi�me cas, le nouveau sommet devient l�unique sommet du polygone.
// Dans tous les cas, la m�thode renvoie l�adresse du nouveau sommet.
Sommet* Polygone::ajouteSommet(const Point &p, Sommet* sommetPrecedent)
{	
	Sommet* s = new Sommet(p);

	if(sommetPrecedent == nullptr){
        s->d_suivant = s;
        s->d_precedent = s;
        d_premier = s;
	} else {

        // Insérer le nouveau sommet après sommetPrecedent
        s->d_precedent = sommetPrecedent;
        s->d_suivant = sommetPrecedent->d_suivant;

        // Mise à jour des liens du sommet précédent et du suivant
        sommetPrecedent->d_suivant->d_precedent = s;
        sommetPrecedent->d_suivant = s;
	}
	
	return s;
}


// Supprime le sommet d�adresse s du polygone.
// On suppose que s est effectivement pr�sent dans le polygone.
void Polygone::supprimeSommet(Sommet* s)
{
    if (s == nullptr) {
        return;
    }

    // Gérer le cas d'un polygone à un seul sommet
    if (s->d_precedent == s && s->d_suivant == s) {
        // Si s est le seul sommet du polygone, il n'y a pas de mise à jour de liens à faire.
    } else {
        s->d_precedent->d_suivant = s->d_suivant;
        s->d_suivant->d_precedent = s->d_precedent;
    }
    delete s;
}





