#include <SFML/Graphics.hpp>

constexpr int ANCHO_MAX = 4;
constexpr int ALTO_MAX = 4;
constexpr float TAMAÑO_TILE = 32.f;


class Mapa {
    private: 
        int mapa[ANCHO_MAX][ALTO_MAX];
        
    public:
        Mapa();

        void cargarNivel(int nivel[ANCHO_MAX][ALTO_MAX]);
        void renderizar(sf::RenderWindow& ventana);
};