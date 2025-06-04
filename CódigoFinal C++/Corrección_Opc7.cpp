bool procesoYaEnCola(string id) {
    NodoCola* temp = colaCPU;
    while (temp) {
        if (temp->id == id)
            return true;    // Ya está en la cola
        temp = temp->siguiente;
    }
    return false;           // No está en la cola
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
