#include "../include/scoremanager.hpp"
#include <cstring>

ScoreManager::ScoreManager(){

}

void ScoreManager::setScore(const int &nivel, const int &movimientos, const std::string &nombre){
    score temp;
    temp.nivel = nivel;
    temp.movimientos = movimientos;

    std::strncpy(temp.nombre, nombre.c_str(), 3);
    temp.nombre[3] = '\0';

    std::ofstream archivo(rutaArchivo, std::ios::binary | std::ios::app);

    if(!archivo) return;

    archivo.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
}

std::vector<score> ScoreManager::getScores(){
    std::vector<score> scores;
    std::ifstream archivo(rutaArchivo, std::ios::binary);

    if(!archivo) return scores;

    score temp;
    
    while(archivo.read(reinterpret_cast<char*>(&temp), sizeof(score))){
        scores.push_back(temp);
    }

    return scores;
}