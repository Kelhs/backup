//
// Created by kelvin on 14/11/23.
//

#include <SDL2/SDL.h>
#include "affichage.h"
#include "point.h"
#include "carte.h"

#include <iostream>
#include <algorithm>
#include <fstream>

bool Xcompare(const Point& p1, const Point& p2) {
    return p1.x() < p2.x() || (p1.x() == p2.x() && p1.y() > p2.y());
}

void triangulations(vector<Point> &T, Carte &C){

    DemiCote* dc = C.ajouteCote(T[0], T[1]);
    C.changeDemiCoteParticulier(dc);

    for(int i = 2; i < T.size(); i++){
        DemiCote* dc2 = C.ajouteCote(T[i], dc);
        while(T[i].aGauche( dc->coordonnees(), dc->suivant()->suivant()->oppose()->coordonnees()) == -1){
            dc = dc->suivant()->suivant()->oppose();
            C.ajouteCote(dc, dc2);
        };

        dc = dc2->oppose()->precedent();

        while(T[i].aGauche(dc->oppose()->coordonnees(), dc->coordonnees()) == -1){
            dc = dc->oppose()->precedent();
            dc2 = C.ajouteCote(dc2, dc);
        };

        dc = dc2;
    }

}

void creerFichierOBJ(Carte& carte, const std::vector<Point>& points, const std::string& nomFichier) {
    std::ofstream out(nomFichier);
    if (!out.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier pour écrire" << std::endl;
        return;
    }

    // Écrire les sommets (points)
    for (const auto& point : points) {
        out << "v " << point.x() << " " << point.y() << " " << point.z() << "\n";
    }

    for (const auto& triangle : carte.getTriangles()) {
        out << "f " << std::get<0>(triangle) + 1 << " " << std::get<1>(triangle) + 1 << " " << std::get<2>(triangle) + 1 << "\n";
    }

    out.close();
}

int main(){

    SDL_Init(SDL_INIT_VIDEO);


    SDL_Window* window = SDL_CreateWindow("Algo géo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1800, 1100, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    std::ifstream file("/home/kelvin/Documents/cours/CarteCombinatoire/ile Saint Christophe.txt");
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier" << std::endl;
        return 1;
    }

    int nombre_de_points;
    file >> nombre_de_points;
    vector<Point> points;
    for (int i = 0; i < nombre_de_points; ++i) {
        double x, y, z;
        file >> x >> y >> z; // Lire les coordonnées
        points.push_back(Point(x/22, 1100 - y/22, z)); // Stocker seulement x et y
    }


    std::sort(points.begin(), points.end(), Xcompare);

    Carte c;

    triangulations(points, c);

    c.delaunay();

    creerFichierOBJ(c, points, "/home/kelvin/Documents/cours/CarteCombinatoire/ileOBJ.obj");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    trace(c, renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(500000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}