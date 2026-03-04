# 🧩 Proyecto Final POO - Sokoban

Juego desarrollado en C++ utilizando la libreria SFML como proyecto para la materia Programación Orientada a Objetos.

El objetivo del juego es resolver puzzles empujando cajas hacia puntos específicos para progresar de nivel.

## 🛠️ Tecnologias

- C++
- SFML
- CMake
- Git

## Controles

- W / ↑ : mover hacia arriba
- A / ← : mover hacia la izquierda
- S / ↓ : mover hacia abajo
- D / → : mover hacia la derecha
- Z : deshacer un movimiento
- R : reiniciar el nivel

## Compilación (Linux)

```bash
mkdir build
cd build
cmake ..
make
./sokoban
```

## Compilación (Windows)

```bash
g++ -c ".\src\*.cpp" -I"rutaSFML\include"
g++ *.o -o sokoban -L"rutaSFML\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
.\sokoban.exe
```

## 👥 Integrantes

- [Kevin](https://github.com/kendodev8)
- [Namir](https://github.com/NamirGareis)
