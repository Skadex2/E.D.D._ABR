#include <iostream>
#include <string>
using namespace std;

// Nodo para pila (gestión de memoria)
struct NodoMemoria {
    string procesoID;
    NodoMemoria* siguiente;
};

// ==================== VARIABLES GLOBALES ====================
NodoMemoria* pilaMemoria = NULL;

// 10. Asignar memoria (push)
void pushMemoria() {
    string id;
    cout << "Ingrese el ID del proceso para asignar memoria: ";
    cin >> id;

    NodoMemoria* nuevo = new NodoMemoria;
    nuevo->procesoID = id;
    nuevo->siguiente = pilaMemoria;
    pilaMemoria = nuevo;

    cout << "Memoria asignada correctamente al proceso.\n";
    system("pause");
    system("CLS");
}
// 11. Liberar memoria (pop)
void popMemoria() {
    if (!pilaMemoria) {
        cout << "La memoria ya esta vacia.\n";
        system("pause");
        system("CLS");
        return;
    }
    cout << "Liberando memoria del proceso ID: " << pilaMemoria->procesoID << "\n";
    NodoMemoria* temp = pilaMemoria;
    pilaMemoria = pilaMemoria->siguiente;
    delete temp;
    system("pause");
    system("CLS");
}

int main() {
    pushMemoria();
    popMemoria();
}

