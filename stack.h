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
    STACK_BLOCO, /**< representa o tipo de um bloco */
    STACK_VAZIO /**< um tipo especial para nao dar push de um dado elemento */
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
        char* val_s;/**< onde string's e blocos ficam guardadas */
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
 * @brief Define o tamanho em bytes da stack da stack.
 */
typedef struct stack  StackC;
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
 * @param stack de onde copiar as variaveis.
 * @return stack inteira.
 */

Stack create(Stack stack);
/**
 * @return stack inteira.
 */
Stack createP();
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
/** 
 * @param stack onde verificar o comprimento
 * @return comprimento da stack 
 */
int stacklen(Stack stack);
/**
 * 
 * @param a elemento a mostrar no ecra
 */
void print_elemento(struct stack_elemento a);
/**
 * @param stack onde remover primeiro elemento
 * @return primeiro elemento da stack
 */
struct stack_elemento popL(Stack stack);
/**
 * @param tipo que tipo tem escrever
 */
void printtipo(const enum stack_tipo tipo);
/**
 * @param stack stack para onde copiar as variaveis
 * @param stk stack de onde copiar as variaveis
 */
void copyVariaveis(Stack stack,Stack stk);
/**
 * @param tipo tipo do elemento
 * @param ... valor a guardar no elemento
 * @return elemento com o valor e tipo dado 
 */
struct stack_elemento setvar(const enum stack_tipo tipo,...);
#endif //fim do guião 
