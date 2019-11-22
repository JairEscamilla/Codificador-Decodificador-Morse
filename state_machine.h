/*
 * @author: César Mauricio Arellano Velásquez, Allan Jair Escamilla Hernández, Raúl González Portillo.
 * @date:   19/Noviembre/2019
 * @file:   state_machine.h
 * @brief:  Motor de la máquina de estados.
 */
#ifndef state_machine_h
#define state_machine_h

// Incluyendo las bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// Enum de los estados de la maquina de estados
typedef enum States{
    LOAD_FILE,
    WAIT,
    ENCODE,
    DECODE,
    FREE_MEMORY,
    FINISH,
    STATE_NUM
} States;

//Estructura árbol binario.
typedef struct DefArbol{
    double Probabilidad;
    char Letra;
    struct DefArbol *izq, *der;
} TipoNodo;

// Estructura que contendra etiqueta y funcion
typedef struct StateMachine{
    States State;
    void (*process)(States* State, TipoNodo** Raiz);
}StateMachine;


// Estructuras de las funciones
int VerificacionEntradaDecode(char Codificado[]);
void InsertarArbol(TipoNodo **Raiz, double Probabilidad, char Letra);
void BorrarArbol(TipoNodo *Raiz);
void Codificar(char Mensaje, char Codificado[], int Pos, TipoNodo *Raiz, int *Flag, char MensajeCodificado[]);
void Minusculas(char Mensaje[]);
// Prototipos de las funciones ejecutables de la maquina de estados
void LoadFile(States *State, TipoNodo** Raiz);
void Wait(States* State, TipoNodo** Raiz);
void Encode(States* State, TipoNodo** Raiz);
void Decode(States* State, TipoNodo** Raiz);
void FreeMemory(States* State, TipoNodo** Raiz);
void Finish(States* State, TipoNodo** Raiz);

States MachineInitialiser(void); // Inicializador de la maquina de estados


#endif // !state_machine_h
