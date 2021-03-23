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
int main() {
    struct Stack stack; //cria uma stack chamada stack
    for (int i=0; i<stack.comprimento; i++){//mostra o conteudo da stack
        printf("%d ", stack.array[i]);
    }
    printf("\n");
    return 0;
}
