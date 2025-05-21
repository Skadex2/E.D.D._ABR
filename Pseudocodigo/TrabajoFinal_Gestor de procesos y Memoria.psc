Proceso GestorCompletoCPUyMemoria
	
    Definir procesos_id, procesos_nombre Como Caracter
    Definir procesos_prioridad Como Entero
    Dimension procesos_id[100], procesos_nombre[100], procesos_prioridad[100]
    
    Definir memoria Como Caracter
    Dimension memoria[100]
    
    Definir totalProcesos, i, j, opcion, encontrado, topePila Como Entero
    Definir idBuscado, nombre, idNuevo, bloqueID Como Caracter
    Definir prioridad, prioridadAux Como Entero
    
    totalProcesos <- 0
    topePila <- 0
    
    Repetir
        Escribir ""
        Escribir "======= GESTOR DE PROCESOS Y MEMORIA ======="
        Escribir "1. Insertar proceso"
        Escribir "2. Listar procesos (sin ordenar)"
        Escribir "3. Eliminar proceso por ID"
        Escribir "4. Buscar proceso por ID"
        Escribir "5. Modificar prioridad de un proceso"
        Escribir "6. Ordenar procesos por prioridad (Mayor -> Menor)"
        Escribir "7. Ejecutar (desencolar) proceso con mayor prioridad"
        Escribir "8. Visualizar cola actual (ordenada)"
        Escribir "9. Asignar memoria (push)"
        Escribir "10. Liberar memoria (pop)"
        Escribir "11. Ver estado actual de memoria"
        Escribir "12. Salir"
        Escribir "Seleccione una opción:"
        Leer opcion
        
        Segun opcion Hacer
            1: // Insertar proceso
                Si totalProcesos < 100 Entonces
                    Escribir "Ingrese ID del proceso:"
                    Leer idNuevo
                    Escribir "Ingrese nombre del proceso:"
                    Leer nombre
                    Escribir "Ingrese prioridad (entero):"
                    Leer prioridad
                    
                    totalProcesos <- totalProcesos + 1
                    procesos_id[totalProcesos] <- idNuevo
                    procesos_nombre[totalProcesos] <- nombre
                    procesos_prioridad[totalProcesos] <- prioridad
                    
                    Escribir "Proceso insertado correctamente."
                Sino
                    Escribir "¡Límite máximo de procesos alcanzado!"
                FinSi
                
            2: // Listar procesos sin ordenar
                Si totalProcesos = 0 Entonces
                    Escribir "No hay procesos registrados."
                Sino
                    Escribir "Lista de procesos:"
                    Para i <- 1 Hasta totalProcesos
                        Escribir "ID: ", procesos_id[i], " | Nombre: ", procesos_nombre[i], " | Prioridad: ", procesos_prioridad[i]
                    FinPara
                FinSi
                
            3: // Eliminar proceso por ID
                Si totalProcesos = 0 Entonces
                    Escribir "No hay procesos para eliminar."
                Sino
                    Escribir "Ingrese el ID del proceso a eliminar:"
                    Leer idBuscado
                    encontrado <- -1
                    Para i <- 1 Hasta totalProcesos
                        Si procesos_id[i] = idBuscado Entonces
                            encontrado <- i
                        FinSi
                    FinPara
                    
                    Si encontrado <> -1 Entonces
                        Para i <- encontrado Hasta totalProcesos - 1
                            procesos_id[i] <- procesos_id[i + 1]
                            procesos_nombre[i] <- procesos_nombre[i + 1]
                            procesos_prioridad[i] <- procesos_prioridad[i + 1]
                        FinPara
                        totalProcesos <- totalProcesos - 1
                        Escribir "Proceso eliminado correctamente."
                    Sino
                        Escribir "No se encontró un proceso con ese ID."
                    FinSi
                FinSi
                
            4: // Buscar proceso por ID
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
                    Escribir "No se encontró un proceso con ese ID."
                FinSi
                
            5: // Modificar prioridad
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
                    Escribir "Ingrese nueva prioridad (entero):"
                    Leer prioridadAux
                    procesos_prioridad[encontrado] <- prioridadAux
                    Escribir "Prioridad modificada correctamente."
                Sino
                    Escribir "No se encontró un proceso con ese ID."
                FinSi
                
            6: // Ordenar procesos por prioridad (mayor a menor)
				Si totalProcesos >= 2 Entonces
					Para i <- 1 Hasta totalProcesos - 1
						Para j <- i + 1 Hasta totalProcesos
							Si procesos_prioridad[i] > procesos_prioridad[j] Entonces
								prioridadAux <- procesos_prioridad[i]
								procesos_prioridad[i] <- procesos_prioridad[j]
								procesos_prioridad[j] <- prioridadAux
								
								idAux <- procesos_id[i]
								procesos_id[i] <- procesos_id[j]
								procesos_id[j] <- idAux
								
								nombreAux <- procesos_nombre[i]
								procesos_nombre[i] <- procesos_nombre[j]
								procesos_nombre[j] <- nombreAux
							FinSi
						FinPara
					FinPara
					Escribir "Procesos ordenados por prioridad (menor número = mayor prioridad)."
					Escribir "Lista ordenada:"
					Para i <- 1 Hasta totalProcesos
						Escribir "ID: ", procesos_id[i], " | Nombre: ", procesos_nombre[i], " | Prioridad: ", procesos_prioridad[i]
					FinPara
				Sino
					Escribir "No hay suficientes procesos para ordenar."
				FinSi


                
			7: // Ejecutar proceso con mayor prioridad (menor número)
				Si totalProcesos = 0 Entonces
					Escribir "No hay procesos para ejecutar."
				Sino
					// Buscar índice con prioridad mínima
					Definir indiceMin Como Entero
					indiceMin <- 1
					Para i <- 2 Hasta totalProcesos
						Si procesos_prioridad[i] < procesos_prioridad[indiceMin] Entonces
							indiceMin <- i
						FinSi
					FinPara
					
					// Mostrar proceso a ejecutar
					Escribir "Ejecutando proceso con mayor prioridad:"
					Escribir "ID: ", procesos_id[indiceMin], " | Nombre: ", procesos_nombre[indiceMin], " | Prioridad: ", procesos_prioridad[indiceMin]
					
					// Eliminar proceso desplazando
					Para i <- indiceMin Hasta totalProcesos - 1
						procesos_id[i] <- procesos_id[i + 1]
						procesos_nombre[i] <- procesos_nombre[i + 1]
						procesos_prioridad[i] <- procesos_prioridad[i + 1]
					FinPara
					totalProcesos <- totalProcesos - 1
				FinSi

                
            8: // Visualizar cola actual (ordenada)
                Si totalProcesos = 0 Entonces
					Escribir "La cola está vacía."
				Sino
					// Ordenar antes de mostrar para asegurar orden ascendente por prioridad
					Si totalProcesos >= 2 Entonces
						Para i <- 1 Hasta totalProcesos - 1
							Para j <- i + 1 Hasta totalProcesos
								Si procesos_prioridad[i] > procesos_prioridad[j] Entonces
									prioridadAux <- procesos_prioridad[i]
									procesos_prioridad[i] <- procesos_prioridad[j]
									procesos_prioridad[j] <- prioridadAux
									
									idAux <- procesos_id[i]
									procesos_id[i] <- procesos_id[j]
									procesos_id[j] <- idAux
									
									nombreAux <- procesos_nombre[i]
									procesos_nombre[i] <- procesos_nombre[j]
									procesos_nombre[j] <- nombreAux
								FinSi
							FinPara
						FinPara
					FinSi
					
					Escribir "Cola actual (ordenada por prioridad):"
					Para i <- 1 Hasta totalProcesos
						Escribir "ID: ", procesos_id[i], " | Nombre: ", procesos_nombre[i], " | Prioridad: ", procesos_prioridad[i]
					FinPara
				FinSi

                
            9: // Asignar memoria (push)
                Si topePila < 100 Entonces
                    Escribir "Ingrese ID del proceso para asignar memoria:"
                    Leer bloqueID
                    topePila <- topePila + 1
                    memoria[topePila] <- bloqueID
                    Escribir "Memoria asignada correctamente al proceso."
                Sino
                    Escribir "¡La memoria está llena!"
                FinSi
                
            10: // Liberar memoria (pop)
				Si topePila > 0 Entonces
					Escribir "Liberando memoria del proceso ID: ", memoria[topePila]
					memoria[topePila] <- "" // Aquí limpiamos el valor visiblemente
					topePila <- topePila - 1
				Sino
					Escribir "La memoria ya está vacía."
				FinSi

                
            11: // Ver estado actual de la memoria
                Si topePila = 0 Entonces
                    Escribir "La memoria está vacía."
                Sino
                    Escribir "Estado actual de la memoria:"
                    Para i <- topePila Hasta 1 Con Paso -1
                        Escribir "Posición del proceso ", i, ": ", memoria[i]
                    FinPara
                FinSi
                
            12:
                Escribir "Saliendo del programa."
                
            De Otro Modo:
                Escribir "Opción no válida, intente nuevamente."
        FinSegun
        
    Hasta Que opcion = 12

FinProceso
