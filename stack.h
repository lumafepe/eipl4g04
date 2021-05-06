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
    STACK_STRING, /**< representa o tipo de uma string */
    STACK_STACK, /**< representa o tipo de uma array */
    STACK_BLOCO /**< representa o tipo de um bloco */
};
/**
 * @struct stack_elemento estrutura de um elemento
 * @brief Tipo e valor de cada elemento da stack.
 */
struct stack_elemento{
    enum stack_tipo tipo;/**tipo do elemento dentro da union*/
    union {
        char val_c;/**< onde char's ficam guardadas */
        long val_l;/**< onde long's ficam guardadas */
        double val_d;/**< onde double's ficam guardadas */
        char* val_s;/**< onde string's e blocos ficam guardadas */
        struct stack *stk;/**< onde arrays's ficam guardadas */
    }data;/**< union onde os valores serão guardados */
};
/**
 * stack estrutura da stack
 * @brief Representa a estrutura da stack desde as suas posições até ao lugar onde os inputs vão ser guardados.
 */
struct stack{
    int comprimento; /**< representa a posição do topo da stack */
    struct stack_elemento * elemento; /**< lugar onde os valores e os seus tipo vão ser guardados */
    struct stack_elemento variaveis[26];/**< lugar onde os valores das variaveis vão ser guardados */
};
/**
 * Stack tipo de uma stack
 * @brief Define o tipo da stack.
 */
typedef struct stack * Stack;
/**
 * StackC tipo para o comprimento de uma stack
 * @brief Define o tamanho em bytes da stack da stack.
 */
typedef struct stack  StackC;

void push(Stack stack,const enum stack_tipo tipo,...);

void pushdata (Stack stack,struct stack_elemento a);

Stack create(Stack stack);

Stack createP();

void destroy(Stack stack);

enum stack_tipo peek(Stack stack);

bool stack_is_empty(Stack stack);

struct stack_elemento pop(Stack stack);

void print_stack(Stack stack);

int stacklen(Stack stack);

void print_elemento(struct stack_elemento a);

struct stack_elemento popL(Stack stack);

void printtipo(const enum stack_tipo tipo);

void copyVariaveis(Stack stack,Stack stk);

struct stack_elemento setvar(const enum stack_tipo tipo,...);
#endif 