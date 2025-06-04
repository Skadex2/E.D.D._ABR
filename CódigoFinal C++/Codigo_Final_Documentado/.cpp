#include <iostream>     // Librería para entrada y salida estándar
#include <fstream>      // Librería para manejo de archivos
#include <string>       // Librería para uso de cadenas
using namespace std;

// ==================== ESTRUCTURAS ====================

// Estructura para representar un proceso en la lista enlazada
struct Proceso {
    string id;              // Identificador único del proceso
    string nombre;          // Nombre del proceso
    int prioridad;          // Nivel de prioridad del proceso (a mayor número, mayor prioridad)
    Proceso* siguiente;     // Puntero al siguiente proceso en la lista

    // Constructor que inicializa los datos del proceso
    Proceso(string _id, string _nombre, int _prioridad) {
        id = _id;
        nombre = _nombre;
        prioridad = _prioridad;
        siguiente = NULL;   // Apunta a NULL al crearse
    }
};

// Nodo para representar un proceso en la pila de memoria
struct NodoMemoria {
    string procesoID;           // ID del proceso asignado en memoria
    NodoMemoria* siguiente;     // Apunta al nodo anterior (comportamiento de pila)
};

// Nodo para representar un proceso en la cola de CPU
struct NodoCola {
    string id;                  // ID del proceso
    string nombre;              // Nombre del proceso
    int prioridad;              // Prioridad del proceso
    NodoCola* siguiente;        // Apunta al siguiente nodo en la cola
};

// ==================== VARIABLES GLOBALES ====================

Proceso* listaProcesos = NULL;      // Lista enlazada que contiene todos los procesos
NodoMemoria* pilaMemoria = NULL;    // Pila (stack) que simula la memoria (push/pop)
NodoCola* colaCPU = NULL;           // Cola de procesos ordenada por prioridad

// ==================== FUNCIONES ====================

// Verifica si un proceso con determinado ID ya está en la cola de CPU
bool procesoYaEnCola(string id) {
    NodoCola* temp = colaCPU;
    while (temp) {
        if (temp->id == id)
            return true;    // Ya está en la cola
        temp = temp->siguiente;
    }
    return false;           // No está en la cola
}

// Busca un proceso por su ID dentro de la lista enlazada de procesos
Proceso* buscarProcesoPorID(string id) {
    Proceso* actual = listaProcesos;
    while (actual) {
        if (actual->id == id)
            return actual;  // Proceso encontrado
        actual = actual->siguiente;
    }
    return NULL;            // No se encontró el proceso
}

// Guarda todos los procesos de la lista en un archivo de texto
void guardarProcesosEnArchivo() {
    ofstream archivo("procesos.txt");   // Abre el archivo para escritura
    Proceso* actual = listaProcesos;
    while (actual) {
        archivo << "ID: " << actual->id << ", "
                << "Nombre: " << actual->nombre << ", "
                << "Prioridad: " << actual->prioridad << "\n";
        actual = actual->siguiente;
    }
    archivo.close();    // Cierra el archivo
}

// Carga los procesos almacenados previamente en el archivo "procesos.txt"
void cargarProcesosDesdeArchivo() {
    ifstream archivo("procesos.txt");   // Abre el archivo para lectura
    string id, nombre;
    int prioridad;

    // Lee los datos línea por línea
    while (archivo >> id >> nombre >> prioridad) {
        // Verifica que no se dupliquen
        if (buscarProcesoPorID(id) == NULL) {
            Proceso* nuevo = new Proceso(id, nombre, prioridad);
            if (!listaProcesos) {
                listaProcesos = nuevo;
            } else {
                Proceso* temp = listaProcesos;
                while (temp->siguiente) temp = temp->siguiente;
                temp->siguiente = nuevo;
            }
        }
    }

    archivo.close();    // Cierra el archivo
}

// 1. Función para insertar un nuevo proceso ingresado por el usuario
void insertarProceso() {
    string id, nombre;
    int prioridad;
	
	cout << "Ingrese ID del proceso (entero): ";
	cin >> id;

    // Evita que se repita un proceso con el mismo ID
    if (buscarProcesoPorID(id)) {
        cout << "Ya existe un proceso con ese ID.\n";
        system("pause");
        system("CLS");
        return;
    }

    // Solicita datos del nuevo proceso
    cout << "Ingrese nombre del proceso: ";
    cin >> nombre;
    
    //Validamos Prioridad
	do {
		cout << "Ingrese prioridad (entero del 1 al 10): ";
		cin >> prioridad;
			
		if (prioridad<1 || prioridad>10) {
				cout<<"\tError (entero del 1 al 10) .... \n";
		}
			
	} while (prioridad<1 || prioridad>10);
    
    

    // Crea e inserta el proceso al final de la lista
    Proceso* nuevo = new Proceso(id, nombre, prioridad);
    if (!listaProcesos) {
        listaProcesos = nuevo;
    } else {
        Proceso* actual = listaProcesos;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }

    guardarProcesosEnArchivo(); // Guarda los datos actualizados en archivo
    system("pause");
    system("CLS");
}

// 2. Lista todos los procesos existentes en la lista
void listarProcesos() {
    if (!listaProcesos) {
        cout << "No hay procesos registrados.\n";
    } else {
        Proceso* actual = listaProcesos;
        cout << "Lista de procesos:\n";
        while (actual) {
            cout << "ID: " << actual->id << " | Nombre: " << actual->nombre << " | Prioridad: " << actual->prioridad << "\n";
            actual = actual->siguiente;
        }
    }
    system("pause");
    system("CLS");
}

// 3. Elimina un proceso por su ID
void eliminarProceso() {
    string id;
    cout << "Ingrese el ID del proceso a eliminar: ";
    cin >> id;

    Proceso* actual = listaProcesos;
    Proceso* anterior = NULL;

    // Busca el proceso a eliminar
    while (actual && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    // Si no lo encuentra
    if (!actual) {
        cout << "Proceso no encontrado.\n";
        system("pause");
        system("CLS");
        return;
    }

    // Elimina el nodo correspondiente
    if (!anterior) {
        listaProcesos = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;                // Libera la memoria
    guardarProcesosEnArchivo();   // Actualiza el archivo
    cout << "Proceso eliminado correctamente.\n";
    system("pause");
    system("CLS");
}

// 4. Busca y muestra un proceso por ID
void buscarProceso() {
    string id;
    cout << "Ingrese el ID del proceso a buscar: ";
    cin >> id;

    Proceso* resultado = buscarProcesoPorID(id); //Buscar el proceso en la lista
    if (resultado) {
        cout << "Proceso encontrado:\n";  // muestra los datos en caso de encontrarlo
        cout << "ID: " << resultado->id << " | Nombre: " << resultado->nombre << " | Prioridad: " << resultado->prioridad << "\n"; //datos
    } else {
        cout << "Proceso no encontrado.\n";  // muestra el siguien mensaje si no encuentra el proceso
    }
    system("pause");
    system("CLS");
}

// 5. Permite cambiar la prioridad de un proceso ya registrado
void modificarPrioridad() {
    string id;
    cout << "Ingrese el ID del proceso: "; //busca el proceso mediante ID
    cin >> id;

    Proceso* p = buscarProcesoPorID(id);
    if (!p) {
        cout << "Proceso no encontrado.\n"; //si no se ubica sale un mensaje 
        system("pause");
        system("CLS");
        return;
    }

    int nuevaPrioridad;
    cout << "Prioridad actual: " << p->prioridad << "\n";
    
	//Validamos Prioridad
	do {
		cout << "Ingrese nueva prioridad: "; 
		cin >> nuevaPrioridad; // solicita nueva prioridad
			
		if (nuevaPrioridad<1 || nuevaPrioridad>10) {
				cout<<"\tError (entero del 1 al 10) .... \n"; // la prioridad tendra que ser entero
		}
			
	} while (nuevaPrioridad<1 || nuevaPrioridad>10);
	
    p->prioridad = nuevaPrioridad; // Asigna prioridad
    guardarProcesosEnArchivo(); // Actualiza archivo
    cout << "Prioridad modificada correctamente.\n";
    system("pause");
    system("CLS");
}

// 6. Ordena los procesos por prioridad de forma descendente (mayor prioridad primero)
void ordenarProcesos() {
    if (!listaProcesos || !listaProcesos->siguiente) {
        cout << "No hay suficientes procesos para ordenar.\n";
        system("pause");
        system("CLS");
        return;
    }

    // Algoritmo de burbuja adaptado a lista enlazada
    bool intercambiado;
    do {
        intercambiado = false;
        Proceso* actual = listaProcesos;
        Proceso* anterior = NULL;

        while (actual && actual->siguiente) {
            Proceso* siguiente = actual->siguiente;
            // Compara prioridades para intercambiar
            if (actual->prioridad < siguiente->prioridad) {
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

    guardarProcesosEnArchivo(); // Guarda el nuevo orden
    cout << "Procesos ordenados por prioridad (Mayor -> Menor).\n";
    listarProcesos(); //mostramos la lista ordenada
    system("pause");
    system("CLS");
}

// 7. Encola todos los procesos a la cola de CPU, ordenados por prioridad
void encolarCPU() {
    Proceso* actual = listaProcesos;
    while (actual) {
        if (!procesoYaEnCola(actual->id)) {
            NodoCola* nuevo = new NodoCola;
            nuevo->id = actual->id;
            nuevo->nombre = actual->nombre;
            nuevo->prioridad = actual->prioridad;
            nuevo->siguiente = NULL;

            // Inserta en la posición correcta según la prioridad
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
        }
        actual = actual->siguiente;
    }

    cout << "Procesos encolados a la CPU segun prioridad.\n";
    system("pause");
    system("CLS");
}

// 8. Desencola y ejecuta el proceso con mayor prioridad
void ejecutarCPU() {
    if (!colaCPU) {
        cout << "No hay procesos en la cola.\n";
        system("pause");
        system("CLS");
        return;
    }

    NodoCola* temp = colaCPU;
    colaCPU = colaCPU->siguiente;
    cout << "Ejecutando proceso:\n"; // muestra el proceso
    cout << "ID: " << temp->id << " | Nombre: " << temp->nombre << " | Prioridad: " << temp->prioridad << "\n";
    delete temp;    // Libera memoria del proceso ejecutado
    system("pause");
    system("CLS");
}

// 9. Muestra todos los procesos en la cola de CPU
void mostrarColaCPU() { //Verifica si la cola esta vacia
    if (!colaCPU) {
        cout << "La cola esta vacia.\n"; // Mensaje si esta vacia
    } else {
        cout << "Cola actual (ordenada por prioridad):\n"; 
        NodoCola* temp = colaCPU;
        while (temp) { //Se imprime el ID, nombre y prioridad de cada proceso en la cola
            cout << "ID: " << temp->id << " | Nombre: " << temp->nombre << " | Prioridad: " << temp->prioridad << "\n";
            temp = temp->siguiente;
        }
    }
    system("pause");
    system("CLS");
}

// 10. Simula la asignación de memoria (Push en la pila)
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

// 11. Simula la liberación de memoria (Pop en la pila)
void popMemoria() {
    if (!pilaMemoria) {
        cout << "La memoria ya esta vacia.\n";
    } else {
        cout << "Liberando memoria del proceso ID: " << pilaMemoria->procesoID << "\n";
        NodoMemoria* temp = pilaMemoria;
        pilaMemoria = pilaMemoria->siguiente;
        delete temp;
    }
    system("pause");
    system("CLS");
}

// 12. Muestra el estado actual de la pila de memoria
void mostrarMemoria() {
    if (!pilaMemoria) {
        cout << "La memoria esta vacia.\n";
    } else {
        NodoMemoria* temp = pilaMemoria;
        int pos = 1;
        while (temp) {
            cout << "Posicion " << pos++ << ": " << temp->procesoID << "\n";
            temp = temp->siguiente;
        }
    }
    system("pause");
    system("CLS");
}

// ==================== FUNCION PRINCIPAL (MAIN) ====================
int main() {
    cargarProcesosDesdeArchivo();    // Carga procesos guardados previamente
	ofstream limpiar("procesos.txt"); // Limpia el archivo (opcional)
	limpiar.close();

    int opcion;

    do {
        // Menú de opciones
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

        // Validación de opción ingresada
        do {
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            if (opcion < 1 || opcion > 13) {
                cout << "Opcion no valida.\n";
                system("pause");
                system("CLS");
            }
        } while (opcion < 1 || opcion > 13);

        // Ejecución según opción
        switch (opcion) {
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
