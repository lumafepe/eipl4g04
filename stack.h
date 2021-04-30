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
    STACK_STACK /**< representa o tipo de uma array */
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
        char val_c;/**< onde char's ficam guardadas */
        long val_l;/**< onde long's ficam guardadas */
        double val_d;/**< onde double's ficam guardadas */
        char* val_s;/**< onde string's ficam guardadas */
        struct stack *stk;/**< onde arrays's ficam guardadas */
    }data;/**< union onde os valores serão guardados */
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
 * @typedef StackC
 * @brief Define o tamanho em bites de uma stack.
 */
typedef struct stack  StackC;

void push(Stack stack,const enum stack_tipo tipo,...);

void pushdata (Stack stack,struct stack_elemento a);

void copyVariaveis(Stack stack,Stack stk); 

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

struct stack_elemento setvar(const enum stack_tipo tipo,...);
#endif 