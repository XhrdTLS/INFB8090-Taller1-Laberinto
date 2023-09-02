/*  INFB8090 Computacion Paralela y Distribuida
    Seccion 411
    Integrantes: 
    - Gustavo Oyarce P.
    - Nicolas Jara C.
    - Tomas Lillo S.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cstdlib>  // Para system("pause")

using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

bool esSalida(int x, int y, int numRows, int numCols) {
    // Verificar si está en una de las filas de salida
    if (x == 0 || x == numRows - 1) {
        return true;
    }
    // Verificar si está en una de las columnas de salida
    if (y == 0 || y == numCols - 1) {
        return true;
    }
    return false;
}

int main() {
    ifstream inputFile("nuevo.txt");

    if (!inputFile.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    char wallCharacter = '█';    // Caracter para representar las paredes
    char pathCharacter = ' ';    // Caracter para representar el camino

    vector<string> Laberinto;  // Vector de cadenas para almacenar el laberinto

    string linea;
    while (getline(inputFile, linea)) {
        Laberinto.push_back(linea);
    }

    inputFile.close();

    int numRows = Laberinto.size();
    int numCols = Laberinto[0].size();

    // Encontrar la entrada (primer fila)
    int entradaX = 0;
    int entradaY = 0;
    for (int i = 0; i < numCols; i++) {
        if (Laberinto[0][i] == pathCharacter) {
            entradaY = i;
            break;
        }
    }

    stack<Point> pila;
    pila.push(Point(0, entradaY)); // Iniciar desde la entrada

    vector<Point> camino;  // Almacena el camino recorrido

    // Direcciones: arriba, abajo, izquierda, derecha
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    bool encontrado = false;

    while (!pila.empty()) {
        Point actual = pila.top();
        int x = actual.x;
        int y = actual.y;

        // Verificar si estamos en una salida
        if (esSalida(x, y, numRows, numCols)) {
            encontrado = true;
            break;
        }

        bool movimientoPosible = false;

        // Intentar moverse en las cuatro direcciones posibles
        for (int i = 0; i < 4; i++) {
            int nuevoX = x + dx[i];
            int nuevoY = y + dy[i];

            if (nuevoX >= 0 && nuevoX < numRows && nuevoY >= 0 && nuevoY < numCols &&
                Laberinto[nuevoX][nuevoY] == pathCharacter) {
                pila.push(Point(nuevoX, nuevoY));
                Laberinto[nuevoX][nuevoY] = '*'; // Marcar como visitado
                camino.push_back(Point(nuevoX, nuevoY));  // Agregar al camino
                movimientoPosible = true;
                break;
            }
        }

        // Si no hay movimientos posibles desde la posición actual, retroceder
        if (!movimientoPosible) {
            pila.pop();
        }
    }

    // Si se encontró una salida, muestra un mensaje de éxito y el camino recorrido
    if (encontrado) {
        cout << "Se encontró una salida." << endl;

        // Imprimir el laberinto con el camino recorrido
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                cout << Laberinto[i][j];  // Mostrar laberinto con caracteres originales
            }
            cout << endl;
        }

        // Generar un archivo de solución
        ofstream outputFile("solucion.txt");
        if (outputFile.is_open()) {
            // Guardar la solución en el archivo
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    outputFile << Laberinto[i][j];  // Mantener caracteres originales en la solución
                }
                outputFile << endl;
            }
            outputFile.close();
            cout << "La solución se ha guardado en 'solucion.txt'." << endl;
        } else {
            cout << "No se pudo crear el archivo de solución." << endl;
        }
    } else {
        cout << "No se encontró una salida." << endl;
    }

    system("pause");

    return 0;
}
