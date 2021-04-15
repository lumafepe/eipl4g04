#ifndef OPERADORES_H_
#define OPERADORES_H_

/**
 *
 * @param stack é a stack onde os valores estao guardados.
 */
void maismais(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void menosmenos(Stack stack);
/**
 * @param a é um elemento da nossa stack.
 * @return devolve em double o elemento da stack.
 */
double toD (struct stack_elemento a);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void mais(Stack stack);
/**
 *
 * @param stack é a stack onde os valores estao guardados.
 */
void menos(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void mult(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void divisao(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void restoDivisao (Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void expoente (Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void conjuncao(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void disjuncao(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void xor (Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void not (Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void copian(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void trocar (Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void rodar (Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void duplica(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void convL (Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void convD (Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void convC (Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void maior(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void menor(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void maiorb(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void menorb(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void ou(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void e(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void ifthenelse(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void igual(Stack stack );
/**
 * @param stack é a stack onde os valores estao guardados.
 */
void notb(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados.
 * @param s variaval onde ir buscar o valor
 */
void var2stack(Stack stack,char s);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param s variaval onde guardar
 */
void stack2var(Stack stack,char s);

#endif