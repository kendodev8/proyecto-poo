#pragma once
#include "../include/datanivel.hpp"
#include <vector>

//Para respetar el principio de responsabilidad única, esta clase se encarga exclusivamente de manejar los niveles del juego,
//almacenando las grillas correspondientes a cada nivel y proporcionando métodos para acceder a ellas

class Niveles {
    public:
        Niveles();

        const grillaNivel& getNivel(int indice) const; //solo de lectura 

        int getCantidad() const { 
        return grillas.size(); 
    }

    private:
        std::vector<grillaNivel> grillas; //no es un arreglo estatico por si maniana quiero sumar mas lvls
};