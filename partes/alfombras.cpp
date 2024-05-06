#include <iostream>
using namespace std;

const int FILAS = 7;
const int COLUMNAS = 7;

// Estructura para representar una casilla del tablero
struct Casilla {
    bool ocupada;
    char jugador;
};

// Definición de una estructura para representar el tablero
struct Tablero {
    Casilla casillas[FILAS][COLUMNAS];
};

// Función para inicializar el tablero con casillas vacías
void inicializarTablero(Tablero &tablero) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            tablero.casillas[i][j].ocupada = false;
            tablero.casillas[i][j].jugador = '-';
        }
    }
}

// Función para mostrar el tablero con las alfombras
void mostrarTablero(const Tablero &tablero) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            if (tablero.casillas[i][j].ocupada) {
                cout << tablero.casillas[i][j].jugador << " ";
            } else {
                cout << "O ";
            }
        }
        cout << endl;
    }
}

// Función para colocar una alfombra en el tablero
bool colocarAlfombra(Tablero &tablero, int fila, int columna, char jugador) {
    // Verificar si las dos casillas que ocuparía la alfombra están disponibles
    if (fila < FILAS && columna < COLUMNAS - 1 && !tablero.casillas[fila][columna].ocupada && !tablero.casillas[fila][columna + 1].ocupada) {
        // Colocar la alfombra
        tablero.casillas[fila][columna].ocupada = true;
        tablero.casillas[fila][columna + 1].ocupada = true;
        tablero.casillas[fila][columna].jugador = jugador;
        tablero.casillas[fila][columna + 1].jugador = jugador;
        return true;
    } else {
        cout << "No se puede colocar la alfombra en esa posición." << endl;
        return false;
    }
}

int main() {
    Tablero tablero;
    inicializarTablero(tablero);

    // Ejemplo de colocar una alfombra por el jugador 'A' en la fila 2, columnas 3 y 4
    colocarAlfombra(tablero, 2, 3, 'A');

    // Mostrar el tablero después de colocar la alfombra
    mostrarTablero(tablero);

    return 0;
}
