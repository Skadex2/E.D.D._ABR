#include <iostream>
#include <string>
using namespace std;
// Cola de prioridad basada en lista enlazada ordenada
struct NodoCola {
    string id;
    string nombre;
    int prioridad;
    NodoCola* siguiente;
};

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

// ==================== VARIABLES GLOBALES ====================
Proceso* listaProcesos = NULL;
NodoCola* colaCPU = NULL;



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
    cout << "Procesos encolados a la CPU segun prioridad.\n";
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

int main () {
	
	encolarCPU();
	ejecutarCPU();
}
