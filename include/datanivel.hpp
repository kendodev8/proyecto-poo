#pragma once
#include <array>

constexpr int ANCHO_MAX = 12;
constexpr int ALTO_MAX = 12;
constexpr float TAMAÑO_TILE = 32.f;

const int PISO = 0;
const int FONDO = 1;
const int PARED = 2;
const int CAJA = 3;
const int BOTON = 4;
const int CAJAOBJETIVO = 5;

using grillaNivel = std::array<std::array<int, ALTO_MAX>, ANCHO_MAX>;