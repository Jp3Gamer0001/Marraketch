#include <iostream>
#include <cstdlib> // Para la función rand() y srand()
#include <ctime>   // Para la función time()
#include <cmath> 
using namespace std;

const int FILAS = 7;
const int COLUMNAS = 7;
const int NUM_ALFOMBRAS = 10;

// Definición de una estructura para representar el tablero
struct Tablero {
    char casillas[FILAS][COLUMNAS];
    string color ="\033[1;32m";
    string colorP1 ="\033[1;33m";
    string colorP2 ="\033[1;34m";
};

// Definición de una estructura para representar un personaje
struct Personaje {
    int fila;
    int columna;
    char icono;
    char vision; //hacia adonde assam està mirando
};

struct Alfombra {
    int fila;
    int columna;
    char orientacion; // 'h' para horizontal, 'v' para vertical
    bool colocada;
};

struct Jugador {
    string nombre;
    int monedasTotales;
    int alfombrasRestantes;
    Alfombra alfombras[NUM_ALFOMBRAS]; 
};

// Función para limpiar la terminal en Linux
void limpiarTerminal() {
    system("clear"); // Ejecutar el comando clear en la terminal
}

void inicializarTablero(Tablero &tablero) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            tablero.casillas[i][j] = 'O';
        }
    }
}

void mostrarTurno(bool &a, Jugador jugadores[]){
    if(a==false){
        cout<<"Turno del jugador "<<jugadores[0].nombre<<":"<<endl<<endl;
    }else{
        cout<<"Turno del jugador "<<jugadores[1].nombre<<":"<<endl<<endl;
    }
}

// Función para mostrar el tablero con Assam
void mostrarTableroConPersonaje(const Tablero &tablero, const Personaje &personaje, bool &a, Jugador jugadores[]) {
    mostrarTurno(a, jugadores);

    // Mostrar monedas de cada jugador
    cout << "Monedas del jugador " << jugadores[0].nombre << ": " << jugadores[0].monedasTotales << endl;
    cout << "Monedas del jugador " << jugadores[1].nombre << ": " << jugadores[1].monedasTotales << endl;

    // Mostrar números de columnas
    cout << "    "; // Espacio para el número de filas
    for (int j = 0; j < COLUMNAS; ++j) {
        cout << "  " << j << "  ";
    }
    cout << endl;

    for (int i = 0; i < FILAS; ++i) {
        cout << " " << i << " "; // Mostrar el número de fila
        for (int j = 0; j < COLUMNAS; ++j) {
            if (i == personaje.fila && j == personaje.columna) {
                cout << "[" ;
                // Mostrar la dirección en la que Assam está mirando
                switch (personaje.vision) {
                    case 'w':
                        cout <<" "<<personaje.icono << "^";
                        break;
                    case 's':
                        cout << " v"<<personaje.icono;
                        break;
                    case 'd':
                        cout <<personaje.icono << "> ";
                        break;
                    case 'a':
                        cout << " <"<<personaje.icono;
                        break;
                    default:
                        cout << " ? "; // Mostrar un carácter '?' si la dirección es desconocida
                        break;
                }
                cout << "]";
            } else {
                // Mostrar las casillas del tablero
                if (tablero.casillas[i][j] == jugadores[0].nombre[0]) {
                    cout << tablero.colorP1; // Cambiar color a amarillo (alfombras del jugador 1)
                } else if (tablero.casillas[i][j] == jugadores[1].nombre[0]) {
                    cout << tablero.colorP2; // Cambiar color a azul (alfombras del jugador 2)
                }
                cout << "[ " << tablero.casillas[i][j] << " ]"; // Mostrar la casilla del tablero
                cout << tablero.color; // Restaurar color por defecto
            }
        }
        cout << endl;
    }
}

char validarDireccionOpuesta(char vision) {
    char direccionOpuesta;
    switch (vision) {
        case 'w':
            direccionOpuesta = 's';
            break;
        case 's':
            direccionOpuesta = 'w';
            break;
        case 'd':
            direccionOpuesta = 'a';
            break;
        case 'a':
            direccionOpuesta = 'd';
            break;
        default:
            cout << "Error: Visión no válida." << endl;
            direccionOpuesta = 'z';
    }
    return direccionOpuesta;
}

void visionPersonaje(char &vision) {
    char direccionOpuesta;
    bool flag = false;
    char nuevaVision;

    do {
        direccionOpuesta = validarDireccionOpuesta(vision);
        cout << "Cambia hacia dónde Assam mira (w: arriba, a: izquierda, s: abajo, d: derecha): ";
        cin >> nuevaVision;

        if (direccionOpuesta == nuevaVision) {
            cout << "Assam no puede mirar hacia atrás" << endl;
        } else if ((nuevaVision == 'w' || nuevaVision == 's') || (nuevaVision == 'a' || nuevaVision == 'd') ) {
            flag = true;
        } else{
            cout << "Direccion no valida" << endl;
        }
    } while (!flag);

    vision = nuevaVision; // Actualizar la visión con la nueva dirección válida
}

// Función para mover al personaje en una dirección dada
void moverPersonaje(Personaje &personaje, int movimientos, char &vision) {
    while (movimientos > 0) {
        // Mover al personaje en la dirección dada
        switch (vision) {
            case 'W':
            case 'w':
                personaje.fila -= 1;
                break;
            case 'A':
            case 'a':
                personaje.columna -= 1;
                break;
            case 'S':
            case 's':
                personaje.fila += 1;
                break;
            case 'D':
            case 'd':
                personaje.columna += 1;
                break;
            default:
                cout << "Dirección no válida. Assam no se ha movido." << endl;
                return;
        }
        movimientos--;

        if (personaje.fila == 0 && personaje.columna < 0) {
            vision = 's';
            personaje.fila = 0;
            personaje.columna = 0;
        } else if (personaje.fila < 0 && personaje.columna == 0) {
            vision = 'd';
            personaje.fila = 0;
            personaje.columna = 0;
        } else if (personaje.fila == FILAS - 1 && personaje.columna >= COLUMNAS) {
            vision = 'w';
            personaje.fila = FILAS - 1;
            personaje.columna = COLUMNAS - 1;
        } else if (personaje.fila >= FILAS && personaje.columna == COLUMNAS - 1) {
            vision = 'a';
            personaje.fila = FILAS - 1;
            personaje.columna = COLUMNAS - 1;
        }

        // Ajustar la dirección si el personaje se sale del tablero
        if (personaje.fila < 0) {
            vision = 's';
            personaje.fila = 0;
            personaje.columna = (personaje.columna % 2 == 0) ? personaje.columna - 1 : personaje.columna + 1;
        } else if (personaje.fila >= FILAS) {
            vision = 'w';
            personaje.fila = FILAS - 1;
            personaje.columna = (personaje.columna % 2 == 0) ? personaje.columna + 1 : personaje.columna - 1;
        } else if (personaje.columna < 0) {
            vision = 'd';
            personaje.columna = 0;
            personaje.fila = (personaje.fila % 2 == 0) ? personaje.fila - 1 : personaje.fila + 1;
        } else if (personaje.columna >= COLUMNAS) {
            vision = 'a';
            personaje.columna = COLUMNAS - 1;
            personaje.fila = (personaje.fila % 2 == 0) ? personaje.fila + 1 : personaje.fila - 1;
        }


    }
}

void pedirJugadores(Jugador jugadores[]) {
    for (int i = 0; i < 2; i++) {
        cout << "Ingrese el nombre del jugador #" << (i + 1) << ": ";
        cin >> jugadores[i].nombre;
        jugadores[i].monedasTotales = 20; // Asignar 20 monedas a cada jugador
        jugadores[i].alfombrasRestantes = NUM_ALFOMBRAS;

        // Inicializar las alfombras del jugador
        for (int j = 0; j < NUM_ALFOMBRAS; ++j) {
            jugadores[i].alfombras[j].colocada = false;
        }
    }
}

void solicitarLanzarDado(Personaje &personaje) {
    char lanzarDado;
    bool a = false;
    do {
        cout << "Presiona 'L' para lanzar el dado: ";
        cin >> lanzarDado;

        if (lanzarDado == 'L' || lanzarDado == 'l') {
            int movimientos = rand() % 6 + 1; // Lanzar el dado (número aleatorio entre 1 y 6)
            cout << "Has lanzado un " << movimientos << ". " << endl;
            // Poner tiempo para visualizar el tablero y ver cuando se mueve y cuanto
            moverPersonaje(personaje, movimientos, personaje.vision);
            a = !a;
        } else {
            cout << "Entrada no válida. Presiona 'L' para lanzar." << endl;
        }
    } while (a == false);
}

bool pagarAOponente(Tablero& tablero, Jugador& jugadorActual, Jugador& oponente, int posx, int posy) {
    int costoTotal = 0;
    char simboloOponente = oponente.nombre[0];

    // Verificar si Assam está parado sobre una alfombra del oponente
    if (tablero.casillas[posx][posy] == simboloOponente) {
        costoTotal += 1;

        // Verificar alfombras adyacentes
        if (posx > 0 && tablero.casillas[posx - 1][posy] == simboloOponente) {
            costoTotal += 1;
        }
        if (posx < FILAS - 1 && tablero.casillas[posx + 1][posy] == simboloOponente) {
            costoTotal += 1;
        }
        if (posy > 0 && tablero.casillas[posx][posy - 1] == simboloOponente) {
            costoTotal += 1;
        }
        if (posy < COLUMNAS - 1 && tablero.casillas[posx][posy + 1] == simboloOponente) {
            costoTotal += 1;
        }

        // Realizar el pago
        if (jugadorActual.monedasTotales >= costoTotal) {
            jugadorActual.monedasTotales -= costoTotal;
            oponente.monedasTotales += costoTotal;
            cout << jugadorActual.nombre << " ha pagado " << costoTotal << " monedas a " << oponente.nombre << "." << endl;
            return true;
        } else {
            oponente.monedasTotales += jugadorActual.monedasTotales;
            jugadorActual.monedasTotales = 0;
            cout << jugadorActual.nombre << " no tiene suficientes monedas para pagar. ¡Ha perdido todas sus monedas!" << endl;
            return false;
        }
    }

    return true; // Si no está parado en una alfombra del oponente, no hay pago
}


// Función para poner una alfombra en el tablero
bool ponerAlfombra(Tablero &tablero, Alfombra alfombra, char jugador) {
    int fila = alfombra.fila;
    int columna = alfombra.columna;
    char orientacion = alfombra.orientacion;

    // Verificar si la posición está dentro del tablero
    if (fila < 0 || columna < 0 || fila >= FILAS || columna >= COLUMNAS) {
        cout << "Posición fuera del tablero." << endl;
        return false;
    }

    if (orientacion == 'h') { // Orientación horizontal
        if (columna + 1 >= COLUMNAS) {
            cout << "No se puede colocar la alfombra en esta posición." << endl;
            return false;
        }
        tablero.casillas[fila][columna] = jugador;
        tablero.casillas[fila][columna + 1] = jugador;
    } else if (orientacion == 'v') { // Orientación vertical
        if (fila + 1 >= FILAS) {
            cout << "No se puede colocar la alfombra en esta posición." << endl;
            return false;
        }
        tablero.casillas[fila][columna] = jugador;
        tablero.casillas[fila + 1][columna] = jugador;
    } else {
        cout << "Orientación no válida." << endl;
        return false;
    }

    return true;
}

// Función para colocar una alfombra en los lugares adyacentes al personaje
void colocarAlfombra(Tablero &tablero, Jugador &jugador, const Personaje &personaje) {
    if (jugador.alfombrasRestantes == 0) {
        cout << "No tienes alfombras disponibles." << endl;
        return;
    }

    char orientacion;
    int fila, columna;
    int alfombraDisponible = -1; // Índice de la primera alfombra disponible

    do {
        cout << "Ingrese la fila donde desea colocar la alfombra (0-6): ";
        cin >> fila;
        cout << "Ingrese la columna donde desea colocar la alfombra (0-6): ";
        cin >> columna;

        if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
            cout << "Posición fuera del tablero. Inténtalo de nuevo." << endl;
            continue;
        }

        // Verificar si la posición está adyacente al personaje
        if ((abs(fila - personaje.fila) > 1) || (abs(columna - personaje.columna) > 1)) {
            cout << "La alfombra solo se puede colocar en las casillas adyacentes al personaje. Inténtalo de nuevo." << endl;
            continue;
        }

        cout << "En qué dirección deseas colocar la alfombra (h: horizontal, v: vertical): ";
        cin >> orientacion;

        if (orientacion != 'h' && orientacion != 'v') {
            cout << "Orientación no válida. Inténtalo de nuevo." << endl;
            continue;
        }

        // Buscamos una alfombra disponible
        for (int i = 0; i < NUM_ALFOMBRAS; ++i) {
            if (!jugador.alfombras[i].colocada) {
                alfombraDisponible = i;
                break;
            }
        }

        if (alfombraDisponible == -1) {
            cout << "No tienes alfombras disponibles." << endl;
            return;
        }

        // Colocamos la alfombra en la posición deseada
        jugador.alfombras[alfombraDisponible].fila = fila;
        jugador.alfombras[alfombraDisponible].columna = columna;
        jugador.alfombras[alfombraDisponible].orientacion = orientacion;

        if (ponerAlfombra(tablero, jugador.alfombras[alfombraDisponible], jugador.nombre[0])) {
            jugador.alfombras[alfombraDisponible].colocada = true;
            jugador.alfombrasRestantes--;
            cout << "Alfombra colocada correctamente. Alfombras restantes: " << jugador.alfombrasRestantes << endl;
            return; // Salir del bucle
        } else {
            cout << "Error al colocar la alfombra. Inténtalo de nuevo." << endl;
        }
    } while (true);
}

int main() {
    srand(time(0)); // Inicializar la semilla del generador de números aleatorios

    Tablero tablero;
    Personaje personaje;
    Jugador jugadores[2];
    bool turno = false;

    // Inicializar el tablero y Assam
    inicializarTablero(tablero);
    personaje.fila = FILAS / 2;
    personaje.columna = COLUMNAS / 2;
    personaje.icono = 'H'; // Por ejemplo, 'H' para Assam
    personaje.vision = 'w'; // Establecer la dirección de visión de Assam al norte

    pedirJugadores(jugadores);

    // Bucle principal para permitir que el usuario se mueva por el tablero
    while (true) {
    limpiarTerminal(); // Limpiar la terminal antes de mostrar el tablero
    mostrarTableroConPersonaje(tablero, personaje, turno, jugadores); // Mostrar el tablero con Assam

    visionPersonaje(personaje.vision);

    limpiarTerminal();
    mostrarTableroConPersonaje(tablero, personaje, turno, jugadores);

    solicitarLanzarDado(personaje);

    limpiarTerminal();
    mostrarTableroConPersonaje(tablero, personaje, turno, jugadores);

    colocarAlfombra(tablero, jugadores[turno ? 1 : 0], personaje);

    int posx = personaje.fila;
    int posy = personaje.columna;
    if (!pagarAOponente(tablero, jugadores[turno ? 1 : 0], jugadores[turno ? 0 : 1], posx, posy)) {
        break; // Si un jugador no tiene suficientes monedas para pagar, terminar el juego
    }

    // Verificar si ambos jugadores ya no tienen alfombras disponibles
    if (jugadores[0].alfombrasRestantes == 0 && jugadores[1].alfombrasRestantes == 0) {
        break; // Si ambos jugadores no tienen alfombras disponibles, terminar el juego
    }

    turno = !turno; // Cambiar de turno
}


    return 0;
}