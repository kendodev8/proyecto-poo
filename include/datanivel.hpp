#pragma once
#include <array>

constexpr int ANCHO_MAX = 12;
constexpr int ALTO_MAX = 12;
constexpr float TAMAÑO_TILE = 32.f;

using grillaNivel = std::array<std::array<int, ALTO_MAX>, ANCHO_MAX>;