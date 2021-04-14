/**
 * @file Ficheiro onde é processado o input dado pelo utilizador.
 */
#include "parser.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"
#include "operadores.h"


/**
 * \brief função que trata dos casos e(algo)
*/
void leituraE(Stack stack,char c){
    switch(c){
        case '>':
            maiorb(stack);
            break;
        case '<':
            menorb(stack);
            break;
        case '|':
            ou(stack);
            break;
        case '&':
            e(stack);
            break;
        default: 
            break;
    }
}
/**
 * \brief função que trata dos casos de Binarios
*/
int leituraOperacoesBinarias(Stack stack,char c){
    int Bool=0;
    switch(c){
        case '&':
            conjuncao(stack);
            Bool=1;
            break;
        case '|':
            disjuncao(stack);
            Bool=1;
            break;
        case '^':
            xor(stack);
            Bool=1;
            break;
        case '~':
            not(stack);
            Bool=1;
            break;
        default:
            break;
    }
    return Bool;
}

/**
 * \brief função que trata dos casos de operadores de contas
*/
int leituraOperacoesContas(Stack stack,char c){
    int Bool=0;
    switch (c) {
        case '%':
            restoDivisao(stack);
            Bool=1;
            break;
        case '#':
            expoente(stack);
            Bool=1;
            break;
        case '+':
            mais(stack);
            Bool=1;
            break;
        case '-': 
            menos(stack);
            Bool=1;
            break;
        case '*':
            mult(stack);
            Bool=1;
            break;
        case '/': 
            divisao(stack);
            Bool=1;
            break;
        case ')':
            maismais(stack);
            Bool=1;
            break;
        case '(':
            menosmenos(stack);
            Bool=1;
            break;
    }
    return Bool;
}
/**
 * \brief função que trata dos casos de operadores sobre a stack
*/
int leituraOperacoesStack(Stack stack,char c[]){
    int Bool=0;
    switch (c[0]) {
        case '_':
            duplica(stack);
            Bool=1;
            break;
        case '$':
            copian(stack);
            Bool=1;
            break;
        case '\\':
            trocar(stack);
            Bool=1;
            break;
        case '@':
            rodar(stack);
            Bool=1;
            break;
        case ';':
            pop(stack);
            Bool=1;
            break;
        case ':':
            stack2var(stack,c[1]);
            Bool=1;
            break;
        default:
            break;
    }
    return Bool;
}
/**
 * \brief função que trata dos casos de operadores de conversões
*/
int leituraOperacoesConversoes(Stack stack,char c){
    int Bool=0;
    switch (c) {
        case 'i':
            convL(stack);
            Bool=1;
            break;
        case 'f':
            convD(stack);
            Bool=1;
            break;
        case 'c':
            convC(stack);
            Bool=1;
            break;
        default:
            break;
    }
    return Bool;
}
/**
 * \brief função que trata dos casos de operadores de Condições
*/
int leituraOperacoesCondicionais(Stack stack,char c[]){
    int Bool=0;
    switch (c[0]) {
        case '?':
            ifthenelse(stack);
            Bool=1;
            break;
        case '=':
            igual(stack);
            Bool=1;
            break;
        case '<':
            menor(stack);
            Bool=1;
            break;
        case '>':
            maior(stack);
            Bool=1;
            break;
        case '!':
            notb(stack);
            Bool=1;
            break;
        case 'e':
            leituraE(stack,c[1]);
            Bool=1;
            break;
        default:
            break;
    }
    return Bool;
}



/**
 * \brief função que trata dos casos de operadores
*/
void leituraCasos(Stack stack,char c[]){
    char str2[32];
    int Bool=0;
    if (!Bool) Bool=leituraOperacoesBinarias(stack,c[0]);
    if (!Bool) Bool=leituraOperacoesContas(stack,c[0]);
    if (!Bool) Bool=leituraOperacoesStack(stack,c);
    if (!Bool) Bool=leituraOperacoesConversoes(stack,c[0]);
    if (!Bool) Bool=leituraOperacoesCondicionais(stack,c);
    if (c[0]=='l' && !Bool){
        assert(scanf("\n%32[^\n]",str2)==1);
        push(stack,STACK_STRING,str2);
        }
    else if (!Bool){ 
        fprintf(stderr,"caracter desconhecido");
        exit(EXIT_FAILURE);
    }

}
/**
 * \brief função que trata de guardar a string como double,long,variavel ou se é um operador
*/
void leitura2(Stack stack,char c[]){
    int a=1;
    unsigned i;
    for (i=0;i<strlen(c);i++){
        if (c[i] == '.'){ // condição que verifica se corresponde a um número ou a um operador
            push(stack,STACK_DOUBLE,atof(c));
            a=0;
            break;}
    }
    if (a){
        for (i=0;i<strlen(c);i++){
            if (c[i] <= '9' && c[i]>='0'){ // condição que verifica se corresponde a um número ou a um operador
                push(stack,STACK_LONG,atoi(c));
                a=0;
                break;}
        }
    }
    if (a){ // a cada operador faz corresponder a sua função
        if (c[0]<='Z' && c[0]>='A') var2stack(stack,c[0]);
        else leituraCasos(stack,c);
    }    
}

/**
 * Esta é a função que trata da leitura do input do user
 * Esta separa-o por espaços e a cada conjunto de elemento envia-os para a leitura2 para serem processados
*/
void leitura (Stack stack){
    char str[1024];
    assert(scanf("%1024[^\n]",str)==1);//lê a linha inserida pelo utilizador e guarda-a em str
    char* token;
    char* rest = str; 
    while ((token = strtok_r(rest, " ", &rest))){ // separa a string por espaçoes e manda para a auxiliar leitura2 cada um dos numeros
        leitura2(stack,token);
    }
}