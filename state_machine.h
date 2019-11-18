#ifndef state_machine_h
#define state_machine_h

// Incluyendo las bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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