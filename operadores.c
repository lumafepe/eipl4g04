/**
 * @file ficheiro onde se encontram todos os operadores do nosso programa.
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"
#include "operadores.h"




/**
* \brief equivalente a ++ de c.
*/
void maismais(Stack stack){
    struct stack_elemento a = pop(stack);
    switch (a.tipo){
        case STACK_DOUBLE:
            push(stack,a.tipo,(a.data.val_d+1.0));
            break;
        case STACK_LONG:
            push(stack,a.tipo,(a.data.val_l+1));
            break;
        case STACK_CHAR:
            push(stack,a.tipo,(a.data.val_c+1));
            break;
        default:
            break;
    }
}

/**
 * \brief equivalente a -- de c.
*/
void menosmenos(Stack stack){
    struct stack_elemento a = pop(stack);
    switch (a.tipo)
    {
        case STACK_DOUBLE:
            push(stack,a.tipo,(a.data.val_d-1));
            break;
        case STACK_LONG:
            push(stack,a.tipo,(a.data.val_l-1));
            break;
        case STACK_CHAR:
            push(stack,a.tipo,(a.data.val_c-1));
        default:
            break;
    }
}
/**
 *\brief função que recebe da stack um elemento e devolve esse elemento em double.
 */
double toD (struct stack_elemento a){
    switch (a.tipo){
        case (STACK_DOUBLE):
            return a.data.val_d;
            break;
        case (STACK_LONG):
            return a.data.val_l*1.0;
            break;
        default:
            break;
    }
    return 0.0;
}

/**
 * \brief equivalente à soma de dois valores.
*/
void mais(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,a.data.val_l+b.data.val_l);
    else push(stack,STACK_DOUBLE,toD(a)+toD(b));
}
/**
 * \brief equivalente à subtração de dois valores.
*/
void menos(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,b.data.val_l-a.data.val_l);
    else push(stack,STACK_DOUBLE,toD(b)-toD(a));

}

/**
 * \brief equivalente à multiplicação de dois valores.
*/
void mult(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,b.data.val_l*a.data.val_l);
    else push(stack,STACK_DOUBLE,toD(b)*toD(a));
}
/**
 * \brief equivalente à divisão inteira de dois valores.
*/
void divisao(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,b.data.val_l/a.data.val_l);
    else push(stack,STACK_DOUBLE,toD(b)/toD(a));
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
    if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,(long) (pow((double) toD(b),(double) toD(a))));
    else push(stack,STACK_DOUBLE, pow(toD(b),toD(a)));
}
/**
 * \brief equivalente à interseção dos bits correspondentes ao número.
*/
void conjuncao(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    push(stack,STACK_LONG,(b.data.val_l&a.data.val_l));
}
/**
 * \brief equivalente à disjunção dos bits correspondentes ao número.
*/
void disjuncao(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    push(stack,STACK_LONG,(b.data.val_l|a.data.val_l));
}
/**
 * \brief compara bits correspondentes a um número, atribuindo 1 sempre que são distintos.
*/
void xor(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    push(stack,STACK_LONG,(b.data.val_l^a.data.val_l));
}

/**
 * \brief inverte os bits de um inteiro.
*/
void not(Stack stack){
    struct stack_elemento b = pop(stack);
    push(stack,STACK_LONG,(~b.data.val_l));
}
/**
 * \brief duplica o topo da stack.
 */
void copian(Stack stack){
    struct stack_elemento p = pop(stack);
    long  a = p.data.val_l;
    enum stack_tipo tipo = stack->elemento[stack->comprimento-a].tipo;
    switch(tipo){
        case STACK_CHAR:
            push(stack,tipo,stack->elemento[stack->comprimento-a].data.val_c);
            break;
        case STACK_LONG:
            push(stack,tipo,stack->elemento[stack->comprimento-a].data.val_l);
            break;
        case STACK_DOUBLE:
            push(stack,tipo,stack->elemento[stack->comprimento-a].data.val_d);
            break;
        case STACK_STRING:
            push(stack,tipo,stack->elemento[stack->comprimento-a].data.val_s);
            break;
        default:
            fprintf(stderr,"fuck");
            exit(EXIT_FAILURE);
    }
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
            push(stack,STACK_LONG,(long int)a.data.val_c);
            break;
        case STACK_LONG:
            push(stack,STACK_LONG,a.data.val_l);
            break;
        case STACK_DOUBLE:
            push(stack,STACK_LONG,(long int )a.data.val_d);
            break;
        case STACK_STRING:
            push(stack,STACK_LONG,atol(a.data.val_s));
            break;
        default:
            fprintf(stderr,"Erro em convL");
            exit(EXIT_FAILURE);
    }
}
/**
 * \brief função que converte os tipos existentes em double.
 */
void convD (Stack stack){
    struct stack_elemento a = pop(stack);
    switch(a.tipo){
        case STACK_CHAR:
            push(stack,STACK_DOUBLE,(double)a.data.val_c);
            break;
        case STACK_LONG:
            push(stack,STACK_DOUBLE,1.0*a.data.val_l);
            break;
        case STACK_DOUBLE:
            push(stack,STACK_DOUBLE,a.data.val_d);
            break;
        case STACK_STRING:
            push(stack,STACK_DOUBLE,atof(a.data.val_s));
            break;
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
            push(stack,STACK_CHAR,a.data.val_c);
            break;
        case STACK_LONG:
            push(stack,STACK_CHAR,(char)a.data.val_l);
            break;
        default:
            fprintf(stderr,"Erro em convC");
            exit(EXIT_FAILURE);
    }
}
/**
 * \brief função que nos dá o maior de dois numeros existentes na stack(em binário).
 */
void maior(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);/**
 * @file ficheiro onde se encontram todos os operadores do nosso programa.
 */
#include <stdlib.h>
#include <string.h>