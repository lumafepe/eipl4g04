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
        }
    else push(stack,STACK_LONG,toD(b) < toD(a));
}

/**
 * \brief função que nos dá o maior de dois numeros existentes na stack(sem binário).
 */
void maiorb(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_STRING) pushdata(stack,(strcmp(b.data.val_s,a.data.val_s)>0)?b:a);
    else pushdata(stack,(toD(b) > toD(a)?b:a));
}
/**
* \brief função que nos dá o menor de dois numeros existentes na stack(sem binário).  
*/
void menorb(Stack stack){
    struct stack_elemento a = pop(stack);
    struct stack_elemento b = pop(stack);
    if (a.tipo==STACK_STRING) pushdata(stack,((strcmp(b.data.val_s,a.data.val_s)<0)?b:a));
    else pushdata(stack,(toD(b) < toD(a)?b:a));
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
            c = a.data.val_s;break;
        case STACK_CHAR:
            c=(char *) malloc(sizeof(char));
            c[0]=a.data.val_c;
            c[1]='\0';break;
        case STACK_LONG:
            c=(char *) malloc(sizeof(char)*contadigitos(a.data.val_l));
            sprintf(c,"%d",(int)a.data.val_l);break;
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
    struct stack_elemento b;
    switch (a.tipo){
        case (STACK_STACK):
            push(stack,STACK_LONG,stacklen(a.data.stk)+1);break;
        case (STACK_STRING):
            push(stack,STACK_LONG,strlen(a.data.val_s));break;
        case (STACK_BLOCO):
            b=pop(stack);
            filter(stack,b,a.data.val_s);break;
        case (STACK_CHAR):
            push(stack,STACK_LONG,1);break;
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
    long a=-1;
    res=strstr(c,c1);
    if (res) push(stack,STACK_LONG,res-c);
    else push(stack,STACK_LONG,a);
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
    Stack stk1=create(stack);
    if (n>stk->comprimento+1) n =0;
    else n = (int)(stk->comprimento+1-n);
    for (i=(int)n;i<stk->comprimento+1;i++) pushdata(stk1,stk->elemento[i]);
    push(stack,STACK_STACK,stk1);
}
/**
 * @brief remove um dado numero de elementos do inicio da array e coloca-os na stack
 */
void retiraXDoInicio(Stack stack,Stack stk,double n){
    Stack stk1=create(stack);
    if (n>stk->comprimento+1) n = stk->comprimento+1;
    for (int i =0;i<n ;i++) pushdata(stk1,popL(stk));
    push(stack,STACK_STACK,stk1);
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
        case STACK_BLOCO:
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











/**
 * @brief 
 */
struct stack_elemento popLS(char i[]){
    struct stack_elemento r;
    r.tipo=STACK_CHAR;
    r.data.val_c=i[0];
    return r;
}


/**
 * @brief função que aplica a função principal de leitura a porções de um input dado (blocos).
 */
void aplicaBloco(Stack stack,char c[]){
    leitura2(stack,c);
}

/**
 * @brief Função que engloba os dois tipos de maps existentes.
 */
void map(Stack stack,struct stack_elemento a,char c[]){
    switch (a.tipo){
        case STACK_STRING:
            mapS(stack,a.data.val_s,c);break;
        case STACK_STACK:
            mapA(stack,a.data.stk,c);break;
        default:break;
        }
}
/**
 * @brief Função que aplica uma função a todos os elementos da string (map).
 */
void mapS(Stack stack,char in[],char c[]){
    char *d;
    char *out= (char *) malloc(sizeof(char)*strlen(in));
    while (in[0]!='\0'){
        d = strdup(c);
        pushdata(stack,popLS(in++));
        aplicaBloco(stack,d);
        strcat(out,toS(pop(stack)));
    }
    push(stack,STACK_STRING,out);
    free(out);
}

/**
 * @brief Função que aplica uma função a todos os elementos da Stack (map).
 */
void mapA(Stack stack,Stack stk,char c[]){
    int comp = stk->comprimento;
    char *d;
    Stack stk1=create(stack);
    while (comp-->=0){
        pushdata(stk1,popL(stk));
        d = strdup(c);
        aplicaBloco(stk1,d);
        free(d);
    }
    copyVariaveis(stack,stk1);
    push(stack,STACK_STACK,stk1);
}




/**
 * @brief Função que engloba os dois tipos de filters existentes.
 */
void filter(Stack stack, struct stack_elemento a,char c[]){
    switch (a.tipo){
    case STACK_STRING:
        filterS(stack,a.data.val_s,c);break;
    case STACK_STACK:
        filterA(stack,a.data.stk,c);break;
    default:
        break;
    }
}

/**
 * @brief Função que faz o filter ao tipo STACK.
 */
void filterA(Stack stack,Stack stk,char c[]){
    char *d;
    struct stack_elemento copia;
    Stack stk1 = create(stack);
    while (stk->comprimento!=-1){
        d = strdup(c);
        copia=popL(stk);
        pushdata(stk1,copia);
        aplicaBloco(stk1,d);
        free(d);
        copyVariaveis(stack,stk1);
        if (toD(pop(stk1))) pushdata(stk1,copia);
    }
    push(stack,STACK_STACK,stk1);
}
/**
 * @brief Função que faz o filter de uma string.
 */
void filterS(Stack stack,char in[],char c[]){
    struct stack_elemento caracter,copia;
    char *d,*out= (char *) malloc(sizeof(char)*strlen(in));
    while (in[0]!='\0'){
        d = strdup(c);
        copia=popLS(in++);
        pushdata(stack,copia);
        aplicaBloco(stack,d);
        caracter = pop(stack);
        if (toD(caracter)) strcat(out,toS(copia));
    }
    push(stack,STACK_STRING,out);
}

/**
 * @brief função que faz o fold da esquerda para a direita  de uma array
 */
void fold(Stack stack,Stack stk, char c[]){
    Stack stk1=create(stack);
    char *d;
    pushdata(stk1,popL(stk));
    while (stk->comprimento!=-1){
        d = strdup(c);
        pushdata(stk1,popL(stk));
        d=leitura2(stk1,d);
    }
    push(stack,STACK_STACK,stk1);
}
/**
 * @brief função auxiliar da guardaempares, que identifica qual o tipo do elemento recebido.
 */
struct stack_elemento guardaemparesAux(struct stack_elemento a){
    switch(a.tipo){
        case STACK_STRING:
            break;
        default:
            a.data.val_d=toD(a);
            a.tipo=STACK_DOUBLE;
            break;
    }
    return a;
}

/**
 * @brief função que guarda um elemento e o seu resultado apos aplicar um bloco num par.
 */
void guardaempares(Stack stk,Stack stk1,char c[],int comp,par *pares){
    char *d;
    struct stack_elemento copia;
    for (int i=0;i<=comp;i++){
        d = strdup(c);
        copia=popL(stk);
        pushdata(stk1,copia);
        aplicaBloco(stk1,d);
        free(d);
        pares[i].elemento=copia;
        pares[i].valor=guardaemparesAux(pop(stk1));
    }
}
/**
 * @brief função que ordena uma lista de pares segundo o valor e caso seja uma string ordena secundariamente por ordem alfabetica.
 */
void ordenaPares(par *pares,int N,char c[]){
    int Bool=1,i;
    par auxiliar;
    while (Bool){
        Bool=0;
        for (i=0;i<N;i++)
            if (strlen(c)==1 && pares[i].valor.tipo==STACK_STRING){
                if (strcmp(pares[i].elemento.data.val_s,pares[i+1].elemento.data.val_s)>0){
                    auxiliar=pares[i];
                    pares[i]=pares[i+1];
                    pares[i+1]=auxiliar;
                    Bool=1;
                }

            }
            else if (toD(pares[i].valor)>toD(pares[i+1].valor)){
                auxiliar=pares[i];
                pares[i]=pares[i+1];
                pares[i+1]=auxiliar;
                Bool=1;
            }
            else if (toD(pares[i].valor)==toD(pares[i+1].valor) && pares[i].valor.tipo==STACK_STRING){
                if (strcmp(pares[i].elemento.data.val_s,pares[i+1].elemento.data.val_s)>0){
                    auxiliar=pares[i];
                    pares[i]=pares[i+1];
                    pares[i+1]=auxiliar;
                    Bool=1;
                }
            }
    }
}
/**
 * @brief função que pega numa lista de pares e a cada elemento de de um par o coloca numa array.
 */
void pushPares(Stack stack,par *pares,int N){
    Stack stk=create(stack);
    for (int i=0;i<=N;i++){
        pushdata(stk,pares[i].elemento);
    }
    push(stack,STACK_STACK,stk);
}
/**
 * @brief função ordena os elementos de uma array segundo um bloco.
 */
void ordenar(Stack stack,Stack stk,char c[]){
    int comp=stacklen(stk)+1;
    Stack stk1 = create(stack);
    par pares[comp];
    guardaempares(stk,stk1,c,--comp,pares);
    ordenaPares(pares,comp,c);
    pushPares(stack,pares,comp);
}

/**
 * @brief enquanto o resultado de aplicar um bloco a um elemento for verdade aplica o bloco a cada um dos elementos da array.
 */
void w(Stack stack){
    struct stack_elemento a = pop(stack);
    char *c = a.data.val_s,*d;
    while(toD(a)){
        d=strdup(c);
        aplicaBloco(stack,d);
        a = pop(stack);
        free(d);
    }
}
/**
 * @brief função que dado um inteiro conta quantos digitos esse número possui.
 */
int contadigitos(int i){
    if (i!=i%10) return (1 + contadigitos(i%10));
    else return 1;
}
/**
 * @brief Função que converte para string um determinado elemento da stack.
 */
void convS(Stack stack){
    push(stack,STACK_STRING,toS(pop(stack)));
}
/**
 * @brief função que dá print do topo da stack.
 */
void print_topo(Stack stack){
    print_elemento(stack->elemento[stack->comprimento]);
    printf("\n");
}