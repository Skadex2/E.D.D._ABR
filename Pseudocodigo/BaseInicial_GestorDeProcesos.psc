Proceso GestorDeProcesos
    Definir procesos_id, procesos_nombre, procesos_prioridad Como Caracter
    Dimension procesos_id[100], procesos_nombre[100], procesos_prioridad[100]
    
    Definir totalProcesos, i, opcion, encontrado Como Entero
    Definir idBuscado, nombre, prioridad, idNuevo, prioridadNueva Como Caracter
	
    totalProcesos <- 0
	
    Repetir
        Escribir ""
        Escribir "======= GESTOR DE PROCESOS ======="
        Escribir "1. Insertar proceso"
		Escribir "2. Buscar proceso por ID"
		Escribir "3. Modificar prioridad"
        Escribir "Seleccione una opci�n:"
        Leer opcion
		
        Segun opcion Hacer
            1:
                Si totalProcesos < 100 Entonces
                    Escribir "Ingrese ID del proceso:"
                    Leer idNuevo
                    Escribir "Ingrese nombre del proceso:"
                    Leer nombre
                    Escribir "Ingrese prioridad del proceso:"
                    Leer prioridad
					
                    procesos_id[totalProcesos + 1] <- idNuevo
                    procesos_nombre[totalProcesos + 1] <- nombre
                    procesos_prioridad[totalProcesos + 1] <- prioridad
                    totalProcesos <- totalProcesos + 1
                    Escribir "Proceso insertado correctamente."
                Sino
                    Escribir "�L�mite m�ximo de procesos alcanzado!"
                FinSi
				
            2:
                Escribir "Ingrese el ID del proceso a buscar:"
                Leer idBuscado
                encontrado <- -1
                Para i <- 1 Hasta totalProcesos
                    Si procesos_id[i] = idBuscado Entonces
                        encontrado <- i
                    FinSi
                FinPara
				
                Si encontrado <> -1 Entonces
                    Escribir "Proceso encontrado:"
                    Escribir "ID: ", procesos_id[encontrado]
                    Escribir "Nombre: ", procesos_nombre[encontrado]
                    Escribir "Prioridad: ", procesos_prioridad[encontrado]
                Sino
                    Escribir "No se encontr� un proceso con ese ID."
                FinSi
				
            3:
				Escribir "Ingrese el ID del proceso para modificar prioridad:"
                Leer idBuscado
                encontrado <- -1
                Para i <- 1 Hasta totalProcesos
                    Si procesos_id[i] = idBuscado Entonces
                        encontrado <- i
                    FinSi
                FinPara
				
                Si encontrado <> -1 Entonces
                    Escribir "Prioridad actual: ", procesos_prioridad[encontrado]
                    Escribir "Ingrese la nueva prioridad:"
                    Leer prioridadNueva
                    procesos_prioridad[encontrado] <- prioridadNueva
                    Escribir "Prioridad modificada correctamente."
                Sino
                    Escribir "No se encontr� un proceso con ese ID."
                FinSi
				
            De Otro Modo:
                Escribir "Opci�n no v�lida. Intente nuevamente."
        FinSegun
		
    Hasta Que opcion = 3
	
FinProceso