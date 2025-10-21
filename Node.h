//
// Created by sebab on 20-10-2025.
//

#ifndef TALLER2_NODE_H
#define TALLER2_NODE_H

struct Node {
    int x;
    int y;
    int valor;
    Node* siguiente;

    Node(int fila, int columna, int valorElemento)
    : x(fila), y(columna), valor(valorElemento), siguiente(nullptr) {}
};

#endif //TALLER2_NODE_H

