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

/*struct Jugador {
    string nombre;
    vector<Alfombra> alfombras;
    int monedasTotales;
};*/


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

// Función para mostrar el tablero con assam
void mostrarTableroConPersonaje(const Tablero &tablero, const Personaje &personaje) {
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            if (i == personaje.fila && j == personaje.columna) {
                cout << "[" ;
                // Mostrar la dirección en la que Assam está mirando
                switch (personaje.vision) {
                    case 'w':
                        cout << " ^ ";
                        break;
                    case 's':
                        cout << " v ";
                        break;
                    case 'd':
                        cout << " > ";
                        break;
                    case 'a':
                        cout << " < ";
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
            return false; // Salir de la función si la visión es inválida
    }

    return direccionOpuesta;
}

// Función para mover al personaje en una dirección dada
void moverPersonaje(Personaje &personaje, char direccion, int movimientos, char &vision) {
    // Determinar la dirección opuesta basada en la visión actual de Assam
    char direccionOpuesta;
    bool flag = false;
    char nuevaVision;

    do {
        direccionOpuesta = validarDireccionOpuesta(vision);
        cout << "Cambia hacia dónde Assam mira (w: arriba, a: izquierda, s: abajo, d: derecha): ";
        cin >> nuevaVision;

        if (direccionOpuesta == nuevaVision) {
            cout << "Assam no puede mirar hacia atrás" << endl;
        } else {
            flag = true;
        }
    } while (!flag);

    vision = nuevaVision; // Actualizar la visión con la nueva dirección válida
    direccionOpuesta = validarDireccionOpuesta(vision);

    do {
        cout << "Elige en qué dirección deseas moverte (w: arriba, a: izquierda, s: abajo, d: derecha): ";
        cin >> direccion;

        // Verificar si la dirección solicitada es la opuesta a la visión actual de Assam
        if (direccion == direccionOpuesta) {
            cout << "Assam no puede caminar hacia atrás." << endl;
        } else {
            // Mover al personaje en la dirección dada
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
                    cout << "Dirección no válida. Assam no se ha movido." << endl;
            }
        }
    } while (direccion == direccionOpuesta); // Continuar preguntando hasta que la dirección sea válida


    /* Comentario futuro: al hacer esto peremos los movimientos extra que hemos hecho, esto quiere decir que si assam se sale de la matriz y gira, este pierde todos los movimientos extra que halla hecho. Para solventar esto podemos restar la diferencia de le saca al tablero para calcular cuanto debe andar en la direccion "vision" que se implementara a assam */

    // mover atravez del tablero a assam
    if (personaje.fila < 0 && personaje.fila!=0){ 
        vision='s';
        if (personaje.columna%2==0){
            personaje.fila = 0;
            personaje.columna-=1;
        } else{
            personaje.fila = 0;
            personaje.columna+=1;
        }
    }

    if (personaje.fila >= FILAS && personaje.fila!=6){
        vision='w';
        if (personaje.columna%2==0){
            personaje.fila = 6;
            personaje.columna+=1;
        } else{
            personaje.fila = 6;
            personaje.columna-=1;
        }
    }
    

    if (personaje.columna < 0 && personaje.columna!=0) { 
        vision='d';
        if (personaje.fila%2==0){
            personaje.columna = 0;
            personaje.fila-=1;
        } else{
            personaje.columna = 0;
            personaje.fila+=1;
        }
    }

    if (personaje.columna >= COLUMNAS && personaje.columna!=6){
        vision='a';
        if (personaje.fila%2==0){
            personaje.columna = 6;
            personaje.fila+=1;
        } else{
            personaje.columna = 6;
            personaje.fila-=1;
        }
    }
    

    if (personaje.columna==0 && personaje.fila<0){
        vision='s';
        personaje.fila = 0;
        personaje.columna = 0;
    }

    if (personaje.fila==0 && personaje.columna<0){
        vision='d';
        personaje.fila = 0;
        personaje.columna = 0;
    }
    
    if (personaje.columna==6 && personaje.fila>6){
        vision='w';
        personaje.fila = 6;
        personaje.columna = 6;
    }

    /*Falta revisar esto, no se cumple en todos los casos*/

    if (personaje.fila==6 && personaje.columna>6){
        vision='a';
        personaje.fila = 6;
        personaje.columna = 6;
    }
    

}

int main() {
    srand(time(0)); // Inicializar la semilla del generador de números aleatorios

    Tablero tablero;
    Personaje personaje;

    // Inicializar el tablero y Assam
    inicializarTablero(tablero);
    personaje.fila = FILAS / 2;
    personaje.columna = COLUMNAS / 2;
    personaje.icono = 'H'; // Por ejemplo, 'H' para Assam
    personaje.vision = 'w'; // Establecer la dirección de visión de Assam al norte

    char lanzarDado;
    bool salir = false;
    char direccion;

    // Bucle principal para permitir que el usuario se mueva por el tablero
    while (!salir) {
        
        limpiarTerminal(); // Limpiar la terminal antes de mostrar el tablero
        // Mostrar el tablero con Assam
        mostrarTableroConPersonaje(tablero, personaje);

        // Solicitar al usuario que lance el dado
        cout << "Presiona 'L' para lanzar el dado: ";
        cin >> lanzarDado;

        if (lanzarDado == 'Q' || lanzarDado == 'q') {
            salir = true;
        } else if (lanzarDado == 'L' || lanzarDado == 'l') {
            int movimientos = rand() % 6 + 1; // Lanzar el dado (número aleatorio entre 1 y 6)
            cout << "Has lanzado un " << movimientos << ". ";
            // Mover al personaje en la dirección dada, excluyendo caminar hacia atrás
            moverPersonaje(personaje, direccion, movimientos, personaje.vision);
        } else {
            cout << "Entrada no válida. Presiona 'L' para lanzar ." << endl;
        }
    }

    return 0;
} /*arreglar bugs, no despliega varios cout, ya que limpia la terminal muy rapido. Ademas el juego solo permite que assam se mueva en linea recta, toca hacer otra funcion para que assam mire y revisar el codigo*/

