#include <iostream>
#include <string>
using namespace std;

// ==================== ESTRUCTURAS ====================

// Nodo para lista enlazada de procesos
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

// Nodo para pila (gestión de memoria)
struct NodoMemoria {
    string procesoID;
    NodoMemoria* siguiente;
};

// Cola de prioridad basada en lista enlazada ordenada
struct NodoCola {
    string id;
    string nombre;
    int prioridad;
    NodoCola* siguiente;
};
Proceso * listaProcesos = NULL;
NodoMemoria * pilaMemoria = NULL;
NodoCola * colaCPU = NULL;

// Eliminar los procesos ID (3)
void eliminarProceso() {
    string id;
    cout << "Ingrese el ID del proceso a eliminar: ";
    cin >> id;

    Proceso* actual = listaProcesos;
    Proceso* anterior = NULL;

    while (actual && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (!actual) {
        cout << "Proceso no encontrado.\n";
        system("pause");
        system("CLS");
        return;
    }

    if (!anterior) {
        listaProcesos = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    cout << "Proceso eliminado correctamente.\n";
    system("pause");
    system("CLS");
} 
//Buscar el proceso por ID (V. devuelve puntero) (4.1)
Proceso* buscarProceso(string id) { 
    Proceso* actual = listaProcesos;
    while (actual) {
        if (actual->id == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

//Buscar el proces mediante el Id (V. con void) (4.2)
void buscarProceso() {
    string id;
    cout << "Ingrese el ID del proceso a buscar: ";
    cin >> id;

    Proceso* resultado = buscarProceso(id);
    if (resultado) {
        cout << "Proceso encontrado:\n";
        cout << "ID: " << resultado->id 
             << " | Nombre: " << resultado->nombre 
             << " | Prioridad: " << resultado->prioridad << "\n";
    } else {
        cout << "Proceso no encontrado.\n";
    }
    system("pause");
    system("CLS");
}


//Modificación por priorida de un proceso insertado (5)
void modificarPrioridad() {
    string id;
    cout << "Ingrese el ID del proceso: ";
    cin >> id;

    Proceso* p = buscarProceso(id);
    if (!p) {
        cout << "Proceso no encontrado.\n";
        system("pause");
        system("CLS");
        return;
    }

    int nuevaPrioridad;
    cout << "Prioridad actual: " << p->prioridad << "\n";
    cout << "Ingrese nueva prioridad: ";
    cin >> nuevaPrioridad;
    p->prioridad = nuevaPrioridad;

    cout << "Prioridad modificada correctamente.\n";
    system("pause");
    system("CLS");
}

//Ordenar los procesos de manera descendente (6)
void ordenarProcesos() {
    if (!listaProcesos || !listaProcesos->siguiente) {
        cout << "No hay suficientes procesos para ordenar.\n";
        system("pause");
        system("CLS");
        return;
    }
    bool intercambiado;
    do {
        intercambiado = false;
        Proceso* actual = listaProcesos;
        Proceso* anterior = NULL;

        while (actual && actual->siguiente) {
            Proceso* siguiente = actual->siguiente;
            if (actual->prioridad < siguiente->prioridad) {
// Interacambiar los nodos
                if (anterior) {
                    anterior->siguiente = siguiente;
                } else {
                    listaProcesos = siguiente;
                }

                actual->siguiente = siguiente->siguiente;
                siguiente->siguiente = actual;

                anterior = siguiente;
                intercambiado = true;
            } else {
                anterior = actual;
                actual = actual->siguiente;
            }
        }
    } while (intercambiado);

    cout << "Procesos ordenados por prioridad (Mayor -> Menor).\n";
    system("pause");
    system("CLS");
}

int main (){
	eliminarProceso();
	buscarProceso();
	modificarPrioridad();
	ordenarProcesos();
}
