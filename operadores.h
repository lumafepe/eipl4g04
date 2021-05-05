#ifndef OPERADORES_H_
#define OPERADORES_H_
/**
 * @param stack é a stack onde os valores estao guardados
 * @param stk array a copiar
 * @param a numero de repetiçoes da array
 */
void arraymult(Stack stack,Stack stk,double a);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param a elemento com a string a copiar
 * @param n numero de repetiçoes da string
 */
void strmult(Stack stack,struct stack_elemento a,double n);
/**
 * @param stack é a stack onde guardar os valores
 * @param stk array de onde remover o elemento
 */
void menosmenosR(Stack stack,Stack stk);
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
/**
 * @param stack é a stack onde os valores estao guardados
 */
void virgula(Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param a elemento que contem o numero onde parar a criação de numeros
 */
void range(Stack stack,struct stack_elemento a);
/**
 * @param stack é a stack/array onde os valores vao ser guardados
 * @param stk é a stack/array de onde copiar os valores
 */
void colocartodos(Stack stack,Stack stk);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param a elemento a quem juntar a array
 * @param stk1 array de onde ir buscar os valores a juntar
 */
void concatenarDeArrays (Stack stack,struct stack_elemento a,Stack stk1);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param stk1 array a quem concatenar um valor
 * @param a elemnto a concatenar
 */
void concatenarAArrays (Stack stack,Stack stk1,struct stack_elemento a);
/**
 * @param stack é a stack onde os valores estao guardados
 */
void dividepornewline (Stack stack);
/**

