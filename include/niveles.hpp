#pragma once

#include "../include/datanivel.hpp"
#include <vector>

class Niveles {
    public:
        Niveles();

        const grillaNivel& getNivel(int indice) const;

        int getCantidad() const { 
        return grillas.size(); 
    }

    private:
        std::vector<grillaNivel> grillas;
};