#include <stdio.h>
#include <string.h>

int CodigoInstrucao(char * inst) {
    int cod_inst;
    
    if(strcmp(inst, "LOAD") == 0)
        cod_inst = 1;
    else if(strcmp(inst, "STORE") == 0)
        cod_inst = 2;
    else if(strcmp(inst, "ADD") == 0)
        cod_inst = 3;
    else if(strcmp(inst, "SUB") == 0)
        cod_inst = 4;
    else if(strcmp(inst, "JMP") == 0)
        cod_inst = 5;
    else if(strcmp(inst, "JPG") == 0)
        cod_inst = 6;
    else if(strcmp(inst, "JPL") == 0)
        cod_inst = 7;
    else if(strcmp(inst, "JPE") == 0)
        cod_inst = 8;
    else if(strcmp(inst, "JPNE") == 0)
        cod_inst = 9;
    else if(strcmp(inst, "PUSH") == 0)
        cod_inst = 10;
    else if(strcmp(inst, "POP") == 0)
        cod_inst = 11;
    else if(strcmp(inst, "READ") == 0)
        cod_inst = 12;
    else if(strcmp(inst, "WRITE") == 0)
        cod_inst = 13;
    else if(strcmp(inst, "CALL") == 0)
        cod_inst = 14;
    else if(strcmp(inst, "RET") == 0)
        cod_inst = 15;
    else if(strcmp(inst, "HALT") == 0)
        cod_inst = 16;
    else if(strcmp(inst, "WORD") == 0)
        cod_inst = -1;
    else if(strcmp(inst, "END") == 0)
        cod_inst = -2;
    else
        cod_inst = 0;
    
    return cod_inst;
}


int main( ) {
    FILE *arq;
    arq = fopen("entrada.txt", "rt");
    char linha[100];
    char *token;
    const char separador[2] = " ";
    int cod_token;

    printf("MV1 ");

    while (!feof(arq)) {
        fgets(linha, 100, arq);
        token = strtok(linha, separador);
        while( token != NULL ) {
            cod_token =  CodigoInstrucao(token);
            printf("%i ", cod_token);
            token = strtok(NULL, separador);
        } 
    }

    fclose(arq);

    char * exemplo = "END";
    int codigo_exemplo = CodigoInstrucao(exemplo);
    printf("%i\n", codigo_exemplo);

    return 0;
}