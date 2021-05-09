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
void strmult(Stack stack,elemento a,double n);
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
double toD (elemento a);
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
void range(Stack stack,elemento a);
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
void concatenarDeArrays (Stack stack,elemento a,Stack stk1);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param stk1 array a quem concatenar um valor
 * @param a elemnto a concatenar
 */
void concatenarAArrays (Stack stack,Stack stk1,elemento a);
/**
 * @param stack é a stack onde os valores estao guardados
 */
void dividepornewline (Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados
 */
void divideporespacos (Stack stack);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param c é a string a ser dividida
 * @param c1 string a dividir por
 */
void dividepor (Stack stack,char c[],char c1[]);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param c é a string onde procurar substring
 * @param c1 string a pesquisar por
 */
void procurasubstring (Stack stack,char c[],char c1[]);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param a é o elemento onde esta a primeira string a concatenar
 * @param b é o elemento onde esta a segunda string a concatenar
 */
void concatenastrings (Stack stack,elemento a,elemento b);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param stk array de onde remover o elemento
 */
void maismaisR(Stack stack,Stack stk);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param stk array de onde remover elementos
 * @param n numero de elementos a remover
 */
void retiraXDoFim(Stack stack,Stack stk,double n);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param stk array de onde remover elementos
 * @param n numero de elementos a remover
 */
void retiraXDoInicio(Stack stack,Stack stk,double n);
/**
 * @param a elemento a tornar em char
 * @return string correspondente ao elemento
 */
char * toS(elemento a);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param c string de onde remover o elemento
 */
void maismaisS(Stack stack,char c[]);
/**
 * @param stack é a stack onde os valores estao guardados
 * @param c string de onde remover o elemento
 */
void menosmenosS(Stack stack,char c[]);
/**
 * @param a elemento a criar copia
 * @return copia do elemento original 
 */
elemento copiaElem(elemento a);
/**
 * @param stack onde os valores estao guardados.
 */
void convS(Stack stack);
/**
 * @param stack stack onde estao os valores e onde guardar
 * @param a primeiro elemento a ordenar 
 * @param b segundo elemento a ordenar 
 * @return 1 se algum caso ocorreu
 */
int concatarray(Stack stack,elemento a,elemento b);
/**
 * @param stack stack onde estao os valores e onde guardar
 * @param a primeiro elemento a multiplicar
 * @param b segundo elemento a multiplicar
 */
int arraymulCasos(Stack stack,elemento a,elemento b);

/**
 * @param stack stack onde estao os valores e onde guardar.
 * @param c array que vamos receber como input.
 */
void aplicaBloco(Stack stack,char c[]);
/**
 * @param stack stack onde estao os valores e onde guardar.
 * @param a elemento da stack.
 * @param c array que vamos receber como input.
 */
void map(Stack stack,elemento a,char c[]);
/**
 * @param stack stack onde estao os valores e onde guardar.
 * @param stk stack que contem os valores sujeitos a alteração.
 * @param c array que vamos receber como input.
 */
void mapA(Stack stack,Stack stk,char c[]);
/**
 * @param stack stack onde estao os valores e onde guardar.
 * @param in 
 * @param c array que vamos receber como input.
 */
void mapS(Stack stack,char in[],char c[]);
/**
 * @param stack stack onde os valores estao guardados
 * @param a array/string a aplicar o bloco
 * @param c bloco a aplicar
 */
void filter(Stack stack, elemento a,char c[]);
/**
 * @param stack stack onde os valores estao guardados
 * @param stk array a aplicar o bloco
 * @param c bloco a aplicar
 */
void filterA(Stack stack,Stack stk,char c[]);
/**
 * @param stack stack onde os valores estao guardados
 * @param int string a aplicar o bloco
 * @param c bloco a aplicar
 */
void filterS(Stack stack,char in[],char c[]);
/**
 * @param stack stack onde os valores estao guardados
 * @param stk array a aplicar o bloco
 * @param c bloco a aplicar
 */
void fold(Stack stack,Stack stk, char c[]);
/**
 * @param i string a remover 1º elemento
 * @return primeiro caracter sob a forma de elemento
 */
elemento popLS(char i[]);
/**
 * tipo de um par
 * @brief define um elemento e o valor de lhe aplicar um bloco
 */
typedef struct pardevalores{
    elemento elemento;/**< representa o elemento original */
    elemento valor;/**< representa o valor pos aplicar o bloco */
}par;
/**
 * @param stack onde os valores estam guardados
 * @param stk array a ordenar
 * @param c bloco a usar para ordenar
 */
void ordenar(Stack stack,Stack stk,char c[]);
/**
 * @param stk stack onde os valores originais estao
 * @param stk1 stack onde colocar os elementos e aplicar o bloco
 * @param c bloco a aplicar
 * @param comp numero de elementos na stack
 * @param pares lista onde guardar os pares
 */
void guardaempares(Stack stk,Stack stk1,char c[],int comp,par *pares);
/**
 * @param pares lista onde guardar os pares
 * @param N numero de pares na lista
 * @param c bloco a aplicar 
 */
void ordenaPares(par *pares,int N,char c[]);
/**
 * @param stack stack onde guardar os elementos
 * @param pares lista com os pares
 * @param N numero de pares existente na lista
 */
void pushPares(Stack stack,par *pares,int N);
/**
 * @param stack stack onde o bloco e a array estão guardados
 */
void w(Stack stack);
/**
 * @param i numero a verificar os digitos
 * @return numero de digitos
 */
int contadigitos(int i);
/**
 * @param stack stack a imprimir o topo
 */
void print_topo(Stack stack);
/**
 * @param stk array onde guardar
 * @param c string a dar explode
 */
void separaString(Stack stk,char c[]);
#endif