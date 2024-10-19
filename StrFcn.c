/********************************************************
Algunas funciones implementadas con strings

By
Angel Antonio Mendez Hernandez
********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int longitud(char *str){
    int counter;
    for(counter=0;str[counter]!='\0';counter++);
    return counter;
}
/* copia caracter por caracter hasta llegar al nulo
o que se acabe el espacio (lo que ocurra primero)*/
char *copia(int n, char *scopy, char *str){
    char *copia1=scopy, *copia2=str;
    int contador=0;
    while (*copia2!='\0' && contador<n-1){
        if (copia1!=copia2){
            *(copia1++)=*(copia2++);
            contador++;
        }
        else{
            printf("Los strings se sobreponen\n");
            return NULL;
        }
    }
    *(copia1)='\0';
    return scopy;
}

int compara(char *s1, char *s2){
	char *str1=s1, *str2=s2;
    while(*str1!='\0' && *str2!='\0'){
        if(*str1!=*str2)
            return *str1-*str2;
        else{
            str1++;
            str2++;
        }
    }
    return 0;
}

int concatena(int n, char *s1, char *s2, char *s3){
    char *ptr[3], *p;
    int i=1;
    ptr[0]=NULL;
    ptr[1]=s2;
    ptr[2]=s3;
    int len_s1 = longitud(s1);
    while(len_s1<n && i<3){
        p = s1 + len_s1;
        *p = ' ';
        p++;
        ptr[0] = copia(n - len_s1, p, ptr[i]);
        len_s1 += longitud(ptr[0])+1;
        i++;
    }
    return longitud(s1);
}

int encuentra(char *s1, char *s2){
    int contador=0, i, j, lim=longitud(s2), lim2=longitud(s1), coincidencia;
    for(i=0;i<=lim-lim2;i++){
        coincidencia=1;
        for(j=0;j<lim2;j++){
            if(s1[j]!=s2[i+j]) {
                coincidencia=0;
                break;
            }
        }
        if(coincidencia) {
            contador++;
        }
    }
    return contador;
}

int **frecuencia(char *s){
    int *caracter, *cuantos, contador, bandera=0, posicion=0, i, j;
    caracter=(int*)malloc(sizeof(int));
    if(caracter==NULL){
        printf("Sin memoria");
        exit(1);
    }
    cuantos=(int*)malloc(sizeof(int));
    if(cuantos==NULL){
        printf("Sin memoria");
        exit(1);
    }
    for(i=0; i<=longitud(s);i++){
        contador=0;
        bandera=1;
        char prueba=s[i];

        for(j=0;j<i;j++){
            if(s[j]==prueba){
                bandera=0;
                break;
            }
        }

        if(bandera){
            // Ajusta el tamaño de los arreglos dinámicos
            caracter=(int *)realloc(caracter, (posicion + 2)*sizeof(int));
            cuantos = (int *)realloc(cuantos, (posicion + 2)*sizeof(int));

            if(caracter==NULL || cuantos==NULL) {
                printf("Sin memoria");
                exit(1);
            }

            caracter[posicion] = prueba;

            for(j=0;j<longitud(s);j++){
                contador+=(s[j]==prueba)?1:0;
            }
            cuantos[posicion]=contador;
            posicion++;
        }
    }
    caracter[posicion]=0;
    cuantos[posicion]=0;
    int **m=(int **)malloc(2*sizeof(int *));
    if (m==NULL) {
        printf("Sin memoria");
        exit(1);
    }

    m[0]=caracter;
    m[1]=cuantos;
    return m;
}

void sinrepetir(char *s){
    int pos1=0, pos2, bandera, j, i, k, len=longitud(s);
    for(i=0;i<=len;i++){
        if(s[i]==' ' || s[i]=='\0'){
            pos2=i;
            bandera=1;
            for(j=pos1;j<pos2;j++){
                for(k=pos1; k<j;k++){
                    if(s[k]==s[j]){
                        bandera=0;
                        break;
                    }
                }
                if(bandera==0){
                    break;
                }
            }
            if(bandera){
                for(j=pos1;j<pos2;j++){
                    printf("%c",s[j]);
                }
                printf("\n");
            }
            pos1=pos2+1;
        }
    }
}


int main()
{
	//Para longitud:
	int l=longitud("Hola");
	printf("%d\n", l);
	//Para copia:
	char str2[]="Hola como estas";
    	char *ptr;
    	char str1[10];
    	ptr=copia(10,str1, str2);
    	printf("%s\n", ptr);
    	
    	//Para compara:
    	char a[]="Hola", b[]="Como";
    	int c=compara(a,b);
    	printf("%d\n", c);
    	
    	//Para concatena:
    	char a1[20]="hola", a2[]="como", a3[]="estas";
    	int l2=concatena(20, a1, a2, a3);
    	printf("%s %d\n", a1, l2);
    	
    	//Para encuentra:
    	char b1[]="esp", b2[]="guitara esp de españa y habla español";
    	int l3=encuentra(b1,b2);
    	printf("%d\n", l3);
    	
    	//Para frecuencia:
    	char frec[]="aaccddddllc";
    	int **arr=frecuencia(frec);
    	for(int i=0; *(*arr+i)!=0; i++){
        	for(int j=0;j<2;j++){
            		if(j%2==0){
                		printf("%c ", *(*(arr+j)+i));
            		}
            		else{
                		printf("%d ", *(*(arr+j)+i));
            		}
        	}
        	printf("\n");
    	}
    	free(arr[0]);
    	free(arr[1]);
    	free(arr);
    	
    	//Para sinrepetir:
    	char frase[]="hola como esta espero que bien";
    	sinrepetir(frase);

  	return 0;
}
