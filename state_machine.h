#ifndef state_machine_h
#define state_machine_h

// Incluyendo las bibliotecas
#include<stdio.h>
#include<stdlib.h>
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

// Estructura que contendra etiqueta y funcion
typedef struct StateMachine{    
    States state;
    void (*process)(States* state);
}StateMachine;

// Prototipos de las funciones ejecutables de la maquina de estados
void load_file(States* state);
void wait(States* state);
void encode(States* state);
void decode(States* state);
void free_memory(States* state);
void finish(States* state);

States machine_initialiser(void); // Inicializador de la maquina de estados


#endif // !state_machine_h