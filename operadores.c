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
} 
/**
* \brief equivalente a ++ de c.
*/
void maismais(Stack stack){//)
    struct stack_elemento a = pop(stack);
    if (a.tipo==STACK_STACK) maismaisR(stack,a.data.stk);
    else if (a.tipo==STACK_STRING) maismaisS(stack,a.data.val_s);
    else maismenos(stack,a,+);
}
/**
 * \brief equivalente a -- de c.
*/
void menosmenos(Stack stack){//(
    struct stack_elemento a = pop(stack);
    if (a.tipo==STACK_STACK) menosmenosR(stack,a.data.stk);
    else if (a.tipo==STACK_STRING) menosmenosS(stack,a.data.val_s);
    else maismenos(stack,a,-);
}
/**
 *\brief função que recebe da stack um elemento e devolve esse elemento em double. ou o comprimento de uma string ou se uma array esta vazia
 */
double toD (struct stack_elemento a){
    switch (a.tipo){
        case STACK_DOUBLE:
            return a.data.val_d;break;
        case STACK_STACK:
            return !(stacklen(a.data.stk)==-1);break;
        case STACK_CHAR:
                return a.data.val_c*1.0;
        case STACK_STRING:
                return strlen(a.data.val_s);
        default:
            return a.data.val_l*1.0;
    }
    return 0.0;
}

/**
 * \brief equivalente à soma de dois valores ou a concatenação 
*/
void mais(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (!concatarray(stack,a,b)){
    if (a.tipo==STACK_STRING||b.tipo==STACK_STRING) concatenastrings(stack,a,b);
    else if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,b.data.val_l + a.data.val_l);
    else push(stack,STACK_DOUBLE,toD(b) + toD(a));
    }
}
/**
 * @brief auxiliar para dividir o caso concatenar a uma array o ou concatenar algo a uma array
 */
int concatarray(Stack stack,struct stack_elemento a,struct stack_elemento b){
    if (b.tipo==STACK_STACK){
        concatenarAArrays(stack,b.data.stk,a);
        return 1;
    }
    else if (a.tipo==STACK_STACK){
        concatenarDeArrays(stack,b,a.data.stk);
        return 1;
    }
    else return 0;
}
/**
 * \brief equivalente à subtração de dois valores.
*/
void menos(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,b.data.val_l - a.data.val_l);
    else push(stack,STACK_DOUBLE,toD(b) - toD(a));
}
/**
 * @brief faz a multiplicação de arrays
 */
void arraymult(Stack stack,Stack stk,double a){
    int r = stacklen(stk), j=0;
    for (int i = 0 ; i < a-1 ; i++){
        for (j=0;j<=r;j++){
            pushdata(stk,stk->elemento[j]);
        }
    }
    push(stack,STACK_STACK,stk);
}
/**
 * @brief faz a multiplicação de strings
 */
void strmult(Stack stack,struct stack_elemento a,double n){
    char *d;
    d=(char *)malloc(sizeof(char)*strlen(a.data.val_s)*(int)n);
    strcpy(d,a.data.val_s);
    for (int i =1;i<n;i++){
        strcat(d,a.data.val_s);
    }
    push(stack,STACK_STRING,d);
}

/**
 * @brief equivalente à multiplicação de dois valores.
 * 
 */
void mult(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (!arraymulCasos(stack,a,b)){
        if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,b.data.val_l * a.data.val_l);
        else push(stack,STACK_DOUBLE,toD(b) * toD(a));
    }
}
/**
 * @brief auxiliar para dividir o caso multiiplicar uma string/array
 */
int arraymulCasos(Stack stack,struct stack_elemento a,struct stack_elemento b){
    if (a.tipo==STACK_STACK){
        arraymult(stack,a.data.stk,toD(b));
        return 1;
        }
    else if (a.tipo==STACK_BLOCO){
        fold(stack,b.data.stk,a.data.val_s);
        return 1;
        }
    else if (b.tipo==STACK_STACK){
        arraymult(stack,b.data.stk,toD(a));
        return 1;
        }
    else if (a.tipo==STACK_STRING){
        strmult(stack,a,toD(b));
        return 1;
        }
    else if (b.tipo==STACK_STRING){
        strmult(stack,b,toD(a));
        return 1;
        }
    else return 0;
}
/**
 * \brief equivalente à divisão de dois valores ou a seperação de uma string por partes
*/
void divisao(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_STRING) dividepor(stack,b.data.val_s,a.data.val_s);
    else if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,b.data.val_l / a.data.val_l);
    else push(stack,STACK_DOUBLE,toD(b) / toD(a));
}
/**
 * \brief equivalente ao resto divisão inteira de dois valores.
*/
void restoDivisao (Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_BLOCO) map(stack,b,a.data.val_s);
    else push(stack,STACK_LONG,(b.data.val_l%a.data.val_l));
}
/**
 * \brief equivalente à exponenciação de valores.
*/
void expoente (Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (b.tipo==STACK_STRING) procurasubstring(stack,b.data.val_s,toS(a));
    else if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,(long) (pow(toD(b),toD(a))));
    else push(stack,STACK_DOUBLE, pow(toD(b),toD(a)));
}

/**
 * \brief equivalente à interseção dos bits correspondentes ao número.
*/
void conjuncao(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    push(stack,STACK_LONG,(b.data.val_l & a.data.val_l));
}
/**
 * \brief equivalente à disjunção dos bits correspondentes ao número.
*/
void disjuncao(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    push(stack,STACK_LONG,(b.data.val_l | a.data.val_l));
}
/**
 * \brief compara bits correspondentes a um número, atribuindo 1 sempre que são distintos.
*/
void xor(Stack stack){
    struct stack_elemento a = pop(stack);\
    struct stack_elemento b = pop(stack);\
    push(stack,STACK_LONG,(b.data.val_l ^ a.data.val_l));
}
/**
 * \brief inverte os bits de um inteiro.
*/
void not(Stack stack){
    struct stack_elemento a = pop(stack);
    if (a.tipo==STACK_STACK) colocartodos(stack,a.data.stk);
    else if (a.tipo==STACK_BLOCO) aplicaBloco(stack,a.data.val_s);
    else push(stack,STACK_LONG,(~ a.data.val_l));
}
/**
* \brief função que vai buscar ao topo da stack um número e se este for diferente de 0 devolve o próprio 0 e, caso contrário, devolve 1.  
*/
void notb(Stack stack){
    struct stack_elemento a = pop(stack);
    push(stack,STACK_LONG,(! a.data.val_l));
}
/**
 * \brief duplica o topo da stack/ordena por um argumento.
 */
void copian(Stack stack){
    struct stack_elemento p = pop(stack);
    if (p.tipo==STACK_BLOCO){
        struct stack_elemento q = pop(stack);
        ordenar(stack,q.data.stk,p.data.val_s);
    }
    else{
    long  a = p.data.val_l;
    struct stack_elemento t = stack->elemento[stack->comprimento-a];
    pushdata(stack,t);
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
            push(stack,STACK_LONG,(int)a.data.val_c);break;
        case STACK_LONG:
            push(stack,STACK_LONG,a.data.val_l);break;
        case STACK_DOUBLE:
            push(stack,STACK_LONG,(long int )a.data.val_d);break;
        case STACK_STRING:
            push(stack,STACK_LONG,atoi(a.data.val_s));break;
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
/**
* \brief função que vai buscar ao topo da stack dois números e verifica se estes são iguais.  
*/
void igual(Stack stack ){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_STRING) push(stack,STACK_LONG,!strcmp(a.data.val_s,b.data.val_s));
    else if (b.tipo==STACK_STRING) push(stack,STACK_CHAR,b.data.val_s[(int)toD(a)]);
    else if (b.tipo==STACK_STACK) pushdata(stack,b.data.stk->elemento[(int)toD(a)]);
    else  push(stack,STACK_LONG,toD(b) == toD(a));
}
/**
 * \brief função que nos dá o maior de dois numeros existentes na stack(em binário).
 */
void maior(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (b.tipo==STACK_STACK) retiraXDoFim(stack,b.data.stk,toD(a));
    else if (a.tipo==STACK_STRING) push(stack,STACK_LONG,strcmp(b.data.val_s,a.data.val_s)>0);
    else if (b.tipo==STACK_STRING){
        b.data.val_s+=strlen(b.data.val_s)-(int)toD(a);
        push(stack,STACK_STRING,b.data.val_s);
        }
    else push(stack,STACK_LONG,toD(b) > toD(a));
}
/**
 * \brief função que nos dá o menor de dois numeros existentes na stack(em binário).
 */
void menor(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (b.tipo==STACK_STACK) retiraXDoInicio(stack,b.data.stk,toD(a));
    else if (a.tipo==STACK_STRING) push(stack,STACK_LONG,strcmp(b.data.val_s,a.data.val_s)<0);
    else if (b.tipo==STACK_STRING){
        b.data.val_s[(int)toD(a)]='\0';
        push(stack,STACK_STRING,b.data.val_s);
