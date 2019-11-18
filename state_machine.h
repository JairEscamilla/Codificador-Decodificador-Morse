#ifndef state_machine_h
#define state_machine_h

// Incluyendo las bibliotecas
#include<stdio.h>
#include<stdlib.h>

// Enum de los estados de la maquina de estados
typedef enum states{
    LOAD_FILE,
    WAIT,
    ENCODE,
    DECODE,
    FREE_MEMORY,
    FINISH
}States;

// Estructura que contendra etiqueta y funcion
typedef struct StateMachine{
    States state;
    void (*process)(States* state);
}StateMachine;

// Prototipos de las funciones ejecutables de la maquina de estados
void load_file();
void wait();
void encode();
void decode();
void free_memory();
void finish();

States machine_initialiser(void); // Inicializador de la maquina de estados


#endif // !state_machine_h