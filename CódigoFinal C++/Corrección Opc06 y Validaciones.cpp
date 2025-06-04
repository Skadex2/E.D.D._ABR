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




// 5. Permite cambiar la prioridad de un proceso ya registrado
void modificarPrioridad() {
    string id;
    cout << "Ingrese el ID del proceso: ";
    cin >> id;

    Proceso* p = buscarProcesoPorID(id);
    if (!p) {
        cout << "Proceso no encontrado.\n";
        system("pause");
        system("CLS");
        return;
    }

    int nuevaPrioridad;
    cout << "Prioridad actual: " << p->prioridad << "\n";
    
	//Validamos Prioridad
	do {
		cout << "Ingrese nueva prioridad: ";
		cin >> nuevaPrioridad;
			
		if (nuevaPrioridad<1 || nuevaPrioridad>10) {
				cout<<"\tError (entero del 1 al 10) .... \n";
		}
			
	} while (nuevaPrioridad<1 || nuevaPrioridad>10);
	
    
    p->prioridad = nuevaPrioridad;
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
    cout << "Procesos ordenados por prioridad (Mayor -> Menor).\n";
    listarProcesos(); //mostramos la lista ordenada
    system("pause");
    system("CLS");
}
