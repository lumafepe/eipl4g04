/**
 * @file ficheiro onde se encontram todos os operadores do nosso programa.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"
#include "operadores.h"
/** @def maismenos
 * @brief macro para a função maismais e menosmenos.
 */
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
/** @def contas
 * @brief macro para a função mais, menos, mult e divisao.
 */
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
    if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,(long) (pow(toD(b),toD(a))));
    else push(stack,STACK_DOUBLE, pow(toD(b),toD(a)));    
}
/** @def contasbinarias
 * @brief macro para a função conjunção, disjuncao e xor.
 */
#define contasbinarias(stack, op){\
        struct stack_elemento a = pop(stack);\
    struct stack_elemento b = pop(stack);\
    push(stack,STACK_LONG,(b.data.val_l op a.data.val_l));\
}
/**
 * \brief equivalente à interseção dos bits correspondentes ao número.
*/
void conjuncao(Stack stack){
    contasbinarias(stack,&);
}
/**
 * \brief equivalente à disjunção dos bits correspondentes ao número.
*/
void disjuncao(Stack stack){
    contasbinarias(stack,|);
}
/**
 * \brief compara bits correspondentes a um número, atribuindo 1 sempre que são distintos.
*/
void xor(Stack stack){
    contasbinarias(stack,^);
}
/** @def notg
 * @brief macro para a função not e notb.
 */
#define notg(stack, op){\
    struct stack_elemento b = pop(stack);\
    push(stack,STACK_LONG,(op b.data.val_l));\
}
/**
 * \brief inverte os bits de um inteiro.
*/
void not(Stack stack){
    notg(stack,~);
}
/**
* \brief função que vai buscar ao topo da stack um número e se este for diferente de 0 devolve o próprio 0 e, caso contrário, devolve 1.  
*/
void notb(Stack stack){
    notg(stack,!);
}
/**
 * \brief duplica o topo da stack.
 */
void copian(Stack stack){
    struct stack_elemento p = pop(stack);
    long  a = p.data.val_l;
    struct stack_elemento t = stack->elemento[stack->comprimento-a];
    pushdata(stack,t);
}
/**
 * \brief troca de dois elementos da stack.
 */
void trocar (Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    pushdata(stack,a);
    pushdata(stack,b);
}
/**
 * \brief Roda três elementos da stack.
 */
void rodar (Stack stack){
    struct stack_elemento p1 = pop(stack);
    struct stack_elemento p2 = pop(stack);
    struct stack_elemento p3 = pop(stack);
    pushdata (stack,p2);
    pushdata (stack,p1);
    pushdata (stack,p3);
}
/**
 * \brief duplica um elemento da stack.
 */
void duplica(Stack stack){
    struct stack_elemento p1 = pop(stack);
    pushdata (stack,p1);
    pushdata (stack,p1);
}
/**
 * \brief função que converte os tipos existentes para long.
 */
void convL (Stack stack){
    struct stack_elemento a = pop(stack);
    switch(a.tipo){
        case STACK_CHAR:
            push(stack,STACK_LONG,(long int)a.data.val_c);break;
        case STACK_LONG:
            push(stack,STACK_LONG,a.data.val_l);break;
        case STACK_DOUBLE:
            push(stack,STACK_LONG,(long int )a.data.val_d);break;
        case STACK_STRING:
            push(stack,STACK_LONG,atol(a.data.val_s));break;
        default:
            fprintf(stderr,"Erro em convL");exit(EXIT_FAILURE);
    }
}
/**
 * \brief função que converte os tipos existentes em double.
 */
void convD (Stack stack){
    struct stack_elemento a = pop(stack);
    switch(a.tipo){
        case STACK_CHAR:
            push(stack,STACK_DOUBLE,(double)a.data.val_c);break;
        case STACK_LONG:
            push(stack,STACK_DOUBLE,1.0*a.data.val_l);break;
        case STACK_DOUBLE:
            push(stack,STACK_DOUBLE,a.data.val_d);break;
        case STACK_STRING:
            push(stack,STACK_DOUBLE,atof(a.data.val_s));break;
        default:
            fprintf(stderr,"Erro em convD");
            exit(EXIT_FAILURE);
    }
}
/**
 * \brief função que converte os tipos existentes em char.
 */
void convC (Stack stack){
    struct stack_elemento a = pop(stack);
    switch(a.tipo){
        case STACK_CHAR:
            push(stack,STACK_CHAR,a.data.val_c);break;
        case STACK_LONG:
            push(stack,STACK_CHAR,(char)a.data.val_l);break;
        default:
            fprintf(stderr,"Erro em convC");exit(EXIT_FAILURE);
    }
}
/** @def maiormenorigual
 * @brief macro para a função igual,menor e maior.
 */
#define maiormenorigual(stack, op){\
    struct stack_elemento a = pop(stack);\
    struct stack_elemento b = pop(stack);\
    push(stack,STACK_LONG,toD(b) op toD(a));\
}
/**
* \brief função que vai buscar ao topo da stack dois números e verifica se estes são iguais.  
*/
void igual(Stack stack ){
    maiormenorigual(stack,==);
}
/**
 * \brief função que nos dá o maior de dois numeros existentes na stack(em binário).
 */
void maior(Stack stack){
    maiormenorigual(stack,>);
}
/**
 * \brief função que nos dá o menor de dois numeros existentes na stack(em binário).
 */
void menor(Stack stack){
    maiormenorigual(stack,<);
}
/** @def maiorbmenorb
 * @brief macro para a função maiorb e menorb.
 */
#define maiorbmenorb(stack, op){\
    struct stack_elemento a = pop(stack);\
    struct stack_elemento b = pop(stack);\
    pushdata(stack,(toD(b) op toD(a)?b:a));\
}
/**
 * \brief função que nos dá o maior de dois numeros existentes na stack(sem binário).
 */
void maiorb(Stack stack){
    maiorbmenorb(stack,>);
}
/**
* \brief função que nos dá o menor de dois numeros existentes na stack(sem binário).  
*/
void menorb(Stack stack){
    maiorbmenorb(stack,<);
}
/**
* \brief função que vai buscar 2 elementos ao topo da stack, se ambos forem falsos, retorna 0 , caso contrário, devolve o segundo.
*/
void ou(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    pushdata(stack,(b.data.val_l?b:a));
}
/**
* \brief função que vai buscar 2 elementos ao topo da stack, se um deles for falso, retorna 0 , caso contrário, devolve o primeiro.  
*/
void e(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (toD(a)&&toD(b)) pushdata(stack,a);
    else push(stack,STACK_LONG,0);
}
/**
* \brief função que vai buscar ao topo da stack 3 elementos, se o elemento que estiver em terceiro lugar for verdadeiro, então coloca na stack o segundo, caso contrário coloca o primeiro.  
*/
void ifthenelse(Stack stack){
    struct stack_elemento e = pop(stack);
    struct stack_elemento t = pop(stack);
    struct stack_elemento i = pop(stack);
    pushdata(stack,(i.data.val_l?t:e));
}
/**
* \brief pega numa variável e transforma-o num elemento da stack.  
*/
void var2stack(Stack stack,char s){
    pushdata(stack,stack->variaveis[s-65]);
}
/**
 * \brief pega no elemento do topo da stack e transforma-o numa variável. 
*/
void stack2var(Stack stack,char s){
    stack->variaveis[s-65]=stack->elemento[stack->comprimento];
}