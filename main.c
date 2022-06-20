#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int RetornaCodigoInstrucao(char * instrucao) {
    int codigo_instrucao;
    
    if(strcmp(instrucao, "LOAD") == 0)
        codigo_instrucao = 1;
    else if(strcmp(instrucao, "STORE") == 0)
        codigo_instrucao = 2;
    else if(strcmp(instrucao, "ADD") == 0)
        codigo_instrucao = 3;
    else if(strcmp(instrucao, "SUB") == 0)
        codigo_instrucao = 4;
    else if(strcmp(instrucao, "JMP") == 0)
        codigo_instrucao = 5;
    else if(strcmp(instrucao, "JPG") == 0)
        codigo_instrucao = 6;
    else if(strcmp(instrucao, "JPL") == 0)
        codigo_instrucao = 7;
    else if(strcmp(instrucao, "JPE") == 0)
        codigo_instrucao = 8;
    else if(strcmp(instrucao, "JPNE") == 0)
        codigo_instrucao = 9;
    else if(strcmp(instrucao, "PUSH") == 0)
        codigo_instrucao = 10;
    else if(strcmp(instrucao, "POP") == 0)
        codigo_instrucao = 11;
    else if(strcmp(instrucao, "READ") == 0)
        codigo_instrucao = 12;
    else if(strcmp(instrucao, "WRITE") == 0)
        codigo_instrucao = 13;
    else if(strcmp(instrucao, "CALL") == 0)
        codigo_instrucao = 14;
    else if(strcmp(instrucao, "RET") == 0)
        codigo_instrucao = 15;
    else if(strcmp(instrucao, "HALT") == 0)
        codigo_instrucao = 16;
    else if(strcmp(instrucao, "WORD") == 0)
        codigo_instrucao = 17;
    else if(strcmp(instrucao, "END") == 0)
        codigo_instrucao = 18;
    else
        codigo_instrucao = 0;
    
    return codigo_instrucao;
}

typedef struct Simbolos {
    char s_simbolo[15];
    int s_endereco;
    struct Simbolos *proximo;
} Simbolos;

int VerificaSimbolo(char * simbolo, Simbolos *tabela) {
    while(tabela != NULL) {
        if(strcmp(simbolo, tabela->s_simbolo) == 0) {
            return 1;
        }
        tabela = tabela->proximo;
    }
    return 0;
}

Simbolos * AdicionaSimbolo(char * simbolo, Simbolos *tabela) {
    if(VerificaSimbolo(simbolo, tabela) == 0) {
        Simbolos *novo_simbolo;
        novo_simbolo = (Simbolos *) malloc(sizeof(Simbolos));
        strcpy(novo_simbolo->s_simbolo, simbolo);
        novo_simbolo->s_endereco = -1;
        novo_simbolo->proximo = NULL;
        
        Simbolos *temp = tabela;
        while( (temp != NULL) && (temp->proximo != NULL) ) {
            temp = temp->proximo;
        }
        
        if(temp == NULL) {
            tabela = novo_simbolo;
        } else {
            temp->proximo = novo_simbolo;
        }
    }
    return tabela;
}

Simbolos * AdicionaEndereco(char * simbolo, int endereco, Simbolos *tabela) {
    tabela = AdicionaSimbolo(simbolo, tabela);
    Simbolos *temp = tabela;
    while(temp != NULL) {
        if(strcmp(simbolo, temp->s_simbolo) == 0) {
            temp->s_endereco = endereco;
        }
        temp = temp->proximo;
    }
    return tabela;
}

int RetornaEndereco(char * simbolo, Simbolos *tabela) {
    int endereco;
    while(tabela != NULL) {
        if(strcmp(simbolo, tabela->s_simbolo) == 0) {
            endereco = tabela->s_endereco;
            break;
        }
        tabela = tabela->proximo;
    }
    return endereco;
}


int main(int argc, char *argv[ ]) {
    
    // Primeiro Passo do Montador
    
    FILE *arquivo_entrada;
    char linha[100];
    char *token;
    const char separador[2] = " ";
    int codigo_token, tamanho_token;
    int posicao_atual = 0;
    Simbolos *tabela = NULL;

    arquivo_entrada = fopen("entrada.txt", "rt");
    while (!feof(arquivo_entrada)) {
        fgets(linha, 100, arquivo_entrada);
        linha[strcspn(linha, "\n")] = 0;
        token = strtok(linha, separador);
        if(strchr(token, ':') != NULL) {
            tamanho_token = strlen(token);
            token[tamanho_token-1] = '\0';
            tabela = AdicionaEndereco(token, posicao_atual, tabela);
            token = strtok(NULL, separador);
        }
        codigo_token = RetornaCodigoInstrucao(token);
        if(codigo_token < 16) {
            token = strtok(NULL, separador);
            tabela = AdicionaSimbolo(token, tabela);
            posicao_atual = posicao_atual + 2;
        } else if(codigo_token == 16) {
            posicao_atual = posicao_atual + 1;
        } else if (codigo_token == 17) {
            token = strtok(NULL, separador);
            posicao_atual = posicao_atual + 1;
        } else if (codigo_token == 18) {
            break;
        }
    }
    fclose(arquivo_entrada);


    // Segundo Passo do Montador

    FILE *arquivo_saida;
    int posicao_operando_label, endereco_inicial, pilha_inicial;
    char cabecalho[4] = "MV1";
    
    endereco_inicial = 0;
    pilha_inicial = 999;

    arquivo_entrada = fopen("entrada.txt", "rt");
    arquivo_saida = fopen(argv[1], "w");

    fprintf(arquivo_saida, "%s ", cabecalho);
    fprintf(arquivo_saida, "%i ", endereco_inicial);
    fprintf(arquivo_saida, "%i ", pilha_inicial);
    fprintf(arquivo_saida, "%i ", posicao_atual);

    posicao_atual = 0;

    while (!feof(arquivo_entrada)) {
        fgets(linha, 100, arquivo_entrada);
        linha[strcspn(linha, "\n")] = 0;
        token = strtok(linha, separador);
        if(strchr(token, ':') != NULL) {
            token = strtok(NULL, separador);
        }
        codigo_token = RetornaCodigoInstrucao(token);
        if(codigo_token < 15) {
            posicao_atual = posicao_atual + 2;
            fprintf(arquivo_saida, "%i ", codigo_token);
            token = strtok(NULL, separador);
            posicao_operando_label = RetornaEndereco(token, tabela);
            posicao_operando_label = posicao_operando_label - posicao_atual;
            fprintf(arquivo_saida, "%i ", posicao_operando_label);
        } else if(codigo_token < 17) {
            posicao_atual = posicao_atual + 1;
            fprintf(arquivo_saida, "%i ", codigo_token);
        } else if (codigo_token == 17) {
            posicao_atual = posicao_atual + 1;
            fprintf(arquivo_saida, "%i ", 0);
        } else if (codigo_token == 18) {
            break;
        }
    }
    fclose(arquivo_entrada);
    fclose(arquivo_saida);    
}