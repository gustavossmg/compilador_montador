#include <stdio.h>

int CodigoInstrucao(char * inst) {
    int cod_inst;
    
    if(inst == "LOAD")
        cod_inst = 1;
    else if(inst == "STORE")
        cod_inst = 2;
    else if(inst == "ADD")
        cod_inst = 3;
    else if(inst == "SUB")
        cod_inst = 4;
    else if(inst == "JMP")
        cod_inst = 5;
    else if(inst == "JPG")
        cod_inst = 6;
    else if(inst == "JPL")
        cod_inst = 7;
    else if(inst == "JPE")
        cod_inst = 8;
    else if(inst == "JPNE")
        cod_inst = 9;
    else if(inst == "PUSH")
        cod_inst = 10;
    else if(inst == "POP")
        cod_inst = 11;
    else if(inst == "READ")
        cod_inst = 12;
    else if(inst == "WRITE")
        cod_inst = 13;
    else if(inst == "CALL")
        cod_inst = 14;
    else if(inst == "RET")
        cod_inst = 15;
    else if(inst == "HALT")
        cod_inst = 16;
    else if(inst == "WORD")
        cod_inst = -1;
    else if(inst == "END")
        cod_inst = -2;
    else
        cod_inst = 0;
    
    return cod_inst;
}


int main( ) {
    FILE *arq;
    arq = fopen("entrada.txt", "rt");
    char linha[100];

    while (!feof(arq)) {
        fgets(linha, 100, arq);
        printf("%s", linha);
    }

    fclose(arq);

    char * exemplo = "END";
    int codigo_exemplo = CodigoInstrucao(exemplo);
    printf("%i\n", codigo_exemplo);

    return 0;
}