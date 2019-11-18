#include "state_machine.h"

int main(void){
    // Inicializacion de variable de estado al estado inicial.
    static States machine_state = LOAD_FILE;
    TipoNodo* Raiz = NULL;
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
                (*machine[machine_state].process)(&machine_state, &Raiz);
        }
    }

    return 0;
}

void load_file(States* state, TipoNodo** Raiz){
    printf("Cargando archivo...");
    FILE *Archivo;
    char Renglon[100], Letra;
    double Probabilidad;
    Archivo = fopen("ordenletras.txt", "rt");
    if (Archivo == NULL){
        printf("El archivo no existe\n");
        printf("Saliendo del programa...");
        exit(0);
    }else{
        while (fgets(Renglon, 50, Archivo) != NULL){
            Renglon[strlen(Renglon)] = '\0';
            sscanf(Renglon, "%c, %lf", &Letra, &Probabilidad);
            InsertarArbol(Raiz, Probabilidad, Letra);
        }
    }
    fclose(Archivo);
    *state = WAIT;
    printf("Archivo cargado!\n");
}
void wait(States* state, TipoNodo** Raiz){
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
void encode(States* state, TipoNodo** Raiz){
    char mensaje[150], codificado[150], mensajeCodificado[150];
    int i = 0, flag = 0;
    printf("Ingresar frase que desea codificar a morse-> ");
    scanf(" %s", mensaje);
    minusculas(mensaje);
    printf("Codificando mensaje...");
    puts("Mensaje codificado con exito!\n");
    printf("\nEl mensaje condificado es: ");
    while(mensaje[i] != '\0'){
        codificar(mensaje[i], codificado, 0, *Raiz, &flag, mensajeCodificado);
        flag = 0;
        printf("%s ", mensajeCodificado);
        codificado[0] = '\0';
        i++;
    }
    printf("\n");
    *state = WAIT;
}
void codificar(char mensaje, char codificado[], int pos, TipoNodo* Raiz, int* flag, char mensajeCodificado[]){
    if (mensaje == Raiz->Letra){
        *flag = 1;
        strcpy(mensajeCodificado, codificado);
    }
    if(Raiz != NULL && Raiz->Letra != mensaje && *flag == 0){
        if(Raiz->izq != NULL){
            codificado[pos] = '.';
            codificado[pos + 1] = '\0';
            codificar(mensaje, codificado, pos + 1, Raiz->izq, flag, mensajeCodificado);
        }
        if(Raiz->der != NULL){
            codificado[pos] = '-';
            codificado[pos + 1] = '\0';
            codificar(mensaje, codificado, pos + 1, Raiz->der, flag, mensajeCodificado);
        }
    }
}

void minusculas(char mensaje[]){
    int i = 0;
    while (mensaje[i] != '\0'){
        mensaje[i] = tolower(mensaje[i]);
        i++;
    }
}

void decode(States* state, TipoNodo** Raiz){
    printf("Decodificando mensaje...");
    //print_process_bar(5);
    *state = WAIT;
    puts("Mensaje decodificado\n");
}
void free_memory(States* state, TipoNodo** Raiz){
    printf("Liberando memoria...\n");
    BorrarArbol(*Raiz);
    *state = FINISH;
}
void finish(States* state, TipoNodo** Raiz){
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

void InsertarArbol(TipoNodo **Raiz, double Probabilidad, char Letra){
    TipoNodo *Avanza, *Nuevo;
    Avanza = *Raiz;
    if ((Nuevo = (TipoNodo *)malloc(sizeof(TipoNodo))) == NULL){
        printf("No hay memoria\n");
        exit(0);
    }
    Nuevo->Probabilidad = Probabilidad;
    Nuevo->Letra = Letra;
    Nuevo->izq = NULL;
    Nuevo->der = NULL;
    while (Avanza != NULL){
        if (Probabilidad > Avanza->Probabilidad){ // muevete a la derecha
            if (Avanza->der != NULL)
                Avanza = Avanza->der;
            else{
                Avanza->der = Nuevo;
                return;
            }
        }
        if (Probabilidad <= Avanza->Probabilidad){ //muevete a la izquierda
            if (Avanza->izq != NULL)
                Avanza = Avanza->izq;
            else{
                Avanza->izq = Nuevo;
                return;
            }
        }
    }
    Avanza = Nuevo;
    *Raiz = Avanza;
}
void BorrarArbol(TipoNodo* Raiz){
    if (Raiz != NULL){
        BorrarArbol(Raiz->izq);
        BorrarArbol(Raiz->der);
        free(Raiz);
    }
}

