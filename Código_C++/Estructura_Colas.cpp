#include <iostream>
#include <string>
using namespace std;
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


// Cola de prioridad basada en lista enlazada ordenada
struct NodoCola {
    string id;
    string nombre;
    int prioridad;
    NodoCola* siguiente;
};



// ==================== VARIABLES GLOBALES ====================
Proceso* listaProcesos = NULL;
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
        actual->siguiente = nuevo;  // Insertar al final
    }
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



int main () {
	int num,i;
	
	
	cout<<"¿Cuantos procesos quieres ingresar?";
	cin>>num;
	for (i=0;i<num;i++) {
		insertarProceso();
	}
	
	
	encolarCPU();
	ejecutarCPU();
    mostrarColaCPU();
}
