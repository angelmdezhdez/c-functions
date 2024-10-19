/*************************************************
Programa para tokenizar strings dado un caracter 
de separacion

By
Angel Antonio Mendez Hernandez
*************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *lectura(){
    char frase[200];
    printf("Ingrese su frase: ");
    fgets(frase,200,stdin);
    frase[strlen(frase)-1]='\0';
    char *ptr=(char*)malloc((strlen(frase)+1)*sizeof(char));
    if(ptr==NULL){
        printf("No hay memoria");
        exit(1);
    }
    strcpy(ptr,frase);
    return ptr;
}

char **token(char *s, char sep){
    int numtokens=0, inicio=0, longitud=0, lim=strlen(s), tnum=0;
    for(int i=0;s[i]!='\0';i++)
        numtokens+=((s[i]==' ')?(1):(0));
    numtokens++;
    char **t=(char **)malloc((numtokens+1)*sizeof(char *));
    if(t==NULL){
        printf("Sin memoria.");
        exit(1);
    }
    for(int i=0;i<=lim;i++){
        if(s[i]==sep || s[i]=='\0'){
            t[tnum]=(char *)malloc(longitud+1);
            if(t[tnum]==NULL){
                printf("Sin memoria.");
                exit(1);
            }
            strncpy(t[tnum],s+inicio,longitud);
            t[tnum][longitud]='\0';
            inicio=i+1;
            longitud=0;
            tnum++;
        }
        else
            longitud++;
    }
    return t;
}

int main(){
    char *str=lectura();
    char sep;
    printf("Ingrese el caracter con el que desea tokenizar: ");
    scanf("%c", &sep);
    char **tok=token(str, sep);
    for(int i=0;tok[i]!=NULL;i++){
        printf("%s ",tok[i]);
        free(tok[i]);
    }
    free(str);
    free(tok);
    return 0;
}
