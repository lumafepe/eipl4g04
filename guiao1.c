#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definir o data type (nº de elementos e os elementos)
struct Stack{
    int comprimento; //pos do topo
    int *array; // onde os valores sao guardada
};

// para dar valores iniciais a stack
void inicializador(struct Stack* stack){
    stack->array = (int *) malloc(0 * sizeof(int));//define a array da stack como tendo 0 bits
    stack->comprimento=0;//proxima pos a guardar passa a 0
}

// aumenta o tamanho da array e adiciona o elemento no inicio da array
void push(struct Stack* stack,int eaa){ // eaa --> elemento a adicionar
    stack->array = realloc(stack->array,(stack->comprimento+1) * sizeof(int)); // aumenta o tamanho da array
    stack->array[stack->comprimento]=eaa; // guarda o novo valor na array
    stack->comprimento++; //aumenta a pos do topo
}

// diminui o tamanho da array e devolve o que esta no topo
int pop(struct Stack* stack){
    if (stack->comprimento>0){//verificar que tem elementos
        stack->comprimento--; // diminur posição do topo da lista
        int a = stack->array[stack->comprimento]; // valor a devolver
        stack->array = realloc(stack->array,(stack->comprimento) * sizeof(int)); //reduzir o tamanho da array da stack
        return a;
    }
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
            default: 
                break;
        } 
    }
}

int main() {
    struct Stack stack; //cria uma stack chamada stack
    inicializador(&stack);//adiciona valores iniciais a stack
    leitura(&stack);//trata da leitura e processamento dos inputs do user
    for (int i=0; i<stack.comprimento; i++){//mostra o conteudo da stack
        printf("%d ", stack.array[i]);
    }
    printf("\n");
    return 0;
}