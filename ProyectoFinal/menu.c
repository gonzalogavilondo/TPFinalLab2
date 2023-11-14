#include "menu.h"

///PRINTF MENU PRINCIPAL
void imprimirCabecera(char cabecera[]){
    printf("\t\t%s     \n",cabecera);
    printf("%c", 219);
    for(int i=0;i<=70;i++){
        printf("%c",220);
    }
    printf("%c",219);
}

void cabeza(char a[]){
    imprimirCabecera(a);
}

void Rectangulo(){
    system("color F4");
    int lado=15;
    int base=73;
    int i=0;
    while(i<base){
        printf("%c",220);
        i++;
    }
    i=0;
    while(i<lado){
        printf("\n%c\t\t\t\t\t\t\t\t\t%c",219,219);
        i++;
    }
    i=0;
    printf("\n");
    printf("%c",219);
    while(i<base-2){
        printf("%c",220);
        i++;
    }
    printf("%c",219);

}
