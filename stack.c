/**
 * @file Funções relativas a stack.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "stack.h"
#include "operadores.h"

/**
 * \brief aumenta o tamanho da stack e adiciona o elemento ao inicio da array.
*/
void push(Stack stack,const enum stack_tipo tipo,...){
    Stack stk;
    stack->elemento=realloc(stack->elemento,sizeof(*stack->elemento)*((++stack->comprimento)+1));
    va_list ap;
    va_start(ap, tipo);
    switch(tipo){
        case STACK_CHAR:
            stack->elemento[stack->comprimento].data.val_c = (char) va_arg(ap, int);break;
        case STACK_LONG:
            stack->elemento[stack->comprimento].data.val_l = va_arg(ap, long);break;
        case STACK_DOUBLE:
            stack->elemento[stack->comprimento].data.val_d = va_arg(ap, double);break;
        case STACK_STRING:
            stack->elemento[stack->comprimento].data.val_s = strdup(va_arg(ap, char *));break;
        case STACK_STACK:
            stk = va_arg(ap, Stack);
            stack->elemento[stack->comprimento].data.stk = create(stack);
            colocartodos(stack->elemento[stack->comprimento].data.stk,stk);break;
        default:
            fprintf(stderr,"erro");exit(EXIT_FAILURE);
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
            push(stack,a.tipo,a.data.val_c);break;
        case STACK_LONG:
            push(stack,a.tipo,a.data.val_l);break;
        case STACK_DOUBLE:
            push(stack,a.tipo,a.data.val_d);break;
        case STACK_STRING:
            push(stack,a.tipo,a.data.val_s);break;
        case STACK_STACK:
            push(stack,a.tipo,a.data.stk);break;
        default:
            fprintf(stderr,"erro em pushdata");exit(EXIT_FAILURE);
    }
}
/**
 * Cria uma stack.
 * É utilizado um array onde, a medida que forem dados inputs , eles vão sendo dispostos no array.
 */
Stack create(Stack stack){
    Stack s = (Stack) malloc(sizeof(StackC));
    s->elemento = (struct stack_elemento *) malloc(0*sizeof(struct stack_elemento *));
    s->comprimento=-1;
    copyVariaveis(s,stack);
    return s;
}
/**
* @brief Dá um elemento pertence a stack com esse determinado tipo.
*/
struct stack_elemento setvar(const enum stack_tipo tipo,...){
    va_list ap;
    va_start(ap, tipo);
    struct stack_elemento a;
    switch(tipo){
        case STACK_LONG:
            a.data.val_l  = va_arg(ap, long);break;
        case STACK_CHAR:
            a.data.val_c = (char) va_arg(ap, int);break;
        default:break;
    }
    a.tipo=tipo;
    return a;
    va_end(ap);
}


/**
 * Cria a stack.
 * É utilizado um array onde, a medida que forem dados inputs , eles vão sendo dispostos no array.
 */
Stack createP(){
    Stack s = (Stack) malloc(sizeof(StackC));
    s->elemento = (struct stack_elemento *) malloc(0*sizeof(struct stack_elemento *));
    s->comprimento=-1;
    s->variaveis['A'-65] = setvar(STACK_LONG,10);
    s->variaveis['B'-65] = setvar(STACK_LONG,11);
    s->variaveis['C'-65] = setvar(STACK_LONG,12);
    s->variaveis['D'-65] = setvar(STACK_LONG,13);
    s->variaveis['E'-65] = setvar(STACK_LONG,14);
    s->variaveis['F'-65] = setvar(STACK_LONG,15);
    s->variaveis['N'-65] = setvar(STACK_CHAR,'\n');
    s->variaveis['S'-65] = setvar(STACK_CHAR,' ');
    s->variaveis['X'-65] = setvar(STACK_LONG,0);
    s->variaveis['Y'-65] = setvar(STACK_LONG,1);
    s->variaveis['Z'-65] = setvar(STACK_LONG,2);
    return s;
}
/**
 * @brief Liberta posições de memória na stack.
 */
void destroy(Stack stack){
    free(stack->elemento);
    free(stack);
}
/**
 * @brief Verifica qual o tipo do elemento no topo da stack.
 */
enum stack_tipo peek(Stack stack){
    return(stack->elemento[stack->comprimento].tipo);
}
/**
 * @brief Dá-nos verdadeiro caso a stack esteja vazia, caso contrário dá falso.
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
        fprintf(stderr,"stack vazia");exit(EXIT_FAILURE);
    }
}
/**
 * @brief Função responsável por imprimir os elementos da stack.
 */
void print_stack(Stack stack){
    for (int i =0;i<=stack->comprimento;i++){
        print_elemento(stack->elemento[i]);
    }
}
/**
 * @brief mostra um elemento da stack 
 */
void print_elemento(struct stack_elemento a){
        switch(a.tipo){
            case STACK_CHAR:
                printf("%c",a.data.val_c);break;
            case STACK_LONG:
                printf("%d",(int)a.data.val_l);break;
            case STACK_DOUBLE:
                printf("%g",a.data.val_d);break;
            case STACK_STRING:
                printf("%s",a.data.val_s);break;
            case STACK_STACK:
                print_stack(a.data.stk);break;
            default:
                fprintf(stderr,"erro no tipo do print_elemento");exit(EXIT_FAILURE);
        }
    }
/**
 * @brief devolve o comprimento de uma stack
 */
int stacklen(Stack stack){
    return stack->comprimento;
}
/**
 * Função que retira do fundo da stack o elemento pretendido.
 * Nesta função temos em atenção o tipo do elemento que queremos retirar,comparando-o com os tipos de elementos existentes na stack.
 * Caso não exista nenhum elemento na stack para se dar pop, ele imprime uma mensagem a dizer que a stack está vazia.
 */
struct stack_elemento popL(Stack stack){
    struct stack_elemento a;
    if (!stack_is_empty(stack)){
        a = stack->elemento[0];
        stack->elemento+=1;
        stack->comprimento--;
    }
    else{
        fprintf(stderr,"stack vazia");exit(EXIT_FAILURE);
    }
    return a;
}

/**
 * @brief copia as variaveis de uma stack para outra
 */
void copyVariaveis(Stack stack,Stack stk){
    for (int i=0;i<26;i++){
        stack->variaveis[i]=stk->variaveis[i];
    }
}