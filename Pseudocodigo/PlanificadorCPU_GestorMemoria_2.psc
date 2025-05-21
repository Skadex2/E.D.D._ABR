Algoritmo PlanificadorCPU_GestorMemoria_SinSubalgoritmos
	
	Definir inicio_j Como Entero
    Definir colaPID, colaPrioridad Como Entero
	Dimension colaPID[100], colaPrioridad[100]
    Definir colaInicio, colaFin Como Entero
	
    colaInicio <- 1
    colaFin <- 0
	
    Definir pilaMemoria Como Entero
	Dimension pilaMemoria[100]
    topePila <- 0
	
    Definir opcion, pid, prioridad, bloqueID, pidBuscar, bloqueBuscar Como Entero
    Definir encontrado Como Logico
    Definir i, j, auxPrioridad, auxPID, pidEjecutado, bloqueLiberado Como Entero
	
    Repetir
        Escribir " "
        Escribir "=== Planificador CPU y Gestor de Memoria ==="
        Escribir "1. Encolar proceso (CPU)"
        Escribir "2. Desencolar y ejecutar proceso"
        Escribir "3. Mostrar cola de procesos"
        Escribir "4. Buscar proceso en cola"
        Escribir "5. Asignar memoria (push)"
        Escribir "6. Liberar memoria (pop)"
        Escribir "7. Mostrar estado de memoria"
        Escribir "0. Salir"
        Escribir "Ingrese opción:"
        Leer opcion
		
        Segun opcion Hacer
            Caso 1:
                Si colaFin = 100 Entonces
                    Escribir "La cola está llena."
                Sino
                    Escribir "Ingrese ID del proceso:"
                    Leer pid
                    Escribir "Ingrese prioridad (menor número = mayor prioridad):"
                    Leer prioridad
                    colaFin <- colaFin + 1
                    colaPID[colaFin] <- pid
                    colaPrioridad[colaFin] <- prioridad
					
                    // Ordenar cola por prioridad (burbuja)
					Si colaFin >= colaInicio + 1 Entonces
                        Para i <- colaInicio Hasta colaFin - 1 Hacer
                            inicio_j <- i + 1
                            Para j <- inicio_j Hasta colaFin Hacer
                                Si colaPrioridad[i] > colaPrioridad[j] Entonces
                                    auxPrioridad <- colaPrioridad[i]
                                    colaPrioridad[i] <- colaPrioridad[j]
                                    colaPrioridad[j] <- auxPrioridad
									
                                    auxPID <- colaPID[i]
                                    colaPID[i] <- colaPID[j]
                                    colaPID[j] <- auxPID
                                FinSi
                            FinPara
                        FinPara
                    FinSi
                    Escribir "Proceso encolado."
                FinSi
            Caso 2:
                Si colaFin < colaInicio Entonces
                    Escribir "No hay procesos para ejecutar."
                Sino
                    pidEjecutado <- colaPID[colaInicio]
                    Para i <- colaInicio Hasta colaFin - 1 Hacer
                        colaPID[i] <- colaPID[i + 1]
                        colaPrioridad[i] <- colaPrioridad[i + 1]
                    FinPara
                    colaFin <- colaFin - 1
                    Escribir "Ejecutando proceso ID: ", pidEjecutado, " ... ¡CPU a toda máquina!"
                FinSi
            Caso 3:
                Si colaFin < colaInicio Entonces
                    Escribir "La cola está vacía."
                Sino
                    Escribir "Cola de procesos (ID - Prioridad):"
                    Para i <- colaInicio Hasta colaFin Hacer
                        Escribir colaPID[i], " - ", colaPrioridad[i]
                    FinPara
                FinSi
            Caso 4:
                Escribir "Ingrese ID a buscar:"
                Leer pidBuscar
                encontrado <- Falso
                Para i <- colaInicio Hasta colaFin Hacer
                    Si colaPID[i] = pidBuscar Entonces
                        encontrado <- Verdadero
                    FinSi
                FinPara
                Si encontrado Entonces
                    Escribir "Proceso encontrado."
                Sino
                    Escribir "Proceso no encontrado."
                FinSi
            Caso 5:
                Si topePila = 100 Entonces
                    Escribir "Pila llena."
                Sino
                    Escribir "Ingrese ID del proceso para asignar en memoria:"
                    Leer bloqueID
                    topePila <- topePila + 1
                    pilaMemoria[topePila] <- bloqueID
                    Escribir "Memoria asignada."
                FinSi
            Caso 6:
                Si topePila = 0 Entonces
                    Escribir "No hay memoria para liberar."
                Sino
                    bloqueLiberado <- pilaMemoria[topePila]
                    topePila <- topePila - 1
                    Escribir "Memoria liberada (bloque ID): ", bloqueLiberado
                FinSi
            Caso 7:
                Si topePila = 0 Entonces
                    Escribir "Pila vacía."
                Sino
                    Escribir "Pila de memoria (de arriba hacia abajo):"
                    Para i<-topePila Hasta 1 Con Paso -1 Hacer
						Escribir pilaMemoria[i]
					Fin Para
                FinSi
            Caso 0:
                Escribir "Saliendo..."
            De Otro Modo:
                Escribir "Opción inválida."
        FinSegun
		
	Hasta que opcion = 0

	
FinAlgoritmo
