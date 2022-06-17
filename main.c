#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int RetornaCodigoInstrucao(char * inst) {
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
        cod_inst = 17;
    else if(strcmp(inst, "END") == 0)
        cod_inst = 18;
    else
        cod_inst = 0;
    
    return cod_inst;
}

typedef struct Simbolos {
    char simbolo[15];
    int endereco;
    struct Simbolos *proximo;
} Simbolos;

int VerificaSimbolo(char * sim, Simbolos *tab) {
    Simbolos *temp = tab;
    while(temp != NULL) {
        if(strcmp(sim, temp->simbolo) == 0) {
            return 1;
        }
        temp = temp->proximo;
    }
    return 0;
}

Simbolos * AdicionaSimbolo(char * sim, Simbolos *tab) {
    if(VerificaSimbolo(sim, tab) == 0) {
        Simbolos *novo_sim;
        novo_sim = (Simbolos *) malloc(sizeof(Simbolos));
        strcpy(novo_sim->simbolo, sim);
        novo_sim->endereco = NULL;
        novo_sim->proximo = NULL;
        
        Simbolos *temp = tab;
        while( (temp != NULL) && (temp->proximo != NULL) ) {
            temp = temp->proximo;
        }
        
        if(temp == NULL) {
            tab = novo_sim;
        } else {
            temp->proximo = novo_sim;
        }
    }
    return tab;
}

Simbolos * AdicionaEndereco(char * sim, int end, Simbolos *tab) {
    tab = AdicionaSimbolo(sim, tab);
    Simbolos *temp = tab;
    while(temp != NULL) {
        if(strcmp(sim, temp->simbolo) == 0) {
            temp->endereco = end;
        }
        temp = temp->proximo;
    }
    return tab;
}

int RetornaEndereco(char * sim, Simbolos *tab) {
    int end;
    Simbolos *temp = tab;
    while(temp != NULL) {
        if(strcmp(sim, temp->simbolo) == 0) {
            end = temp->endereco;
            break;
        }
        temp = temp->proximo;
    }
    return end;
}


int main( ) {
    FILE *arq;
    char linha[100];
    char *token;
    const char separador[2] = " ";
    int cod_token, tam_token;
    int end_atual = 0;
    Simbolos *tabela = NULL;

    arq = fopen("entrada.txt", "rt");
    while (!feof(arq)) {
        fgets(linha, 100, arq);
        linha[strcspn(linha, "\n")] = 0;
        token = strtok(linha, separador);
        if(strchr(token, ':') != NULL) {
            tam_token = strlen(token);
            token[tam_token-1] = '\0';
            tabela = AdicionaEndereco(token, end_atual, tabela);
            token = strtok(NULL, separador);
        }
        cod_token = RetornaCodigoInstrucao(token);
        if(cod_token < 16) {
            token = strtok(NULL, separador);
            tabela = AdicionaSimbolo(token, tabela);
            end_atual = end_atual + 2;
        } else if(cod_token == 16) {
            end_atual = end_atual + 1;
        } else if (cod_token == 17) {
            token = strtok(NULL, separador);
            end_atual = end_atual + 1;
        } else if (cod_token == 18) {
            break;
        }
    }
    fclose(arq);

    int end_var;
    end_atual = 0;
    arq = fopen("entrada.txt", "rt");
    while (!feof(arq)) {
        fgets(linha, 100, arq);
        linha[strcspn(linha, "\n")] = 0;
        token = strtok(linha, separador);
        if(strchr(token, ':') != NULL) {
            token = strtok(NULL, separador);
        }
        cod_token = RetornaCodigoInstrucao(token);
        if(cod_token < 16) {
            end_atual = end_atual + 2;
            printf("%i ", cod_token);
            token = strtok(NULL, separador);
            end_var = RetornaEndereco(token, tabela);
            end_var = end_var - end_atual;
            printf("%i ", end_var);
        } else if(cod_token == 16) {
            end_atual = end_atual + 1;
            printf("%i ", cod_token);
        } else if (cod_token == 17) {
            end_atual = end_atual + 1;
            printf("%i ", 0);
        } else if (cod_token == 18) {
            break;
        }
    }
    fclose(arq);
}