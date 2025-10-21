//
// Created by sebab on 20-10-2025.
//

#ifndef TALLER2_SPARSEMATRIX_H
#define TALLER2_SPARSEMATRIX_H

#include "Node.h"
#include <iostream>

class SparseMatrix {
private:
    Node* cabeza;
    int numeroNodos;
public:
    SparseMatrix();
    ~SparseMatrix();
    void agregar(int valor, int x, int y);
    int obtener(int x, int y) const;
    void eliminar(int x, int y);
    void imprimirValores() const;
    int densidad() const;
    SparseMatrix* multiplicar(const SparseMatrix* otra) const;
private:
    void obtenerExtremos(int &maxFila, int &maxColumna) const;
};

#endif //TALLER2_SPARSEMATRIX_H