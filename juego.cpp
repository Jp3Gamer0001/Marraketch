#include <iostream>
#include <cstdlib> // Para la función rand() y srand()
#include <ctime>   // Para la función time()
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
    char vision; //hacia adonde assam està mirando
};

struct Alfombra {
    int fila;
    int columna;
    char propietario; // Por ejemplo, '1' para jugador 1 y '2' para jugador 2
};

struct Jugador {
    string nombre;
    Alfombra alfombras[8];
    int monedasTotales;
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

// Función para mostrar el tablero con assam
void mostrarTableroConPersonaje(const Tablero &tablero, const Personaje &personaje, bool &a, Jugador jugadores[]) {
    mostrarTurno(a, jugadores);
    for (int i = 0; i < FILAS; ++i) {
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
                cout << "[ " << tablero.casillas[i][j] << " ]"; // Mostrar la casilla del tablero
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
        } else if ((nuevaVision == 'w' || nuevaVision == 's')||(nuevaVision == 'a' || nuevaVision == 'd') ) {
            flag = true;
        } else{
            cout << "Direccion no valida" << endl;
        }
    } while (!flag);

    vision = nuevaVision; // Actualizar la visión con la nueva dirección válida

}


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
        jugadores[i].monedasTotales = 8; // Asignar 8 monedas a cada jugador
    }    
}

void solicitarLanzarDado(Personaje &personaje) {
    char lanzarDado;
    bool a=false;
    do{
    cout << "Presiona 'L' para lanzar el dado: ";
    cin >> lanzarDado;

    if (lanzarDado == 'L' || lanzarDado == 'l') {
        int movimientos = rand() % 6 + 1; // Lanzar el dado (número aleatorio entre 1 y 6)
        cout << "Has lanzado un " << movimientos << ". " << endl;
        // Poner tiempo para visualizar el tablero y ver cuando se mueve y cuanto
        moverPersonaje(personaje, movimientos, personaje.vision);
        a=!a;
    } else {
        cout << "Entrada no válida. Presiona 'L' para lanzar." << endl;
    }
    }while(a==false);
    
}

int main() {
    srand(time(0)); // Inicializar la semilla del generador de números aleatorios

    Tablero tablero;
    Personaje personaje;
    Jugador jugadores[2];
    bool turno;

    // Inicializar el tablero y Assam
    inicializarTablero(tablero);
    personaje.fila = FILAS / 2;
    personaje.columna = COLUMNAS / 2;
    personaje.icono = 'H'; // Por ejemplo, 'H' para Assam
    personaje.vision = 'w'; // Establecer la dirección de visión de Assam al norte

    char lanzarDado;
    bool salir = false;
    char direccion;
    pedirJugadores(jugadores);
    // Bucle principal para permitir que el usuario se mueva por el tablero
    while (!salir) {
        
        limpiarTerminal(); // Limpiar la terminal antes de mostrar el tablero
        // Mostrar el tablero con Assam
        mostrarTableroConPersonaje(tablero, personaje, turno, jugadores);
        visionPersonaje(personaje.vision);
        limpiarTerminal();
        mostrarTableroConPersonaje(tablero,personaje, turno, jugadores);
        solicitarLanzarDado(personaje);
        turno = !turno;
    }

    return 0;
} /*arreglar bugs, no despliega varios cout, ya que limpia la terminal muy rapido. Ademas el juego solo permite que assam se mueva en linea recta, toca hacer otra funcion para que assam mire y revisar el codigo*/

