/**
 * @file ficheiro onde se encontram todos os operadores do nosso programa.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"
#include "operadores.h"
#include "parser.h"

/**
 * @brief funçao responsavel de remover o elemento no topo da array e o colocar na stack
 */
void maismaisR(Stack stack,Stack stk){
    struct stack_elemento a = pop(stk);
    push(stack,STACK_STACK,stk);
    pushdata(stack,a);
}
/**
 * @brief funçao responsavel de remover o elemento no inicio da array e o colocar na stack
 */
void menosmenosR(Stack stack,Stack stk){
    struct stack_elemento a = popL(stk);
    push(stack,STACK_STACK,stk);
    pushdata(stack,a);
}
/**
 * @brief funçao responsavel de remover o ultimo elemento da string e o colocar na stack
 */
void maismaisS(Stack stack,char c[]){
    char a = c[strlen(c)-1];
    c[strlen(c)-1]='\0';
    push(stack,STACK_STRING,c);
    push(stack,STACK_CHAR,a);
}
/**
 * @brief função responsavel de remover o primeiro elemento da string e o colocar na stack
 */
void menosmenosS(Stack stack,char c[]){
    char a = c[0];
    push(stack,STACK_STRING,++c);
    push(stack,STACK_CHAR,a);
}

/** @def maismenos
 * @brief macro para a função maismais e menosmenos.
 */
#define maismenos(stack,a,op){\
    switch (a.tipo){\
    case STACK_DOUBLE:\
        push(stack,a.tipo,(a.data.val_d op 1.0));break;\
    case STACK_LONG:\
        push(stack,a.tipo,(a.data.val_l op 1));break;\
    case STACK_CHAR:\
        push(stack,a.tipo,(a.data.val_c op 1));break;\
    default:break;\
    }\
