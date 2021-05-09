#ifndef STACK_H_
#define STACK_H_
#include <stdbool.h>
/**
 * @enum stack_tipo
 * @brief Tipo de cada elemento da stack.
 */
typedef enum stack_tipo{
    STACK_CHAR, /**< representa o tipo de uma char */
    STACK_LONG, /**< representa o tipo de uma long */
    STACK_DOUBLE, /**< representa o tipo de uma double */
    STACK_STRING, /**< representa o tipo de uma string */
    STACK_STACK, /**< representa o tipo de uma array */
    STACK_BLOCO /**< representa o tipo de um bloco */
}Enumeracao;
/**
 * @struct stack_elemento estrutura de um elemento
 * @brief Tipo e valor de cada elemento da stack.
 */
typedef struct stack_elemento{
    enum stack_tipo tipo;/**tipo do elemento dentro da union*/
    union {
        char val_c;/**< onde char's ficam guardadas */
        long val_l;/**< onde long's ficam guardadas */
        double val_d;/**< onde double's ficam guardadas */
        char* val_s;/**< onde string's e blocos ficam guardadas */
        struct stack *stk;/**< onde arrays's ficam guardadas */
    }data;/**< union onde os valores serão guardados */
}elemento;
/**
 * @struct stack estrutura da stack
 * @brief Representa a estrutura da stack desde as suas posições até ao lugar onde os inputs vão ser guardados.
 */
typedef struct stack{
    int comprimento; /**< representa a posição do topo da stack */
    elemento * elemento; /**< lugar onde os valores e os seus tipo vão ser guardados */
    elemento variaveis[26];/**< lugar onde os valores das variaveis vão ser guardados */
}* Stack,StackC;


void push(Stack stack,Enumeracao tipo,...);

void pushdata (Stack stack,elemento a);

Stack create(Stack stack);

Stack createP();

void destroy(Stack stack);

Enumeracao peek(Stack stack);

bool stack_is_empty(Stack stack);

elemento pop(Stack stack);

void print_stack(Stack stack);

int stacklen(Stack stack);

void print_elemento(elemento a);

elemento popL(Stack stack);

void printtipo(Enumeracao tipo);

void copyVariaveis(Stack stack,Stack stk);

elemento setvar(Enumeracao tipo,...);
#endif 