#include "state_machine.h"

int main(void){
    // Inicializacion de variable de estado al estado inicial.
    static States MachineState = LOAD_FILE;
    TipoNodo* Raiz = NULL;
    // Instancia de pares {Label,funcion} de la maquina de estados.
    StateMachine Machine[] = {
        {LOAD_FILE, LoadFile},
        {WAIT, Wait},
        {ENCODE, Encode},
        {DECODE, Decode},
        {FREE_MEMORY, FreeMemory},
        {FINISH, Finish}
    };

    for(;;){
        if(MachineState > STATE_NUM){
            puts("Error");
            return 0;
        }else{
            // Manda Ejecutar la funcion machine.process() correspondiente a la etiqueta MachineState.
                (*Machine[MachineState].process)(&MachineState, &Raiz);
        }
    }

    return 0;
}

void LoadFile(States* State, TipoNodo** Raiz){
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
    *State = WAIT;
    printf("Archivo cargado!\n");
}
void Wait(States* State, TipoNodo** Raiz){
    int Opcion;
    printf("(1) Codificar mensaje.\n(2) Decodificar mensaje.\n(3) Salir.\nIngresar opción-> ");
    scanf("%d", &Opcion);
    switch(Opcion){
        case 1: 
            *State = ENCODE;
            break;
        case 2: 
            *State = DECODE;
            break;
        case 3: 
            *State = FREE_MEMORY;
            break;
        default: 
            printf("Esta opción no existe!");
    }
}
void Encode(States* State, TipoNodo** Raiz){
    char Mensaje[150], Codificado[150], MensajeCodificado[150];
    int i = 0, Flag = 0;
    printf("Ingresar frase que desea codificar a morse-> ");
    scanf(" %s", Mensaje);
    Minusculas(Mensaje);
    printf("Codificando mensaje...");
    puts("Mensaje codificado con éxito!\n");
    printf("\nEl mensaje condificado es: ");
    while(Mensaje[i] != '\0'){
        Codificar(Mensaje[i], Codificado, 0, *Raiz, &Flag, MensajeCodificado);
        Flag = 0;
        printf("%s ", MensajeCodificado);
        Codificado[0] = '\0';
        i++;
    }
    printf("\n");
    *State = WAIT;
}
void Codificar(char Mensaje, char Codificado[], int Pos, TipoNodo* Raiz, int* Flag, char MensajeCodificado[]){
    if (Mensaje == Raiz->Letra){
        *Flag = 1;
        strcpy(MensajeCodificado, Codificado);
    }
    if(Raiz != NULL && Raiz->Letra != Mensaje && *Flag == 0){
        if(Raiz->izq != NULL){
            Codificado[Pos] = '.';
            Codificado[Pos + 1] = '\0';
            Codificar(Mensaje, Codificado, Pos + 1, Raiz->izq, Flag, MensajeCodificado);
        }
        if(Raiz->der != NULL){
            Codificado[Pos] = '-';
            Codificado[Pos + 1] = '\0';
            Codificar(Mensaje, Codificado, Pos + 1, Raiz->der, Flag, MensajeCodificado);
        }
    }
}

void Minusculas(char Mensaje[]){
    int i = 0;
    while (Mensaje[i] != '\0'){
        Mensaje[i] = tolower(Mensaje[i]);
        i++;
    }
}

void Decode(States* State, TipoNodo** Raiz){
    printf("Decodificando mensaje...");
    //PrintProcessBar(5);
    *State = WAIT;
    puts("Mensaje decodificado\n");
}
void FreeMemory(States* State, TipoNodo** Raiz){
    printf("Liberando memoria...\n");
    BorrarArbol(*Raiz);
    *State = FINISH;
}
void Finish(States* State, TipoNodo** Raiz){
    printf("Saliendo del programa...\n");
    //PrintProcessBar(3);
    exit(0);
}

void PrintProcessBar(size_t Time){
    size_t Temp;
    for (Temp = 0; Temp < Time; Temp++){
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

