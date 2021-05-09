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
                maiorb(stack);break;
            case '<':
                menorb(stack);break;
            case '|':
                ou(stack);break;
            case '&':
                e(stack);break;
            default:break;
        }
}
/**
 * \brief função que trata dos casos de Binarios
*/
void leituraOperacoesBinarias(Stack stack,char c,int *Bool){
    if (*Bool)
        switch(c){
            case '&':
                conjuncao(stack);
                *Bool=0;break;
            case '|':
                disjuncao(stack);
                *Bool=0;break;
            case '^':
                xor(stack);
                *Bool=0;break;
            case '~':
                not(stack);
                *Bool=0;break;
            default:break;
        }
}
/**
 * \brief função que trata dos casos de operadores de contas
*/
void leituraOperacoesContas(Stack stack,char c,int *Bool){
    if (*Bool)
        switch (c) {
            case '%':
                restoDivisao(stack);
                *Bool=0;break;
            case '#':
                expoente(stack);
                *Bool=0;break;
            case '+':
                mais(stack);
                *Bool=0;break;
            case '-': 
                menos(stack);
                *Bool=0;break;
            case '*':
                mult(stack);
                *Bool=0;break;
            case '/': 
                divisao(stack);
                *Bool=0;break;
            case ')':
                maismais(stack);
                *Bool=0;break;
            case '(':
                menosmenos(stack);
                *Bool=0;break;
        }

}
/**
 * \brief função que trata dos casos de operadores sobre a stack
*/
void leituraOperacoesStack(Stack stack,char c[],int *Bool){
    if (*Bool)
        switch (c[0]) {
            case '_':
                duplica(stack);
                *Bool=0;break;
            case '$':
                copian(stack);
                *Bool=0;break;
            case '\\':
                trocar(stack);
                *Bool=0;break;
            case '@':
                rodar(stack);
                *Bool=0;break;
            case ';':
                pop(stack);
                *Bool=0;break;
            case ':':
                stack2var(stack,c[1]);
                *Bool=0;break;
            case 'p':
                print_topo(stack);
                *Bool=0;break;
            default:break;
        }
}
/**
 * \brief função que trata dos casos de operadores de conversões
*/
void leituraOperacoesConversoes(Stack stack,char c,int*Bool){
    if (*Bool)
        switch (c) {
            case 'i':
                convL(stack);
                *Bool=0;break;
            case 'f':
                convD(stack);
                *Bool=0;break;
            case 'c':
                convC(stack);
                *Bool=0;break;
            case 's':
                convS(stack);
                *Bool=0;break;
            default:break;
        }
    
}
/**
 * \brief função que trata dos casos de operadores de Condições
*/
void leituraOperacoesCondicionais(Stack stack,char c[],int*Bool){
    if (*Bool)
        switch (c[0]) {
            case '?':
                ifthenelse(stack);
                *Bool=0;break;
            case '=':
                igual(stack);
                *Bool=0;break;
            case '<':
                menor(stack);
                *Bool=0;break;
            case '>':
                maior(stack);
                *Bool=0;break;
            case '!':
                notb(stack);
                *Bool=0;break;
            case 'e':
                leituraE(stack,c[1]);
                *Bool=0;break;
            default:break;
        }
}
/**
 * \brief função que trata dos casos de strings e arrays
*/
void leituraOperacoesArrays(Stack stack,char c[],int *Bool){
    if (*Bool)
        switch (c[0]) {
            case ',':
                virgula(stack);
                *Bool=0;break;
            case 'S':
                if (c[1]=='/'){
                    divideporespacos(stack);
                    *Bool=0;
                }break;
            case 'N':
                if (c[1]=='/'){
                    dividepornewline(stack);
                    *Bool=0;
                }break;
            case 'w':
                w(stack);
                *Bool=0;break;
            default:break;
    }
}

/**
 * \brief função que trata dos casos de operadores
*/
void leituraCasos(Stack stack,char c[]){
    char str2[10240],*str3=malloc(sizeof(char)*1000);
    int Bool=1;
    leituraOperacoesBinarias(stack,c[0],&Bool);
    leituraOperacoesContas(stack,c[0],&Bool);
    leituraOperacoesStack(stack,c,&Bool);
    leituraOperacoesConversoes(stack,c[0],&Bool);
    leituraOperacoesCondicionais(stack,c,&Bool);
    leituraOperacoesArrays(stack,c,&Bool);
    if (c[0]=='l' && Bool){
        assert(scanf("\n%10240[^\n]",str2)==1);
        push(stack,STACK_STRING,str2);
        }
    else if (c[0]=='t' && Bool){
        while((str3=fgets(str3,1000,stdin))){
            strcat(str2,str3);
        }
        push(stack,STACK_STRING,str2);
    }
    else if (Bool){ 
        fprintf(stderr,"caracter desconhecido");exit(EXIT_FAILURE);
    }

}
/**
 * \brief função que trata de guardar a string como double,long,variavel ou se é um operador
*/
void leitura3(Stack stack,char c[]){
    int a=1;
    unsigned i;
    for (i=0;i<strlen(c);i++){
        if (c[i] == '.'){ // condição que verifica se corresponde a um número ou a um operador
            push(stack,STACK_DOUBLE,atof(c));
            a=0;break;
        }
    }
    if (a){
        for (i=0;i<strlen(c);i++){
            if (c[i] <= '9' && c[i]>='0'){ // condição que verifica se corresponde a um número ou a um operador
                push(stack,STACK_LONG,atoi(c));
                a=0;break;
            }
        }
    }
    if (a){ // a cada operador faz corresponder a sua função
        if (c[0]<='Z' && c[0]>='A' && c[1]!='/') var2stack(stack,c[0]);
        else leituraCasos(stack,c);
    }    
}
/**
 * @brief verifica se duas strings sao parcialmente iguais.
 */
int verifica(char c[],char d[]){
    for (int i=0;i<75;i++){
        if (c[i]!=d[i]) return 0;
    }
    return 1;
}
/**
 * Esta é a função que trata da leitura do input do user
 * Esta envia para o texto para a leitura2 para ser processado
*/
void leitura (Stack stack){
    char str[10240];
    assert(fgets(str,10240,stdin)!=NULL);
    leitura2(stack,str);
}

/**
 * @brief auxiliar a leitura2 responsavel por guardar as array
 */
char * lerArrayAux(Stack stack,char *rest){
    Stack stk;
    char *l;
    rest++;
    stk = create(stack);
    l= strdup(rest);
    rest=leitura2(stk,l);
    copyVariaveis(stack,stk);
    push(stack,STACK_STACK,stk);
    return rest;
}
/**
 * @brief auxiliar a leitura2 responsavel por guardar os blocos
 */
char * lerBlocoAux(Stack stack,char *rest){
    int Bool=1,i=0;
    char *out = (char *)malloc(sizeof(char)*strlen(rest));
    while (Bool){
        switch (rest[0]){
        case '{':
            Bool++;break;
        case '}':
            Bool--;break;
        default:break;
        }
        out[i++] = *(rest++);
        out[i] = '\0';
    }
    out[i-1]='\0';
    push(stack,STACK_BLOCO,out);
    return rest;

}




/**
 * Esta é a função que trata de separa o texto por partes e dependodo do que for o que fazer com ele
*/
char * leitura2(Stack stack, char *rest){
    int Bool=1;
    char * token;
    while (Bool){
        switch (rest[0]){
            case ('{'):
                rest++;
                rest=lerBlocoAux(stack,rest);
                break;
            case ('['):
                rest=lerArrayAux(stack,rest);break;
            case (']'):
                Bool=0;
                rest++;break;;
            case '\"':
                rest++;
                if(*rest=='\"') {push(stack,STACK_STRING,""); rest++;}
                else if ((token=strtok_r(rest, "\"",&rest))) push(stack,STACK_STRING,token);
                else Bool=0;
                break;
            case ' ':
                rest++;break;
            case '\n':
                Bool=0;break;
            default:
                if ((token = strtok_r(rest, " ", &rest))) leitura3(stack,token);
                else Bool=0;
                    break;
            }
    }
    return rest;
}

