#include "../include/juego.hpp"
#include "../include/menu.hpp"

int main() {
    Escena *principal = new Menu;
    Juego juego(principal);
    juego.run();
    return 0;
}