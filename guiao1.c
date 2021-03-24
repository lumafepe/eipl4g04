#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//defenir o data type (nº de elementos e os elementos)
struct Stack{
    int comprimento; //pos do topo
    int *array; // onde os valores sao guardada
};
// aumenta o tamanho da array e adiciona o elemento no inicio da array
void push(struct Stack* stack,int eaa){ // eaa --> elemento a adicionar
    stack->comprimento++; //aumenta a pos do topo
    stack->array = realloc(stack->array,(stack->comprimento+1) * sizeof(int)); // aumenta o tamanho da array
    stack->array[stack->comprimento]=eaa; // guarda o novo valor na array
}

// diminui o tamanho da array e devolve o que esta no topo
int pop(struct Stack* stack){
    if (stack->comprimento>=0){//verificar que tem elementos
        int a = stack->array[stack->comprimento]; // valor a devolver
        stack->array = realloc(stack->array,(stack->comprimento) * sizeof(int)); //reduzir o tamanho da array da stack
        stack->comprimento--; // diminur posição do topo da lista
        return a;
    } else return 0;
}

// para dar valores iniciais a stack
void inicializador(struct Stack* stack){
    stack->array = (int *) malloc(0 * sizeof(int));//define a array da stack como tendo 0 bits
    stack->comprimento=-1;//proxima pos a guardar passa a 0
}
//equivalente  a pow da libraria math.h mas para funcionar com int em vez de double
int powints( int base, int expoente){
    if (expoente == 0) return 1; //condição de paragens recursiva
    int ac = powints(base, expoente/2); 
    if (expoente % 2 == 0)  //algoritmo de calculamento de um numero eleveado a outro
        return ac* ac;
    else
        return (base * ac * ac);
}
// equivalente a ++ de c
void maismais(struct Stack* stack){
    push(stack,pop(stack)+1);
}

// equivalente a -- de c
void menosmenos(struct Stack* stack){
    push(stack,pop(stack)-1);
}

// equivalente à soma de dois valores
void mais(struct Stack* stack){
    push(stack,pop(stack)+pop(stack));
}
// equivalente à subtração de dois valores
void menos(struct Stack* stack){
    int a = pop(stack);
    push(stack,pop(stack)-a);
}
// equivalente à multiplicação de dois valores
void mult(struct Stack* stack){
    push(stack,pop(stack)*pop(stack));
}
// equivalente à divisão de dois valores
void divisao(struct Stack* stack){
    int a=pop(stack);
    push(stack,pop(stack)/a);
}
// equivalente ao resto da divisão de dois valores
void restoDivisao (struct Stack* stack){
    int a = pop(stack);
    push(stack,(pop(stack)%a));
}
// equivalente à exponenciação de valores
void expoente (struct Stack* stack){
    int a = pop(stack);
    push(stack,powints(pop(stack),a));
}
// equivalente à interseção dos bits correspondentes ao número
void conjuncao(struct Stack* stack){
   push(stack,pop(stack)&pop(stack));
}
// equivalente à disjunção dos bits correspondentes ao número
void disjuncao(struct Stack* stack){
    push(stack,pop(stack)|pop(stack));
}
// compara bits correspondentes a um número, atribuindo 1 sempre que são distintos
void xor(struct Stack* stack){
    push(stack,pop(stack)^pop(stack));
}

// função auxiliar da função leitura
void leitura2(struct Stack* stack,char c[])
{
    if (c[0] <= '9' && c[0]>='0'){ // condição que verifica se corresponde a um número ou a um operador
        push(stack,atoi(c));
    }
    else{ // a cada operador faz corresponder a sua função
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
            default: 
                break;
        } 
    }
}

//faz o tratamento de dados do input do utilizador
void leitura (struct Stack* stack){
    char str[100];
    assert(scanf("%100[^\n]",str)==1);//lê a linha inserida pelo utilizador e guarda-a em str
    char* token;
    char* rest = str; 
    while ((token = strtok_r(rest, " ", &rest))){ // separa a string por espaçoes e manda para a auxiliar leitura2 cada um dos numeros
        leitura2(stack,token);
    }
}

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
