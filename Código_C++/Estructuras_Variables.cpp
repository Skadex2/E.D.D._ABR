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
