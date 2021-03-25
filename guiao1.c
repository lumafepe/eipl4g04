/**
 * @file ficheiro principal do programa
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * \brief definir o data type (nº de elementos e os elementos).
*/
struct Stack{
    int comprimento; /**< representa a posição do topo da stack */
    int *array; /**< lugar onde os valores vão ser guardados */
};

/**
 * \brief aumenta o tamanho da stack e adiciona o elemento ao inicio da array.
*/
void push(struct Stack* stack,int eaa){ // eaa --> elemento a adicionar
    stack->comprimento++; //aumenta a pos do topo
    stack->array = realloc(stack->array,(stack->comprimento+1) * sizeof(int)); // aumenta o tamanho da array
    stack->array[stack->comprimento]=eaa; // guarda o novo valor na array
}

/**
 * \brief diminui o tamanho da stack e devolve o que estava no topo.
 * @return elemento no topo da stack
*/
int pop(struct Stack* stack){
    if (stack->comprimento>=0){//verificar que tem elementos
        int a = stack->array[stack->comprimento]; // valor a devolver
        stack->array = realloc(stack->array,(stack->comprimento) * sizeof(int)); //reduzir o tamanho da array da stack
        stack->comprimento--; // diminur posição do topo da lista
        return a;
    } else return 0;
}

/**
 * \brief serve para dar valores iniciais a stack.
*/
void inicializador(struct Stack* stack){
    stack->array = (int *) malloc(0 * sizeof(int)); /**< inicia o tamanho da array onde os dados vao ser guardados como 0 */
    stack->comprimento=-1; /**< inicia o topo da array como na posição -1 */
}

/**
 * \brief equivalente a pow da libraria math.h mas para funcionar com int em vez de double.
 * @return número resultante da base elevada ao expoente
*/
int powints( int base, int expoente){
    if (expoente == 0) return 1; //condição de paragens recursiva
    int ac = powints(base, expoente/2); 
    if (expoente % 2 == 0)  //algoritmo de calculamento de um numero eleveado a outro
        return ac* ac;
    else
        return (base * ac * ac);
}
/**
* \brief equivalente a ++ de c.
*/
void maismais(struct Stack* stack){
    push(stack,pop(stack)+1);
}

/**
* \brief equivalente a -- de c.
*/
void menosmenos(struct Stack* stack){
    push(stack,pop(stack)-1);
}

/**
* \brief equivalente à soma de dois valores.
*/
void mais(struct Stack* stack){
    push(stack,pop(stack)+pop(stack));
}
/**
* \brief equivalente à subtração de dois valores.
*/
void menos(struct Stack* stack){
    int a = pop(stack);
    push(stack,pop(stack)-a);
}
/**
* \brief equivalente à multiplicação de dois valores.
*/
void mult(struct Stack* stack){
    push(stack,pop(stack)*pop(stack));
}
/**
* \brief equivalente à divisão inteira de dois valores.
*/
void divisao(struct Stack* stack){
    int a=pop(stack);
    push(stack,pop(stack)/a);
}
/**
* \brief equivalente ao resto divisão inteira de dois valores.
*/
void restoDivisao (struct Stack* stack){
    int a = pop(stack);
    push(stack,(pop(stack)%a));
}
/**
 * \brief equivalente à exponenciação de valores.
*/
void expoente (struct Stack* stack){
    int a = pop(stack);
    push(stack,powints(pop(stack),a));
}
/**
 * \brief equivalente à interseção dos bits correspondentes ao número.
*/
void conjuncao(struct Stack* stack){
   push(stack,pop(stack)&pop(stack));
}
/**
 * \brief equivalente à disjunção dos bits correspondentes ao número.
*/
void disjuncao(struct Stack* stack){
    push(stack,pop(stack)|pop(stack));
}
/**
 * \brief compara bits correspondentes a um número, atribuindo 1 sempre que são distintos.
*/
void xor(struct Stack* stack){
    push(stack,pop(stack)^pop(stack));
}
/**
 * \brief inverte os bits de um inteiro.
*/
void not(struct Stack* stack){
    push(stack,~pop(stack));
}
/**
 * Função auxiliar da função leitura
 * Esta função, dada uma string, distingue se é constituida por inteiros ou constituida por um operador
 * No caso de se verificar a presença de uma string constituida por inteiros esta tranforma-a num número inteiro (atoi) e adiciona-o ao topo da stack, caso contrário, realiza a função do operador em questão
*/
void leitura2(struct Stack* stack,char c[])
{
    int a=1;
    unsigned i;
    for (i=0;i<strlen(c);i++){
        if (c[i] <= '9' && c[i]>='0'){ // condição que verifica se corresponde a um número ou a um operador
            push(stack,atoi(c));
            a=0;
            break;}
    }
    if (a){ // a cada operador faz corresponder a sua função
        switch (c[0]) {
            case '%':
                restoDivisao(stack);
                break;
            case '#':
                expoente(stack);
                break;
            case '&':
                conjuncao(stack);
                break;
            case '|':
                disjuncao(stack);
                break;
            case '^':
                xor(stack);
                break;
            case '+':
                mais(stack);
                break;
            case '-': 
                menos(stack);
                break;
            case '*':
                mult(stack);
                break;
            case '/': 
                divisao(stack);
                break;
            case ')':
                maismais(stack);
                break;
            case '(':
                menosmenos(stack);
                break;
            case '~':
                not(stack);
                break;
            default: 
                break;
        } 
    }
}

/**
 * Esta é a função que trata da leitura do input do user
 * Esta separa-o por espaços e a cada conjunto de elemento envia-os para a leitura2 para serem processados
*/
void leitura (struct Stack* stack){
    char str[1024];
    assert(scanf("%1024[^\n]",str)==1);//lê a linha inserida pelo utilizador e guarda-a em str
    char* token;
    char* rest = str; 
    while ((token = strtok_r(rest, " ", &rest))){ // separa a string por espaçoes e manda para a auxiliar leitura2 cada um dos numeros
        leitura2(stack,token);
    }
}
/**
 * Esta é a função principal do nosso guião
 * Chama as funções que constituem o nosso trabalho desde a chamada da stack para o armazenazamento dos inputs dados pelo utilizador ao cálculo das operações pedidas
 * Mostra também o conteúdo existente na stack
 * @return 0
 */
int main() {
    struct Stack stack; //cria uma stack chamada stack
    inicializador(&stack);//adicona valores iniciais a stack
    leitura(&stack);//trata da leitura e processamento dos inputs do user
    for (int i=0; i<=stack.comprimento; i++){//mostra o conteudo da stack
        printf("%d", stack.array[i]);
    }
    printf("\n");
    return 0;
}



