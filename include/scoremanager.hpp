#pragma once
#include <fstream>
#include <vector>

struct score {
    int nivel;
    int movimientos;
    char nombre[4];
};

class ScoreManager {
    public:
        ScoreManager();
        void setScore(const int &nivel, const int &movimientos, const std::string &nombre);
        std::vector<score> getScores();
    
    private:
        std::string rutaArchivo = "scores.dat";
};