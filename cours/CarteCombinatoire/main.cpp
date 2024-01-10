//
// Created by kelvin on 14/11/23.
//
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include "affichage.h"
#include "point.h"
#include "carte.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

struct Vertex {
    double x, y, z;
};

struct Color {
    double r, g, b;
};

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

void mtlgeneration() {
    std::string inputFilename = "C:/Users/Kelvin Idesheim/Documents/Cours/backup/cours/CarteCombinatoire/ileOBJ.obj"; // Chemin du fichier OBJ d'entrée
    std::string outputFilename = "C:/Users/Kelvin Idesheim/Documents/Cours/backup/cours/CarteCombinatoire/ileColorOBJ.obj"; // Chemin du fichier OBJ de sortie
    std::string mtlFilename = "C:/Users/Kelvin Idesheim/Documents/Cours/backup/cours/CarteCombinatoire/colors.mtl"; // Chemin du fichier MTL

    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename);
    std::ofstream mtlFile(mtlFilename);

    std::string line;
    std::vector<Vertex> vertices;
    std::vector<Color> colors;

    // Lire le fichier OBJ et extraire les sommets
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        if (prefix == "v") {
            Vertex v;
            iss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
            Color color;

            // Calculer la couleur en fonction de Z
            if(v.z == 0){
                color.r = 0;
                color.g = 191;
                color.b = 255;
            } else if(v.z < 20) {
                color.r = 255;
                color.g = 250;
                color.b = 205;
            } else if(v.z < 40){
                color.r = 154;
                color.g = 205;
                color.b = 50;
            } else if (v.z < 80){
                color.r = 205;
                color.g = 133;
                color.b = 63;
            } else {
                color.r = 240;
                color.g = 248;
                color.b = 255;
            }

            colors.push_back(color);
            outputFile << line << std::endl;
        }
            // Écrire d'autres lignes directement dans le nouveau fichier OBJ
        else {
            outputFile << line << std::endl;
        }
    }

    // Écrire les définitions de matériaux dans le fichier MTL
    for (size_t i = 0; i < colors.size(); ++i) {
        mtlFile << "newmtl material" << i << std::endl;
        mtlFile << "Kd " << colors[i].r << " " << colors[i].g << " " << colors[i].b << std::endl;
    }

    // Référencer le fichier MTL dans le fichier OBJ
    outputFile << "mtllib " << mtlFilename << std::endl;

    // Écrire les sommets et leurs matériaux dans le fichier OBJ
    for (size_t i = 0; i < vertices.size(); ++i) {
        outputFile << "usemtl material" << i << std::endl;
        outputFile << "v " << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << std::endl;
    }

    inputFile.close();
    outputFile.close();
    mtlFile.close();
}

int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Algo géo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1800, 1100, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    std::ifstream file("C:/Users/Kelvin Idesheim/Documents/Cours/backup/cours/CarteCombinatoire/ile Saint Christophe.txt");
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
        points.push_back(Point(x, y, z));
    }

    std::sort(points.begin(), points.end(), Xcompare);

    Carte c;

    triangulations(points, c);

    c.delaunay();

    creerFichierOBJ(c, points, "C:/Users/Kelvin Idesheim/Documents/Cours/backup/cours/CarteCombinatoire/ileOBJ.obj");
    mtlgeneration();
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