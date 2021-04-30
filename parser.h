#ifndef PARSER_H_
#define PARSER_H_
#include "stack.h"
#include <stdbool.h>
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caracter posterior ao e
*/
void leituraE(Stack stack,char c);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caracteres a processar
*/
void leituraCasos(Stack stack,char c[]);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caractere a processar
 * @return sé algum caso dentro da fubção aconteceu
 */
void leituraOperacoesBinarias(Stack stack,char c,int *Bool);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caractere a processar
 * @return sé algum caso dentro da fubção aconteceu
 */
void leituraOperacoesContas(Stack stack,char c,int *Bool);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caracteres a processar
 * @return sé algum caso dentro da fubção aconteceu
 */
void leituraOperacoesStack(Stack stack,char c[],int *Bool);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caractere a processar
 * @return sé algum caso dentro da fubção aconteceu
 */
void leituraOperacoesConversoes(Stack stack,char c,int*Bool);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caracteres a processar
 * @return sé algum caso dentro da fubção aconteceu
 */
void leituraOperacoesCondicionais(Stack stack,char c[],int*Bool);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caracteres a processar
*/
void leitura3(Stack stack,char c[]);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caracteres a processar
 * @return sé algum caso dentro da fubção aconteceu
 */
void leituraOperacoesArrays(Stack stack,char c[],int *Bool);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param rest entrada a processar
 * @return o que ainda sobra da string depois de cada passagem
 */
char * leitura2(Stack stack,char *rest);
/**
 * @param stack é a stack onde os valores estão guardados
*/

void leitura (Stack stack);
#endif