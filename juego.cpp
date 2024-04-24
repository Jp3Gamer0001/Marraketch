#include <iostream>
#include <cstdlib> // Para la función rand() y srand()
#include <ctime> // Para la función time()
using namespace std;

const int FILAS = 7;
const int COLUMNAS = 7;

// Definición de una estructura para representar el tablero
struct Tablero {
    char casillas[FILAS][COLUMNAS];
};

// Definición de una estructura para representar un personaje
struct Personaje {
    int fila;
    int columna;
    char icono;
};

// Función para limpiar la terminal en Linux
void limpiarTerminal() {
    system("clear"); // Ejecutar el comando clear en la terminal
}

// Función para inicializar el tablero con casillas blancas y negras
void inicializarTablero(Tablero &tablero) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j){
                tablero.casillas[i][j] = 'O';
        }
    }
}

// Función para mostrar el tablero con el personaje
void mostrarTableroConPersonaje(const Tablero &tablero, const Personaje &personaje) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            if (i == personaje.fila && j == personaje.columna) {
                cout << personaje.icono << " "; // Mostrar el personaje en su posición
            } else {
                cout << tablero.casillas[i][j] << " "; // Mostrar la casilla del tablero
            }
        }
        cout << endl;
    }
}

int main() {
    srand(time(0)); // Inicializar la semilla del generador de números aleatorios

    Tablero tablero;
    Personaje personaje;

    // Inicializar el tablero y el personaje
    inicializarTablero(tablero);
    personaje.fila = FILAS / 2;
    personaje.columna = COLUMNAS / 2;
    personaje.icono = 'P'; // Por ejemplo, 'P' para el personaje

    char lanzarDado;
    bool salir = false;

    // Bucle principal para permitir que el usuario se mueva por el tablero
    while (!salir) {
        limpiarTerminal(); // Limpiar la terminal antes de mostrar el tablero

        // Mostrar el tablero con el personaje
        mostrarTableroConPersonaje(tablero, personaje);

        // Solicitar al usuario que lance el dado
        cout << "Presiona 'L' para lanzar el dado (o 'Q' para salir): ";
        cin >> lanzarDado;

        if (lanzarDado == 'Q' || lanzarDado == 'q') {
            salir = true;
        } else if (lanzarDado == 'L' || lanzarDado == 'l') {
            int movimientos = rand() % 6 + 1; // Lanzar el dado (número aleatorio entre 1 y 6)
            cout << "Has lanzado un " << movimientos << ". ";
            cout << "Elige en qué dirección deseas moverte (W: arriba, A: izquierda, S: abajo, D: derecha): ";
            char direccion;
            cin >> direccion;

            // Actualizar la posición del personaje según la dirección elegida
            switch (direccion) {
                case 'W':
                case 'w':
                    personaje.fila -= movimientos;
                    break;
                case 'A':
                case 'a':
                    personaje.columna -= movimientos;
                    break;
                case 'S':
                case 's':
                    personaje.fila += movimientos;
                    break;
                case 'D':
                case 'd':
                    personaje.columna += movimientos;
                    break;
                default:
                    cout << "Dirección no válida. El personaje no se ha movido." << endl;
            }

            // Mantener al personaje dentro del tablero
            if (personaje.fila < 0) personaje.fila = 0;
            if (personaje.fila >= FILAS) personaje.fila = FILAS - 1;
            if (personaje.columna < 0) personaje.columna = 0;
            if (personaje.columna >= COLUMNAS) personaje.columna = COLUMNAS - 1;
        } else {
            cout << "Entrada no válida. Presiona 'L' para lanzar el dado o 'Q' para salir." << endl;
        }
    }

    return 0;
}

