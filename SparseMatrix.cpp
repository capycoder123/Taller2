//
// Created by sebab on 20-10-2025.
//

#include "SparseMatrix.h"

SparseMatrix::SparseMatrix() : cabeza(nullptr), numeroNodos(0) {}

SparseMatrix::~SparseMatrix() {
    Node* actual = cabeza;
    while (actual != nullptr) {
        Node* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    numeroNodos = 0;
}

void SparseMatrix::obtenerExtremos(int &maxFila, int &maxColumna) const {
    maxFila = -1;
    maxColumna = -1;
    Node* actual = cabeza;
    while (actual != nullptr) {
        if (actual->x > maxFila) {
            maxFila = actual->x;
        }
        if (actual->y > maxColumna) {
            maxColumna = actual->y;
        }
        actual = actual->siguiente;
    }
}

void SparseMatrix::agregar(int valor, int x, int y) {
    if (x < 0 || y < 0) {
        std::cerr << "Error: Coordenadas negativas (" << x << "," << y << ")" << std::endl;
        return;
    }
    if (valor == 0) {
        eliminar(x, y);
        return;
    }

    Node* actual = cabeza;
    Node* anterior = nullptr;
    while (actual != nullptr && (actual-> x < x || (actual->x == x && actual->y < y))) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual != nullptr && actual->x == x && actual->y == y) {
        actual->valor = valor;
    } else {
        Node* nuevo = new Node(x,y,valor);
        if (anterior == nullptr) {
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        } else {
            nuevo->siguiente = actual;
            anterior->siguiente = nuevo;
        }
        numeroNodos++;
    }
}

int SparseMatrix::obtener(int x, int y) const {
    if (x < 0 || y < 0) {
        return 0;
    }
    Node* actual = cabeza;
    while (actual != nullptr) {
        if (actual->x == x && actual->y == y) {
            return actual->valor;
        }
        if (actual->x > x || (actual->x == x && actual->y > y)) {
            break;
        }
        actual = actual->siguiente;
    }
    return 0;
}

void SparseMatrix::eliminar(int x, int y) {
    if (x < 0 || y < 0) {
        std::cerr << "Error: Coordenadas negativas (" << x << "," << y << ")" << std::endl;
        return;
    }
    Node* actual = cabeza;
    Node* anterior = nullptr;
    while (actual != nullptr) {
        if (actual->x == x && actual->y == y) {
            if (anterior == nullptr) {
                cabeza = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            numeroNodos--;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
}

void SparseMatrix::imprimirValores() const {
    if (cabeza == nullptr) {
        std::cout << "(vacio)" << std::endl;
        return;
    }
    Node* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "(" << actual->x << "," << actual->y << ") -->" << actual->valor << std::endl;
        actual = actual->siguiente;
    }
}

int SparseMatrix::densidad() const {
    if (cabeza == nullptr) {
        return 0;
    }
    int maxFila, maxColumna;
    obtenerExtremos(maxFila, maxColumna);
    if (maxFila < 0 || maxColumna < 0) {
        return 0;
    }
    long totalPosiciones = static_cast<long>(maxFila + 1) * static_cast<long>(maxColumna + 1);
    if (totalPosiciones == 0) {
        return 0;
    }
    int porcentaje = static_cast<int>((numeroNodos * 100) / totalPosiciones);
    return porcentaje;
}

SparseMatrix* SparseMatrix::multiplicar(const SparseMatrix* otra) const {
    SparseMatrix* resultado = new SparseMatrix();

    if (cabeza == nullptr || otra == nullptr || otra->cabeza == nullptr) {
        return resultado;
    }

    int maxFilaA, maxColA;
    obtenerExtremos(maxFilaA, maxColA);
    int maxFilaB, maxColB;
    otra->obtenerExtremos(maxFilaB, maxColB);

    int filasA = maxFilaA + 1;
    int colsA = maxColA + 1;
    int filasB = maxFilaB + 1;
    int colsB = maxColB + 1;

    if (colsA != filasB) {
        std::cerr << "Error: Dimensiones incompatibles para multiplicar. "
                  << "Matriz A: " << filasA << "x" << colsA << ", Matriz B: " << filasB << "x" << colsB << std::endl;
        return resultado;
    }

    Node* nodoA = cabeza;
    while (nodoA != nullptr) {
        Node* nodoB = otra->cabeza;
        while (nodoB != nullptr) {
            if (nodoA->y == nodoB->x) {
                int i = nodoA -> x;
                int j = nodoB -> y;
                int contribucion = nodoA -> valor * nodoB -> valor;
                if (contribucion != 0) {
                    int valorExistente = resultado->obtener(i,j);
                    int nuevoValor = valorExistente + contribucion;
                    resultado->agregar(nuevoValor, i, j);
                }
            }
            nodoB = nodoB->siguiente;
        }
        nodoA = nodoA->siguiente;
    }
    return resultado;
}
