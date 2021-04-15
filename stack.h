#ifndef STACK_H_
#define STACK_H_
#include <stdbool.h>
/**
 * @enum stack_tipo
 * @brief Tipo de cada elemento da stack.
 */
enum stack_tipo{
    STACK_CHAR, /**< representa o tipo de uma char */
    STACK_LONG, /**< representa o tipo de uma long */
    STACK_DOUBLE, /**< representa o tipo de uma double */
    STACK_STRING /**< representa o tipo de uma string */
};

/**
 * @struct stack_elemento
 * @brief Tipo e valor de cada elemento da stack.
 * @var tipo: Tipo de cada elemento da stack.
 * @var data: Membro que contem os valores guardados na stack
 */
struct stack_elemento{
    enum stack_tipo tipo;
    union {
        char val_c;
        long val_l;
        double val_d;
        char* val_s;
    }data;
};

/**
 * @struct stack
 * @brief Representa a estrutura da stack desde as suas posições até ao lugar onde os inputs vão ser guardados.
 */
struct stack{
    int comprimento; /**< representa a posição do topo da stack */
    struct stack_elemento * elemento; /**< lugar onde os valores e os seus tipo vão ser guardados */
    struct stack_elemento variaveis[26];/**< lugar onde os valores das variaveis vão ser guardados */
};

/**
 * @typedef Stack
 * @brief Define o tipo da stack.
 */
typedef struct stack * Stack;

/**
 * @param stack é a stack onde os valores estao guardados
 * @param tipo tipo do valor a guardar
 * @param ... argumentos a serem inseridos na stack
 */
void push(Stack stack,const enum stack_tipo tipo,...);

/**
 * @param stack é a stack onde os valores estao guardados
 * @param a elemnto a dar push para a stack
 */
void pushdata (Stack stack,struct stack_elemento a);

/**
 * @return stack inteira.
 */
Stack create();

/**
 * @param stack stack a destroir
 */
void destroy(Stack stack);

/**
 * @param stack onde ver tipo do topo 
 * @return tipo do elemento no topo da stack.
 */
enum stack_tipo peek(Stack stack);

/**
 * @param stack a verificar se esta vazia
 * @return 1 se stack esta vazia e 0 caso contrário.
 */
bool stack_is_empty(Stack stack);

/** 
 * @param stack onde remover o topo
 * @return elemnto que estava no topo da stack
 */
struct stack_elemento pop(Stack stack);

/**
 * @param stack a imprimir
 */
void print_stack(Stack stack);

#endif 