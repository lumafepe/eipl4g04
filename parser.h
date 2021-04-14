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
int leituraOperacoesBinarias(Stack stack,char c);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caractere a processar
 * @return sé algum caso dentro da fubção aconteceu
 */
int leituraOperacoesContas(Stack stack,char c);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caracteres a processar
 * @return sé algum caso dentro da fubção aconteceu
 */
int leituraOperacoesStack(Stack stack,char c[]);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caractere a processar
 * @return sé algum caso dentro da fubção aconteceu
 */
int leituraOperacoesConversoes(Stack stack,char c);
/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caracteres a processar
 * @return sé algum caso dentro da fubção aconteceu
 */
int leituraOperacoesCondicionais(Stack stack,char c[]);


/**
 * @param stack é a stack onde os valores estão guardados
 * @param c caracteres a processar
*/
void leitura2(Stack stack,char c[]);

/**
 * @param stack é a stack onde os valores estão guardados
*/
void leitura (Stack stack);

#endif