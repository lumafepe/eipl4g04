/**
 * @file ficheiro principal do programa
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <malloc.h>
#include <math.h>
#include "stack.h"
#include "operadores.h"
#include "parser.h"
/**
 * Esta é a função principal do nosso guião
 * Chama as funções que constituem o nosso trabalho desde a chamada da stack para o armazenazamento dos inputs dados pelo utilizador ao cálculo das operações pedidas
 * Mostra também o conteúdo existente na stack
 * @return 0
 */
int main() {                                           
    Stack stk = create();
    leitura(stk);
    print_stack(stk);
    destroy(stk);
    return 0;
}