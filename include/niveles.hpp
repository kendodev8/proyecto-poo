#pragma once

#include "../include/datanivel.hpp"
#include <vector>

class Niveles {
    public:
        Niveles();

        const grillaNivel& getNivel(int indice) const;

    private:
        std::vector<grillaNivel> grillas;
};