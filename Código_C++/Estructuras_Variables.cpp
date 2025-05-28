#include <iostream>
#include <string>
using namespace std;

// ESTRUCTURAS

// Nodo para lista enlazada 
struct Proceso {
    string id;
    string nombre;
    int prioridad;
    Proceso* siguiente;

    Proceso(string _id, string _nombre, int _prioridad) {
        id = _id;
        nombre = _nombre;
        prioridad = _prioridad;
        siguiente = NULL;
    }
};

// Nodo para pila
struct NodoMemoria {
    string procesoID;
    NodoMemoria* siguiente;
};

// Nodo para cola
struct NodoCola {
    string id;
    string nombre;
    int prioridad;
    NodoCola* siguiente;
};

// VARIABLES GLOBALES 
Proceso* listaProcesos = NULL;
NodoMemoria* pilaMemoria = NULL;
NodoCola* colaCPU = NULL; 

// 1. Insertar proceso en la lista
void insertarProceso() {
    string id, nombre;
    int prioridad;

    cout << "Ingrese ID del proceso: ";
    cin >> id;
    cout << "Ingrese nombre del proceso: ";
    cin >> nombre;
    cout << "Ingrese prioridad (entero): ";
    cin >> prioridad;

    Proceso* nuevo = new Proceso(id, nombre, prioridad);

    if (!listaProcesos) {
        listaProcesos = nuevo;  // Primer nodo
    } else {
        Proceso* actual = listaProcesos;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;  
    }
    system("pause");
    system("CLS");
}

// 2. Listar procesos
void listarProcesos() {
    if (!listaProcesos) {
        cout << "No hay procesos registrados.\n";
    } else {
        Proceso* actual = listaProcesos;
        cout << "Lista de procesos:\n";
        while (actual) {
            cout << "ID: " << actual->id 
                 << " | Nombre: " << actual->nombre 
                 << " | Prioridad: " << actual->prioridad << "\n";
            actual = actual->siguiente;
        }
    }
    system("pause");
    system("CLS");
}

int main (){
	insertarProceso();
	listarProcesos();
}
