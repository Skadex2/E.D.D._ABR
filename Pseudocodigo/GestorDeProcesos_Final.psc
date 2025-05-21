Proceso GestorDeProcesos
    Definir procesos_id, procesos_nombre Como Caracter
	Definir procesos_prioridad Como Entero
    Dimension procesos_id[100], procesos_nombre[100], procesos_prioridad[100]
    
    Definir totalProcesos, i, opcion, encontrado Como Entero
    Definir idBuscado, nombre, idNuevo Como Caracter
	Definir prioridad, prioridadNueva Como Entero
	
    totalProcesos <- 0
	
    Repetir
        Escribir ""
        Escribir "======= GESTOR DE PROCESOS ======="
        Escribir "1. Insertar un proceso"
		Escribir "2. Lista de procesos (Sin ordenar)"
		Escribir "3. Eliminar un procesos"
		Escribir "4. Busqueda por ID"
		Escribir "5. Modificar prioridad de un proceso"
		Escribir "6. Ordenar procesos por prioridad(Mayor -> Menor)"
		Escribir "7. Salir"
        Escribir "Seleccione una opción:"
        Leer opcion
		
        Segun opcion Hacer
            1://Insertar
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
                    Escribir "¡Límite máximo de procesos alcanzado!"
                FinSi
				
            2://MOSTRAR
                Si totalProcesos = 0 Entonces
                    Escribir "No hay procesos registrados."
                Sino
                    Escribir "Lista de procesos:"
                    Para i <- 1 Hasta totalProcesos
                        Escribir "ID: ", procesos_id[i], " | Nombre: ", procesos_nombre[i], " | Prioridad: ", procesos_prioridad[i]
                    FinPara
                FinSi
				
			3://ELIMINAR
				Si totalProcesos = 0 Entonces
					Escribir "No hay Procesos para eliminar."
				SiNo
					Escribir "Ingrese el ID del proceso a eliminar:"
					Leer idBuscado
					encontrado <- -1
					Para i <- 1 Hasta totalProcesos
						Si procesos_id[i] = idBuscado Entonces
							encontrado <- i
						FinSi
					FinPara
					
					Si encontrado <> -1 Entonces
						Si encontrado < totalProcesos Entonces
							Para i <- encontrado Hasta totalProcesos - 1
								procesos_id[i] <- procesos_id[i+1]
								procesos_nombre[i] <- procesos_nombre[i+1]
								procesos_prioridad[i] <- procesos_prioridad[i+1]
							FinPara
						FinSi
						totalProcesos <- totalProcesos - 1
						Escribir "Proceso eliminado correctamente."
					Sino
						Escribir "No se encontró un proceso con ese ID."
					FinSi
				FinSi
                	
				
            4: //Buscar
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

				
            5://MODIFICAR
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
                    Escribir "No se encontró un proceso con ese ID."
                FinSi
				
            6://Ordenamiento
                Para i <- 1 Hasta totalProcesos - 1
                    Para j <- i + 1 Hasta totalProcesos
                        Si procesos_prioridad[i] < procesos_prioridad[j] Entonces
                            prioridad <- procesos_prioridad[i]
                            procesos_prioridad[i] <- procesos_prioridad[j]
                            procesos_prioridad[j] <- prioridad
                            idBuscado <- procesos_id[i]
                            procesos_id[i] <- procesos_id[j]
                            procesos_id[j] <- idBuscado
                            nombre <- procesos_nombre[i]
                            procesos_nombre[i] <- procesos_nombre[j]
                            procesos_nombre[j] <- nombre
                        FinSi
                    FinPara
                FinPara
                Escribir "Procesos ordenados por prioridad (mayor a menor)."    
				
            7://SALIR
                Escribir "Saliendo del programa..."
				
            De Otro Modo:
                Escribir "Opción no válida. Intente nuevamente."
        FinSegun
		
    Hasta Que opcion = 7
	
FinProceso
