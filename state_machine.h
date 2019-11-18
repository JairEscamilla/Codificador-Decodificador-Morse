#ifndef state_machine_h
#define state_machine_h

// Incluyendo las bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

// Enum de los estados de la maquina de estados
typedef enum states{
    LOAD_FILE,
    WAIT,
    ENCODE,
    DECODE,
    FREE_MEMORY,
    FINISH,
    STATE_NUM
} States;
typedef struct def_Arbol{
    double Probabilidad;
    char Letra;
    struct def_Arbol *izq, *der;
} TipoNodo;

// Estructura que contendra etiqueta y funcion
typedef struct StateMachine{    
    States state;
    void (*process)(States* state, TipoNodo* Raiz);
}StateMachine;



void InsertarArbol(TipoNodo **Raiz, double Probabilidad, char Letra);
void BorrarArbol(TipoNodo *Raiz);
// Prototipos de las funciones ejecutables de la maquina de estados
void load_file(States *state, TipoNodo *Raiz);
void wait(States* state, TipoNodo* Raiz);
void encode(States* state, TipoNodo* Raiz);
void decode(States* state, TipoNodo* Raiz);
void free_memory(States* state, TipoNodo* Raiz);
void finish(States* state, TipoNodo* Raiz);

States machine_initialiser(void); // Inicializador de la maquina de estados


#endif // !state_machine_h