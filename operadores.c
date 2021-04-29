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
 * @brief funçao responsavel de remover o primeiro elemento da string e o colocar na stack
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
* \brief equivalente a ++ de c ou remover o ultimo elemento de um objecto e coloca-lo na stack.
*/
void maismais(Stack stack){//)
    struct stack_elemento a = pop(stack);
    if (a.tipo==STACK_STACK) maismaisR(stack,a.data.stk);
    else if (a.tipo==STACK_STRING) maismaisS(stack,a.data.val_s);
    else maismenos(stack,a,+);
}
/**
 * \brief equivalente a -- de c ou remover o primeiro elemento de um objecto e coloca-lo na stack.
*/
void menosmenos(Stack stack){//(
    struct stack_elemento a = pop(stack);
    if (a.tipo==STACK_STACK) menosmenosR(stack,a.data.stk);
    else if (a.tipo==STACK_STRING) menosmenosS(stack,a.data.val_s);
    else maismenos(stack,a,-);
}
/**
 *\brief função que recebe da stack um elemento e devolve esse elemento em double ou se uma array devolve se esta vazia
 */
double toD (struct stack_elemento a){
    switch (a.tipo){
    case STACK_DOUBLE:
        return a.data.val_d;break;
    case STACK_STACK:
        return !(stacklen(a.data.stk)==-1);break;
    default:
        return a.data.val_l*1.0;
    }
    return 0.0;
}
/** @def contas
 * @brief macro para a função mais, menos, mult e divisao.
 */
#define contas(stack,a,b, op){\
    if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,b.data.val_l op a.data.val_l);\
    else push(stack,STACK_DOUBLE,toD(b) op toD(a));\
}

/**
 * \brief equivalente à soma de dois valores ou a concatenação 
*/
void mais(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (b.tipo==STACK_STACK) concatenarAArrays(stack,b.data.stk,a);
    else if (a.tipo==STACK_STACK) concatenarDeArrays(stack,b,a.data.stk);
    else if (a.tipo==STACK_STRING||b.tipo==STACK_STRING) concatenastrings(stack,a,b);
    else contas(stack,a,b,+);
}
/**
 * \brief equivalente à subtração de dois valores.
*/
void menos(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    contas(stack,a,b,-);
}
/**
 * \brief faz a multiplicação de uma array por um numero
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
 * \brief faz a multiplicação de uma string por um numero
*/
void strmult(Stack stack,struct stack_elemento a,double n){
    char *d;
    d=strdup(a.data.val_s);
    for (int i =1;i<n;i++){
        strcat(d,a.data.val_s);
    }
    push(stack,STACK_STRING,d);
}

/**
 * @brief equivalente à multiplicação de dois valores ou a repetição de uma array/string n numero de vezes
 * 
 */
void mult(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_STACK) arraymult(stack,a.data.stk,toD(b));
    else if (b.tipo==STACK_STACK) arraymult(stack,b.data.stk,toD(a));
    else if (a.tipo==STACK_STRING) strmult(stack,a,toD(b));
    else if (b.tipo==STACK_STRING) strmult(stack,b,toD(a));
    else contas(stack,a,b,*);
}
/**
 * \brief equivalente à divisão de dois valores ou a seperação de uma string por partes
*/
void divisao(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_STRING) dividepor(stack,b.data.val_s,a.data.val_s);
    else contas(stack,a,b,/);
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
 * \brief equivalente à exponenciação de valores ou a pesquisa de uma um texto num outro texto
*/
void expoente (Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_STRING) procurasubstring(stack,b.data.val_s,a.data.val_s);
    else if (a.tipo==STACK_LONG && b.tipo==STACK_LONG) push(stack,STACK_LONG,(long) (pow(toD(b),toD(a))));
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
#define notg(stack,a, op){\
    push(stack,STACK_LONG,(op a.data.val_l));\
}
/**
 * \brief inverte os bits de um inteiro ou coloca todos os elemento de uma array na stack
*/
void not(Stack stack){
    struct stack_elemento a = pop(stack);
    if (a.tipo==STACK_STACK) colocartodos(stack,a.data.stk);
    else notg(stack,a,~);
}
/**
* \brief função que vai buscar ao topo da stack um número e se este for diferente de 0 devolve o próprio 0 e, caso contrário, devolve 1.  
*/
void notb(Stack stack){
    struct stack_elemento a = pop(stack);
    notg(stack,a,!);
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
#define maiormenorigual(stack,a,b, op){\
    push(stack,STACK_LONG,toD(b) op toD(a));\
}
/**
* \brief função que vai buscar ao topo da stack dois elementos e verifica se estes são iguais ou delvolve o elemento numa posição x de uma stack/array  
*/
void igual(Stack stack ){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_STRING) push(stack,STACK_LONG,!strcmp(a.data.val_s,b.data.val_s));
    else if (b.tipo==STACK_STRING) push(stack,STACK_CHAR,b.data.val_s[(int)toD(a)]);
    else if (b.tipo==STACK_STACK) pushdata(stack,b.data.stk->elemento[(int)toD(a)]);
    else maiormenorigual(stack,a,b,==);
}
/**
 * \brief função que nos dá o maior de dois elementos existentes na stack ou devolve os n primeiros elementos de uma string/stack
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
    else maiormenorigual(stack,a,b,>);
}
/**
 * \brief função que nos dá o menor de dois elementos existentes na stack ou devolve os n ultimos elementos de uma string/stack
 */
void menor(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (b.tipo==STACK_STACK) retiraXDoInicio(stack,b.data.stk,toD(a));
    else if (a.tipo==STACK_STRING) push(stack,STACK_LONG,strcmp(b.data.val_s,a.data.val_s)<0);
    else if (b.tipo==STACK_STRING){
        b.data.val_s[(int)toD(a)]='\0';
        push(stack,STACK_STRING,b.data.val_s);
        }
    else maiormenorigual(stack,a,b,<);
}
/** @def maiorbmenorb
 * @brief macro para a função maiorb e menorb.
 */
#define maiorbmenorb(stack,a,b,op){\
    pushdata(stack,(toD(b) op toD(a)?b:a));\
}

/**
 * \brief função que nos dá o maior de dois elementos existentes na stack(sem binário).
 */
void maiorb(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_STRING) pushdata(stack,(strcmp(b.data.val_s,a.data.val_s)>0)?b:a);
    else maiorbmenorb(stack,a,b,>);
}
/**
* \brief função que nos dá o menor de dois elementos existentes na stack(sem binário).  
*/
void menorb(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_STRING) pushdata(stack,((strcmp(b.data.val_s,a.data.val_s)<0)?b:a));
    else maiorbmenorb(stack,a,b,<);
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
* \brief função que delve o valor de um elemento sobre a forma de string
*/
char * toS(struct stack_elemento a){
    char *c=NULL;
    switch (a.tipo) {
        case STACK_STRING:
            c= strdup(a.data.val_s);break;
        case STACK_CHAR:
            c=(char *) malloc(sizeof(char));
            c[0]=a.data.val_c;
            c[1]='\0';break;
        default:
            break;
    }
    return c;
}
/**
 * @brief junta dois elementos de tipo string em uma so e coloca-a na stack
 */
void concatenastrings (Stack stack,struct stack_elemento a,struct stack_elemento b){
    char *as=toS(a),*bs=toS(b);
    char *c= (char *) malloc(sizeof(char)* (strlen(as)+ strlen(bs)));
    strcpy(c,bs);
    strcat(c,as);
    push(stack,STACK_STRING,c);
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
    pushdata(stack,(toD(i)?t:e));
}

/**
* \brief pega numa variável e transforma-o num elemento da stack.  
*/
void var2stack(Stack stack,char s){
    pushdata(stack,copiaElem(stack->variaveis[s-65]));
}
/**
 * \brief pega no elemento do topo da stack e transforma-o numa variável. 
*/
void stack2var(Stack stack,char s){
    Stack stk = create(stack);
    pushdata(stk,stack->elemento[stack->comprimento]);
    stack->variaveis[s-65] = stk->elemento[0];
}
/**
 * @brief funçao que dependendo do que esta na stack devolve quantos elementos existem numa array/string ou cria um array com os numeros inteiros de 0 a N
 */
void virgula(Stack stack){
    struct stack_elemento a = pop(stack);
    switch (a.tipo){
        case (STACK_STACK):
            push(stack,STACK_LONG,stacklen(a.data.stk)+1);break;
        case (STACK_STRING):
            push(stack,STACK_LONG,strlen(a.data.val_s));break;
        default:
            range(stack,a);
    }
}
/**
 * @brief função que cria um array com os numeros inteiros de 0 a valor de a
 */
void range(Stack stack,struct stack_elemento a){
    Stack stk=create(stack);
    for (int i = 0;i<toD(a);i++){
        push(stk,STACK_LONG,i);
    }
    push(stack,STACK_STACK,stk);
}
/**
 * @brief coloca todos os elementos de um array noutro ou para a stack
 */
void colocartodos(Stack stack,Stack stk){
    int i=0;
    while (i<=stk->comprimento){
        pushdata(stack,stk->elemento[i++]);
    }
}

/**
 * @brief divide uma string por espaços e guarda no array q é colocada na stack
 */
void divideporespacos (Stack stack){
    Stack stk=create(stack);
    struct stack_elemento a = pop(stack);
    char *token = strtok(a.data.val_s," \n");
    while(token != NULL){
        push(stk,STACK_STRING,token);
        token = strtok(NULL," \n");
    }
    push(stack,STACK_STACK,stk);
}
/**
 * @brief divide uma string por linha e guarda no array q é colocada na stack
 */
void dividepornewline (Stack stack){
    Stack stk=create(stack);
    struct stack_elemento a = pop(stack);
    char *token;
    while ((token = strtok_r(a.data.val_s, "\n", &a.data.val_s))){
        push(stk,STACK_STRING,token);
    }
    push(stack,STACK_STACK,stk);
}
/**
 * @brief divide uma string por um dado elemento e guarda no array q é colocada na stack
 */
void dividepor (Stack stack,char c[],char c1[]){
    Stack stk=create(stack);
    char *token;
    while ((token = strtok_r(c, c1, &c))){
        push(stk,STACK_STRING,token);
    }
    push(stack,STACK_STACK,stk);
}
/**
 * @brief verifica se existe uma substring dentro da string se houver coloca a posição na stack caso contrario devolve -1
 */
void procurasubstring (Stack stack,char c[],char c1[]){
    char* res;
    res=strstr(c,c1);
    if (res) push(stack,STACK_LONG,res-c);
    else push(stack,STACK_LONG,-1);
}
/**
 * @brief junta a um elemento todos os elementos de uma array e coloca-os num array dentro da stack
 */
void concatenarDeArrays (Stack stack,struct stack_elemento a,Stack stk1){
    Stack stk;
    switch (a.tipo){
        case (STACK_STACK):
            stk=a.data.stk;break;
        default :
            stk=create(stack);
            pushdata(stk,a);break;
    }
    colocartodos(stk,stk1);
    push(stack,STACK_STACK,stk);
}
/**
 * @brief junta aos elementos de uma array um elemnto e guarda a array  dentro da stack
 */
void concatenarAArrays (Stack stack,Stack stk1,struct stack_elemento a){
    switch (a.tipo){
        case (STACK_STACK):
            colocartodos(stk1,a.data.stk);break;
        default :
            pushdata(stk1,a);break;
    }
    push(stack,STACK_STACK,stk1);
}
/**
 * @brief remove um dado numero de elementos do fim da array e coloca-os na stack
 */
void retiraXDoFim(Stack stack,Stack stk,double n){
    int i;
    if (n>stk->comprimento+1) n =0;
    else n = (int)(stk->comprimento+1-n);
    for (i=(int)n;i<stk->comprimento+1;i++) pushdata(stack,stk->elemento[i]);
}
/**
 * @brief remove um dado numero de elementos do inicio da array e coloca-os na stack
 */
void retiraXDoInicio(Stack stack,Stack stk,double n){
    if (n>stk->comprimento+1) n = stk->comprimento+1;
    for (int i =0;i<n ;i++) pushdata(stack,popL(stk));
}
/**
 * @brief copia um elemento para uma nova variavel e devolve a copia do elemento
 */
struct stack_elemento copiaElem(struct stack_elemento a){
    struct stack_elemento b;
    switch (a.tipo) {
        case STACK_LONG:
            b.data.val_l=a.data.val_l;break;
        case STACK_STRING:
            b.data.val_s=a.data.val_s;break;
        case STACK_DOUBLE:
            b.data.val_d=a.data.val_d;break;
        case STACK_STACK:
            b.data.stk=a.data.stk;break;
        case STACK_CHAR:
            b.data.val_c=a.data.val_c;break;
        default:break;
    }
    b.tipo=a.tipo;
    return b;

}