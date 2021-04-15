/**
 * @file ficheiro onde se encontram todos os operadores do nosso programa.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"
#include "operadores.h"     
#define maismenos(stack,op){\
    struct stack_elemento a = pop(stack);\
    switch (a.tipo){\
    case STACK_DOUBLE:\
        push(stack,a.tipo,(a.data.val_d op 1.0));break;\
    case STACK_LONG:\
        push(stack,a.tipo,(a.data.val_l op 1));break;\
    case STACK_CHAR:\
        push(stack,a.tipo,(a.data.val_c op 1));break;\
    default:break;\
    }\
} 
/**
* \brief equivalente a ++ de c.
*/
void maismais(Stack stack){
    maismenos(stack,+);
}
/**
 * \brief equivalente a -- de c.
*/
void menosmenos(Stack stack){
    maismenos(stack,-);
}
/**
 *\brief função que recebe da stack um elemento e devolve esse elemento em double.
 */
double toD (struct stack_elemento a){
    return (a.tipo==STACK_DOUBLE?(a.data.val_d):(a.data.val_l*1.0));
}
#define contas(stack, op){\
    struct stack_elemento a = pop(stack);\
    struct stack_elemento b = pop(stack);\
    if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,b.data.val_l op a.data.val_l);\
    else push(stack,STACK_DOUBLE,toD(b) op toD(a));\
}
/**
 * \brief equivalente à soma de dois valores.
*/
void mais(Stack stack){
    contas(stack,+);
}
/**
 * \brief equivalente à subtração de dois valores.
*/
void menos(Stack stack){
    contas(stack,-);
}
/**
 * \brief equivalente à multiplicação de dois valores.
*/ 
void mult(Stack stack){
    contas(stack,*);
}
/**
 * \brief equivalente à divisão inteira de dois valores.
*/
void divisao(Stack stack){
    contas(stack,/);
}
/**
 * \brief equivalente ao resto divisão inteira de dois valores.
*/
void restoDivisao (Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    push(stack,STACK_LONG,(b.data.val_l%a.data.val_l));
}
/**
 * \brief equivalente à exponenciação de valores.
*/
void expoente (Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);