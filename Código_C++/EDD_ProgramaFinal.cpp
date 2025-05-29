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

// ==================== VARIABLES GLOBALES ====================
Proceso* listaProcesos = NULL;
NodoMemoria* pilaMemoria = NULL;
NodoCola* colaCPU = NULL;

// ==================== FUNCIONES ====================

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
        actual->siguiente = nuevo;  // Insertar al final
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

// 3. Eliminar proceso por ID
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
// 4. Buscar proceso por ID (versión que devuelve puntero)
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

// 4. Buscar proceso por ID (versión void para mostrar resultado)
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


// 5. Modificar prioridad de un proceso
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

// 6. Ordenar procesos por prioridad (Mayor -> Menor)
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
                // Intercambiar nodos
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

// 7. Encolar proceso a la cola CPU
void encolarCPU() {
    Proceso* actual = listaProcesos;
    while (actual) {
        NodoCola* nuevo = new NodoCola;
        nuevo->id = actual->id;
        nuevo->nombre = actual->nombre;
        nuevo->prioridad = actual->prioridad;
        nuevo->siguiente = NULL;

        if (!colaCPU || nuevo->prioridad < colaCPU->prioridad) {
            nuevo->siguiente = colaCPU;
            colaCPU = nuevo;
        } else {
            NodoCola* temp = colaCPU;
            while (temp->siguiente && temp->siguiente->prioridad <= nuevo->prioridad)
                temp = temp->siguiente;
            nuevo->siguiente = temp->siguiente;
            temp->siguiente = nuevo;
        }
        actual = actual->siguiente;
    }
    cout << "Procesos encolados a la CPU según prioridad.\n";
    system("pause");
    system("CLS");
}

// 8. Ejecutar proceso (desencolar)
void ejecutarCPU() {
    if (!colaCPU) {
        cout << "No hay procesos en la cola.\n";
        system("pause");
        system("CLS");
        return;
    }
    NodoCola* temp = colaCPU;
    colaCPU = colaCPU->siguiente;
    cout << "Ejecutando proceso:\n";
    cout << "ID: " << temp->id << " | Nombre: " << temp->nombre << " | Prioridad: " << temp->prioridad << "\n";
    delete temp;
    system("pause");
    system("CLS");
}

// 9. Mostrar cola CPU
void mostrarColaCPU() {
    if (!colaCPU) {
        cout << "La cola está vacia.\n";
        system("pause");
        system("CLS");
        return;
    }

    cout << "Cola actual (ordenada por prioridad):\n";
    NodoCola* temp = colaCPU;
    while (temp) {
        cout << "ID: " << temp->id << " | Nombre: " << temp->nombre << " | Prioridad: " << temp->prioridad << "\n";
        temp = temp->siguiente;
    }
    system("pause");
    system("CLS");
}

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

// 12. Mostrar estado actual de la memoria
void mostrarMemoria() {
    if (!pilaMemoria) {
        cout << "La memoria está vacia.\n";
        system("pause");
        system("CLS");
        return;
    }

    NodoMemoria* temp = pilaMemoria;
    int pos = 1;
    while (temp) {
        cout << "Posicion " << pos++ << ": " << temp->procesoID << "\n";
        temp = temp->siguiente;
    }
    system("pause");
    system("CLS");
}

// ==================== MAIN ====================
int main() {
    int opcion;
    do {
        cout << "\n======= GESTOR DE PROCESOS Y MEMORIA =======\n";
        cout << "1. Insertar proceso\n";
        cout << "2. Listar procesos (sin ordenar)\n";
        cout << "3. Eliminar proceso por ID\n";
        cout << "4. Buscar proceso por ID\n";
        cout << "5. Modificar prioridad de un proceso\n";
        cout << "6. Ordenar procesos por prioridad (Mayor -> Menor)\n";
        cout << "7. Encolar proceso a la cola CPU\n";
        cout << "8. Ejecutar (desencolar) proceso con mayor prioridad\n";
        cout << "9. Visualizar cola actual (ordenada)\n";
        cout << "10. Asignar memoria (push)\n";
        cout << "11. Liberar memoria (pop)\n";
        cout << "12. Ver estado actual de memoria\n";
        cout << "13. Salir\n";
        
        do{
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            if(opcion<1 || opcion > 13){
                cout << "Opcion no valida.\n";
                system("pause");
                system("CLS");
            }
            
        }while(opcion<1 || opcion > 13);
        
        switch(opcion) {
            case 1: insertarProceso(); break;    
            case 2: listarProcesos(); break;
            case 3: eliminarProceso(); break;
            case 4: buscarProceso(); break;
            case 5: modificarPrioridad(); break;
            case 6: ordenarProcesos(); break;
            case 7: encolarCPU(); break;
            case 8: ejecutarCPU(); break;
            case 9: mostrarColaCPU(); break;
            case 10: pushMemoria(); break;
            case 11: popMemoria(); break;
            case 12: mostrarMemoria(); break;
            case 13: cout << "Saliendo...\n"; break;
        }
    } while (opcion != 13);

}

