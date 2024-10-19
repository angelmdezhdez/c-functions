/********************************************
Un ejemplo aplicativo de estructuras y 
uso de archivos

By
Angel Antonio Mendez Hernandez
*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *proms[18];
int grupos[6];

struct escuela{
    char grupo;
    char turno[11];
};

struct estudiante{
    char nombre[50];
    char promedio[3];
    int edad;
    struct escuela E;
};

int promedios(const char *a){
    int prome;
    for (prome=0; prome<18; prome++){
        if(strcmp(proms[prome], a)==0)
            return prome;
    }
    return -1; //Devuelve -1 si el promedio no esta en la lista
}

int leerEstudiantesDesdeArchivo(const char *nombreArchivo, struct estudiante estudiantes[], int maxEstudiantes) {
    FILE *archivo=fopen(nombreArchivo, "r");
    if(archivo==NULL){
        perror("No se pudo abrir el archivo");
        return -1; //Para indicar si hubo un error
    }
    int num_estudiantes=0;

    while(num_estudiantes<maxEstudiantes &&
           fscanf(archivo, "%s %s %d %c %s",
                  estudiantes[num_estudiantes].nombre,
                  estudiantes[num_estudiantes].promedio,
                  &estudiantes[num_estudiantes].edad,
                  &estudiantes[num_estudiantes].E.grupo,
                  estudiantes[num_estudiantes].E.turno)==5) {
        num_estudiantes++;
    }
    fclose(archivo);
    return num_estudiantes; //Devuelve los estudiantes leidos
}

void escribirEstudiantesEnArchivo(const char *nombreArchivo, struct estudiante estudiantes[], int num_estudiantes){
    FILE *archivoSalida=fopen(nombreArchivo, "w");
    if(archivoSalida==NULL){
        perror("No se pudo abrir el archivo de salida");
        return;
    }
    for(int i=0; i<num_estudiantes; i++){
        fprintf(archivoSalida, "Nombre: %s ", estudiantes[i].nombre);
        fprintf(archivoSalida, "Promedio: %s ", estudiantes[i].promedio);
        fprintf(archivoSalida, "Edad: %d ", estudiantes[i].edad);
        fprintf(archivoSalida, "Grupo: %c ", estudiantes[i].E.grupo);
        fprintf(archivoSalida, "Turno: %s ", estudiantes[i].E.turno);
        fprintf(archivoSalida, "\n");
    }
    fclose(archivoSalida);
    printf("Se escribieron %d alumnos en el archivo de salida.\n", num_estudiantes);
}

//Funcion de comparacion de nombres para qsort
int compararNombres(const void *a, const void *b){
    return strcmp(((struct estudiante *)a)->nombre, ((struct estudiante *)b)->nombre);
}

//Funcion para ordenar por nombres
void ordenar_nombres(struct estudiante estudiantes[], int num_estudiantes){
    qsort(estudiantes, num_estudiantes, sizeof(struct estudiante), compararNombres);
}

//Funcion de comparacion de edades para qsort
int compararEdades(const void *a, const void *b){
    return ((struct estudiante *)a)->edad - ((struct estudiante *)b)->edad;
}

//Funcion para ordenar por edades
void ordenar_edades(struct estudiante estudiantes[], int num_estudiantes){
    qsort(estudiantes, num_estudiantes, sizeof(struct estudiante), compararEdades);
}

//Funcion de comparacion de promedios para qsort
int compararPromedios(const void *a, const void *b) {
    //No tengo idea de porque no funcionaba poniendo todo en el return
    //sin necesidad de definir A y B
    int A = promedios(((struct estudiante *)a)->promedio);
    int B = promedios(((struct estudiante *)b)->promedio);
    return B-A;
}

//Funcion para ordenar por promedios
void ordenar_Promedios(struct estudiante estudiantes[], int num_estudiantes) {
    qsort(estudiantes, num_estudiantes, sizeof(struct estudiante), compararPromedios);
}

//Funcion para contar los estudiantes por grupo
void estudiantesxGrupo(struct estudiante estudiantes[], int num_estudiantes){
    int frecGrupos[6]={0}, g, i;
    //Identificamos el grupo y lo sumamos al contador correspondiente
    //aprovechando el hecho de que los grupos son letras consecutivos
    for(i=0; i<num_estudiantes; i++){
        g=(estudiantes[i].E.grupo);
        frecGrupos[g-65]++;
    }
    printf("Estas son las cantidades de alumnos por grupo: \n");
    for(i=0; i<6;i++){
        printf("Grupo %c: %d\n", i+65, frecGrupos[i]);
    }
}

//Funcion para contar los estudiantes por turno
void estudiantesxTurno(struct estudiante estudiantes[], int num_estudiantes){
    int frecTurnos[2]={0}, i;
    for(i=0; i<num_estudiantes; i++){
        if(strcmp(estudiantes[i].E.turno, "Vespertino")==0)
            frecTurnos[0]++;
        else
            frecTurnos[1]++;
    }
    printf("Estas son las cantidades de alumnos por turno: \nMatutino: %d\nVespertino: %d\n", frecTurnos[1], frecTurnos[0]);
}

//Funcion para dar de baja estudiante
void bajaEstudiante(struct estudiante estudiantes[], int *num_estudiantes) {
    char eliminar[50];
    int i, j;
    printf("Ingrese el nombre del alumno que desea dar de baja: ");
    scanf("%s", eliminar);
    //buscamos al estudiante que hay que eliminar
    for(i=0; i<*num_estudiantes; i++){
        if(strcmp(estudiantes[i].nombre, eliminar)==0)
            break;
    }
    //Una vez que lo encontramos, en esa posicion recorremos todos los
    //estudiantes que sigan, solo le estamos "quitando el lugar", y en
    //consecuencia, al numero de estudiantes le quitamos 1.
    if(i<*num_estudiantes){
        for(j=i; j<(*num_estudiantes-1); j++)
            estudiantes[j]=estudiantes[j+1];
        (*num_estudiantes)--;
        printf("Alumno dado de baja exitosamente.\n");
    }
    else//En caso de que el alumno que ingresen no exista
        printf("Alumno no encontrado.\n");
}

//Funcion para dar de alta estudiante
void altaEstudiante(struct estudiante estudiantes[], int *num_estudiantes){
    //Asignamos las caracteristicas del nuevo estudiante
    printf("Ingrese el nombre del nuevo alumno: ");
    scanf("%s", estudiantes[*num_estudiantes].nombre);
    printf("Ingrese el promedio: ");
    scanf("%s", estudiantes[*num_estudiantes].promedio);
    getchar();
    printf("Ingrese la edad: ");
    scanf("%d", &estudiantes[*num_estudiantes].edad);
    printf("Ingrese el grupo: ");
    scanf(" %c", &estudiantes[*num_estudiantes].E.grupo);
    printf("Ingrese el turno: ");
    scanf("%s", estudiantes[*num_estudiantes].E.turno);
    //Agregamos 1 a la cantidad de estudiantes registrados
    (*num_estudiantes)++;
    printf("Alumno dado de alta exitosamente.\n");
}

int main(int argc, char *argv[]){
    //verificamos que se hayan dado los argumentos necesarios
    if(argc!=3){
        printf("Uso incorrecto, debes dar dos argumentos.\n");
        return 1;
    }
    //Inicializamos los promedios y los grupos, nos sirven para el momento de
    //compararlos y ordenarlos
    proms[0]="F-";
    proms[1]="F";
    proms[2]="F+";
    proms[3]="E-";
    proms[4]="E";
    proms[5]="E+";
    proms[6]="D-";
    proms[7]="D";
    proms[8]="D+";
    proms[9]="C-";
    proms[10]="C";
    proms[11]="C+";
    proms[12]="B-";
    proms[13]="B";
    proms[14]="B+";
    proms[15]="A-";
    proms[16]="A";
    proms[17]="A+";
    grupos[0]='A';
    grupos[1]='B';
    grupos[2]='C';
    grupos[3]='D';
    grupos[4]='E';
    grupos[5]='F';

    char *entrada = argv[1];
    char *salida = argv[2];
    struct estudiante estudiantes[100]; //suponemos que solo habran 100 estudiantes
    int num_estudiantes, bandera=1, opcion;
    //leemos el archivo dado
    num_estudiantes = leerEstudiantesDesdeArchivo(entrada, estudiantes, 100);
    if (num_estudiantes == -1) {
        printf("Error al abrir el archivo de entrada. Código de error: %d (%s)\n", errno, strerror(errno));
        exit(1);
    }
    printf("Se leyeron %d estudiantes.\n", num_estudiantes);
    if(num_estudiantes==0)
        exit(1);
    //comenzamos el ciclo
    while(bandera==1){
        printf("Ingrese la opcion que desee:\n1. Imprimir,\n2. Ordenar por nombre,\n3. ordenar por edad,\n4. Ordenar por promedios,\n5. \
Numero de estudiantes por grupo,\n6. Numero de estudiantes por turno,\n7. Baja estudiante\n8. Alta estudiante\n9. Fin\n");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                escribirEstudiantesEnArchivo(salida, estudiantes, num_estudiantes);
                break;
            case 2:
                ordenar_nombres(estudiantes, num_estudiantes);
                printf("Estudiantes ordenados exitosamente\n");
                break;
            case 3:
                ordenar_edades(estudiantes, num_estudiantes);
                printf("Estudiantes ordenados exitosamente\n");
                break;
            case 4:
                ordenar_Promedios(estudiantes, num_estudiantes);
                printf("Estudiantes ordenados exitosamente\n");
                break;
            case 5:
                estudiantesxGrupo(estudiantes, num_estudiantes);
                break;
            case 6:
                estudiantesxTurno(estudiantes, num_estudiantes);
                break;
            case 7:
                bajaEstudiante(estudiantes, &num_estudiantes);
                break;
            case 8:
                altaEstudiante(estudiantes, &num_estudiantes);
                break;
            case 9:
                escribirEstudiantesEnArchivo(salida, estudiantes, num_estudiantes);
                bandera=0;
                break;
        }
    }
    return 0;
}
