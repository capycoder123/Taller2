#include <iostream>
#include <limits>
#include "SparseMatrix.h"

int main() {
    SparseMatrix *A = new SparseMatrix();
    SparseMatrix *B = new SparseMatrix();
    SparseMatrix *C = new SparseMatrix();

    char opcionPrincipal;
    do {
        std::cout << "\n=== MENÚ PRINCIPAL ===\n";
        std::cout << "Seleccione la matriz (A, B, C) para operar\n";
        std::cout << "M) Multiplicar A * B -> C\n";
        std::cout << "S) Salir\n";
        std::cout << "Opción: ";
        std::cin >> opcionPrincipal;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        opcionPrincipal = std::toupper(opcionPrincipal);

        if (opcionPrincipal == 'A' || opcionPrincipal == 'B' || opcionPrincipal == 'C') {
            SparseMatrix *matrizSeleccionada = nullptr;
            char nombre = opcionPrincipal;
            if (nombre == 'A') matrizSeleccionada = A;
            if (nombre == 'B') matrizSeleccionada = B;
            if (nombre == 'C') matrizSeleccionada = C;

            char opcionOperacion;
            do {
                std::cout << "\n--- Operando sobre matriz " << nombre << " ---\n";
                std::cout << "1) Agregar (insertar/actualizar valor)\n";
                std::cout << "2) Eliminar valor\n";
                std::cout << "3) Obtener valor\n";
                std::cout << "4) Imprimir valores almacenados\n";
                std::cout << "5) Ver densidad (%)\n";
                std::cout << "6) Volver al menú principal\n";
                std::cout << "Opción: ";
                std::cin >> opcionOperacion;

                switch (opcionOperacion) {
                    case '1': {
                        int x,y,valor;
                        std::cout << "Ingrese fila (x): ";
                        std::cin >> x;
                        std::cout << "Ingrese columna (y): ";
                        std::cin >> y;
                        std::cout << "Ingrese valor (entero): ";
                        std::cin >> valor;
                        matrizSeleccionada->agregar(valor,x,y);
                        if (valor != 0) {
                            std::cout << "Valor agregado/actualizado en (" << x << ", " << y << ").\n";
                        } else {
                            std::cout << "Valor en (" << x << ", " << y << ") eliminado (0 ingresado).\n";
                        }
                        break;
                    }
                    case '2': {
                        int x,y;
                        std::cout << "Ingrese fila (x) a eliminar: ";
                        std::cin >> x;
                        std::cout << "Ingrese columna (y) a eliminar: ";
                        std::cin >> y;
                        int valAntes = matrizSeleccionada->obtener(x, y);
                        matrizSeleccionada->eliminar(x, y);
                        if (valAntes != 0) {
                            std::cout << "Valor en (" << x << ", " << y << ") eliminado.\n";
                        } else {
                            std::cout << "No se encontró valor en (" << x << ", " << y << ").\n";
                        }
                        break;
                    }
                    case '3': {
                        int x,y;
                        std::cout << "Ingrese fila (x): ";
                        std::cin >> x;
                        std::cout << "Ingrese columna (y): ";
                        std::cin >> y;
                        int valor = matrizSeleccionada->obtener(x, y);
                        std::cout << "Valor en (" << x << ", " << y << "): " << valor << "\n";
                        break;
                    }
                    case '4': {
                        std::cout << "Valores almacenados en matriz " << nombre << ":\n";
                        matrizSeleccionada->imprimirValores();
                        break;
                    }
                    case '5': {
                        int dens = matrizSeleccionada->densidad();
                        std::cout << "Densidad de matriz " << nombre << ": " << dens << "%\n";
                        break;
                    }
                    case '6': {
                        std::cout << "Regresando al menú principal...\n";
                        break;
                    }
                    default: {
                        std::cout << "Opción inválida, intente de nuevo.\n";
                        if (!std::cin) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        break;
                    }
                }
            } while (opcionOperacion != '6');
        }
        else if (opcionPrincipal == 'M') {
            delete C;
            C = A->multiplicar(B);
            std::cout << "Se ha multiplicado A * B. El resultado se almacenó en la matriz C.\n";
        }
        else if (opcionPrincipal == 'S') {
            std::cout << "Saliendo del programa...\n";
        }
        else {
            std::cout << "Opción inválida, intente nuevamente.\n";
            if (!std::cin) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    } while (opcionPrincipal != 'S');

    delete A;
    delete B;
    delete C;
    return 0;
}