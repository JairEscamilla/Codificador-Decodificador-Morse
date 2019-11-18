#include "state_machine.h"

int main(void){
    // Inicializacion de variable de estado al estado inicial.
    static States machine_state = LOAD_FILE;
    // Instancia de pares {Label,funcion} de la maquina de estados.
    StateMachine machine[] = {
        {LOAD_FILE, load_file},
        {WAIT, wait},
        {ENCODE, encode},
        {DECODE, decode},
        {FREE_MEMORY, free_memory},
        {FINISH, finish}
    };

    for(;;){
        if(machine_state > STATE_NUM){
            puts("Error");
            return 0;
        }else{
            // Manda Ejecutar la funcion machine.process() correspondiente a la etiqueta machine_state.
            (*machine[machine_state].process)(&machine_state);
        }
    }

    return 0;
}

void load_file(States* state){
    printf("Cargando archivo...");
    *state = WAIT;
    printf("Archivo cargado!\n");
}
void wait(States* state){
    int opcion;
    printf("(1) Codificar mensaje.\n(2) Decodificar mensaje.\n(3) Salir.\nIngresar opcion-> ");
    scanf("%d", &opcion);
    switch(opcion){
        case 1: 
            *state = ENCODE;
            break;
        case 2: 
            *state = DECODE;
            break;
        case 3: 
            *state = FREE_MEMORY;
            break;
        default: 
            printf("Esta opcion no existe!");
    }
}
void encode(States* state){
    printf("Codificando mensaje...");
    //print_process_bar(5);
    *state = WAIT;
    puts("Mensaje codificado\n");
}
void decode(States* state){
    printf("Decodificando mensaje...");
    //print_process_bar(5);
    *state = WAIT;
    puts("Mensaje decodificado\n");
}
void free_memory(States* state){
    printf("Liberando memoria...\n");
    //print_process_bar(5);
    *state = FINISH;
}
void finish(States* state){
    printf("Saliendo del programa...\n");
    //print_process_bar(3);
    exit(0);
}

void print_process_bar(size_t time){
    size_t temp;
    for (temp = 0; temp < time; temp++){
        printf(".");
        sleep(1);
    }
}