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

int main() {
    struct Stack stack; //cria uma stack chamada stack
    inicializador(&stack);//adiciona valores iniciais a stack
    for (int i=0; i<stack.comprimento; i++){//mostra o conteudo da stack
        printf("%d ", stack.array[i]);
    }
    printf("\n");
    return 0;
}
