/**
 * @file Funções relativas a stack.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "stack.h"


/**
 * \brief aumenta o tamanho da stack e adiciona o elemento ao inicio da array.
*/
void push(Stack stack,const enum stack_tipo tipo,...){
    stack->comprimento++;
    stack->elemento=realloc(stack->elemento,sizeof(*stack->elemento)*(stack->comprimento+1));
    va_list ap;
    va_start(ap, tipo);
    switch(tipo){
        case STACK_CHAR:
            stack->elemento[stack->comprimento].data.val_c = (char) va_arg(ap, int);
            break;
        case STACK_LONG:
            stack->elemento[stack->comprimento].data.val_l = va_arg(ap, long);
            break;
        case STACK_DOUBLE:
            stack->elemento[stack->comprimento].data.val_d = va_arg(ap, double);
            break;
        case STACK_STRING:
            stack->elemento[stack->comprimento].data.val_s = va_arg(ap, char *);
            break;
        default:
            fprintf(stderr,"erro");
            exit(EXIT_FAILURE);
    }
    stack->elemento[stack->comprimento].tipo=tipo;
    va_end(ap);
}

/**
 * \brief dá push de um elemento completo.
*/
void pushdata (Stack stack,struct stack_elemento a){ 
    switch(a.tipo){
        case STACK_CHAR:
            push(stack,a.tipo,a.data.val_c);
            break;
        case STACK_LONG:
            push(stack,a.tipo,a.data.val_l);
            break;
        case STACK_DOUBLE:
            push(stack,a.tipo,a.data.val_d);
            break;
        case STACK_STRING:
            push(stack,a.tipo,a.data.val_s);
            break;
        default:
            fprintf(stderr,"erro em pushdata");
            exit(EXIT_FAILURE);
    }
}

/**
 * Cria a stack.
 * É utilizado um array onde, a medida que forem dados inputs , eles vão sendo dispostos no array.
 */
Stack create(){
    Stack s = (Stack) malloc(sizeof(struct stack));
    s->elemento = (struct stack_elemento *) malloc(0*sizeof(struct stack_elemento *));
    s->comprimento=-1;
    s->variaveis['A'-65].tipo = STACK_LONG;s->variaveis['A'-65].data.val_l=10;
    s->variaveis['B'-65].tipo = STACK_LONG;s->variaveis['B'-65].data.val_l=11;
    s->variaveis['C'-65].tipo = STACK_LONG;s->variaveis['C'-65].data.val_l=12;
    s->variaveis['D'-65].tipo = STACK_LONG;s->variaveis['D'-65].data.val_l=13;
    s->variaveis['E'-65].tipo = STACK_LONG;s->variaveis['E'-65].data.val_l=14;
    s->variaveis['F'-65].tipo = STACK_LONG;s->variaveis['F'-65].data.val_l=15;

    s->variaveis['N'-65].tipo = STACK_CHAR;s->variaveis['N'-65].data.val_c='\n';
    s->variaveis['S'-65].tipo = STACK_CHAR;s->variaveis['S'-65].data.val_c=' ';

    s->variaveis['X'-65].tipo = STACK_LONG;s->variaveis['X'-65].data.val_l=0;
    s->variaveis['Y'-65].tipo = STACK_LONG;s->variaveis['Y'-65].data.val_l=1;
    s->variaveis['Z'-65].tipo = STACK_LONG;s->variaveis['Z'-65].data.val_l=2;
    return s;
}

/**
 * Liberta posições de memória na stack.
 */
void destroy(Stack stack){
    free(stack->elemento);
    free(stack);
}

/**
 * Verifica qual o tipo do elemento no topo da stack.
 */
enum stack_tipo peek(Stack stack){
    return(stack->elemento[stack->comprimento].tipo);
}

/**
 * Dá-nos verdadeiro caso a stack esteja vazia, caso contrário dá falso.
 */
bool stack_is_empty(Stack stack){
    return (stack->comprimento==-1);
}

/**
 * Função que retira do topo da stack o elemento pretendido.
 * Nesta função temos em atenção o tipo do elemento que queremos retirar,comparando-o com os tipos de elementos existentes na stack.
 * Caso não exista nenhum elemento na stack para se dar pop, ele imprime uma mensagem a dizer que a stack está vazia.
 */
struct stack_elemento pop(Stack stack){
    if (!stack_is_empty(stack)){
        struct stack_elemento a = stack->elemento[stack->comprimento];
        stack->elemento=realloc(stack->elemento,sizeof(*stack->elemento)*(stack->comprimento));
        stack->comprimento--;
        return a;
    }
    else{
        fprintf(stderr,"stack vazia");
        exit(EXIT_FAILURE);
    }
}

/**
 * Função responsável por imprimir os elementos da stack.
 */
void print_stack(Stack stack){
    for (int i =0;i<=stack->comprimento;i++){
        switch(stack->elemento[i].tipo){
            case STACK_CHAR:
                printf("%c",stack->elemento[i].data.val_c);
                break;
            case STACK_LONG:
                printf("%ld",stack->elemento[i].data.val_l);
                break;
            case STACK_DOUBLE:
                printf("%g",stack->elemento[i].data.val_d);
                break;
            case STACK_STRING:
                printf("%s",stack->elemento[i].data.val_s);
                break;
            default:
                fprintf(stderr,"erro no tipo do print_stack");
                exit(EXIT_FAILURE);
        }
    }
    printf("\n");
}