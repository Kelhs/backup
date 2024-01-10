#include <iostream>
#include <vector>
#include <random>
#include <iostream>

void algoRandom(int nombreDeGenes, int taillePopulation){
    srand(time(0));
    // Initialisation du générateur
    std::random_device rd;
    std::mt19937 gen(rd());

    // Définition de la distribution
    std::uniform_int_distribution<> dis(0, 1);

    std::vector<std::vector<int>> pop;
    //Initialisation de la population
    for(int i = 0; i < taillePopulation; i++) {
        std::vector<int> cards;
        pop.push_back(cards);
        for(int j = 0; j < nombreDeGenes; j++) {

            // Génération du nombre aléatoire
            int randomNum = dis(gen);
            pop[i].push_back(randomNum);
        }
    }

    int count = 0;

    while(count != 100){
        count++;
        bool resultFound = false;
        for(auto& individu: pop){
            int somme = 0;
            int produit = 0;

            for(int i = 0; i < 10; i++){
                if(individu[i] == 0){
                    somme += i + 1;
                }
                if(individu[i] == 1){
                    if(produit == 0){
                        produit = i + 1;
                    } else {
                        produit = produit * (i + 1);
                    }
                }
            }
            if(abs(somme - 36) + abs(produit - 360) == 0){
                std::cout << "__________________RESULTAT___________________" << std::endl;
                std::cout << "||" << individu[0] << "|" << individu[1] << "|" << individu[2] << "|" << individu[3] << "|" << individu[4] << "|" << individu[5] << "|" << individu[6] << "|" << individu[7] << "|" << individu[8] << "|" << individu[9] << "||"<< std::endl;
                std::cout << "__________________Nombre d'itération: " << count << "___________________" << std::endl;

                resultFound = true;
                break;
            }
        }

        if(resultFound){
            break;
        }

        for(int i = 0; i < taillePopulation; i++){
            std::cout << "_____________________________________" << std::endl;
            std::cout << "Parent 1 : " << "||" << pop[i][0] << "|" << pop[i][1] << "|" << pop[i][2] << "|" << pop[i][3] << "|" << pop[i][4] << "|" << pop[i][5] << "|" << pop[i][6] << "|" << pop[i][7] << "|" << pop[i][8] << "|" << pop[i][9] << "||"<< std::endl;

            int indexParent2 = rand() % pop.size();
            while(indexParent2 == i){
                indexParent2 = rand() % pop.size();
            }

            int randomReproduction = rand() % 100;

            if(randomReproduction < 75){
                std::cout << "Parent 2 : " << "||" << pop[indexParent2][0] << "|" << pop[indexParent2][1] << "|" << pop[indexParent2][2] << "|" << pop[indexParent2][3] << "|" << pop[indexParent2][4] << "|" << pop[indexParent2][5] << "|" << pop[indexParent2][6] << "|" << pop[indexParent2][7] << "|" << pop[indexParent2][8] << "|" << pop[indexParent2][9] << "||"<< std::endl;

                for(int j = 0; j < 3; j++){
                    pop[i][j] = pop[indexParent2][j];
                }
                for(int k = pop[i].size() - 3; k < pop[i].size(); k++){
                    pop[i][k] = pop[indexParent2][k];

                }

            }

            int randomMutation = rand() % 100;
            if(randomMutation < 10){
                int indexMutation = rand() % nombreDeGenes;
                if(pop[i][indexMutation] == 0){
                    pop[i][indexMutation] = 1;
                } else {
                    pop[i][indexMutation] = 0;
                }
            }
            std::cout << "Enfant : " << "||" << pop[i][0] << "|" << pop[i][1] << "|" << pop[i][2] << "|" << pop[i][3] << "|" << pop[i][4] << "|" << pop[i][5] << "|" << pop[i][6] << "|" << pop[i][7] << "|" << pop[i][8] << "|" << pop[i][9] << "||"<< std::endl;
            std::cout << "_____________________________________" << std::endl;

        }
    }
}

int main() {
    algoRandom(10, 100);
    return 0;
}
