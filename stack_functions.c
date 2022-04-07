#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack_header.h"

// Inicializa a pilha e retorna NULL.
ptSTCK* Initialize_Stack(){
    return NULL;
}

// Aloca um elemento no topo da pilha.
ptSTCK* Push(ptSTCK* ptStack, ptCNTL* ptControl, short int num, int a, int b, int c){
    ptSTCK *new, *ptAux = ptStack;
    new = (ptSTCK*) malloc(sizeof(ptSTCK));   
    new->top = num;   

    // Testa se a pilha já esta cheia.
    if(ptControl->counter >= (128)){        
        printf("ERRO NA LINHA %d:PUSH EM QUEUE CHEIA\n", a - b + c + 1);
        return ptStack;
    }
    // Se não estiver, incrementar o contador.
    else{
        ptControl->counter = ptControl->counter + 1;
    }

    // Caso a pilha esteja vazia, irá inserir no inicio dela.
    if(ptStack == NULL){ 
        new->next = ptStack;
        ptStack = new;
    }
    // Caso não esteja vazia.
    else{
        // Percorre a pilha até o topo.
        while(ptAux->next != NULL){
            ptAux = ptAux->next;
        }
        // Coloca o elemento no topo da pilha.
        ptAux->next = new;
        new->next = NULL;
    }

    //Retorna o estado atual da pilha.
    return ptStack; 
}

// Retira o elemento que está no topo da pilha.
ptSTCK* Pop(ptSTCK* ptStack, ptCNTL* ptControl, int a, int b, int c){
    ptSTCK *ptAux = ptStack;
    // Testa se a pilha está vazia.
    if (ptAux == NULL){
        printf("ERRO NA LINHA %d:POP EM QUEUE VAZIA\n", a - b + c + 1);
        return ptStack;
    }
    // Caso tenha apenas um elemento.
    else if (ptAux->next == NULL){
        ptStack = Clear(ptStack, ptControl);
        return ptStack;
    }
    // Se não, percorre ela até o final.
    else{
        while(ptAux->next->next != NULL){
            ptAux = ptAux->next;
        }        
        // Desaloca o último elemento da pilha.
        free(ptAux->next);
        ptAux->next = NULL;
        ptControl->counter = ptControl->counter - 1;
    }
    return ptStack;
}

// Instruções que não possuem parâmetro.
// Soma os dois elementos do topo da pilha e armazena o resultado em $R
ptSTCK* Add(ptSTCK* ptStack, ptCNTL* ptControl, int a, int b, int c){
    ptSTCK *ptAux = ptStack;

    if(ptControl->counter < 2){
        printf("ERRO NA LINHA %d:SEM ELEMENTOS SUFICIENTES NA PILHA PARA REALIZAR A OPERAÇÃO.\n", a - b + c + 1);
    }
    else{
        // Percorre ela até o final da pilha.
        while(ptAux->next->next != NULL){
            ptAux = ptAux->next;
        }
        // Soma os dois elementos e armazena no registrador $R.
        ptControl->reg = ptAux->top;
        ptControl->reg = ptControl->reg + ptAux->next->top;
    }
}

// Subtrai os dois elementos do topo da pilha e armazena o resultado em $R
ptSTCK* Sub(ptSTCK* ptStack, ptCNTL* ptControl, int a, int b, int c){
    ptSTCK *ptAux = ptStack;

    if(ptControl->counter < 2){
        printf("ERRO NA LINHA %d:SEM ELEMENTOS SUFICIENTES NA PILHA PARA REALIZAR A OPERAÇÃO.\n", a - b + c + 1);
    }
    else{
        // Percorre ela até o final da pilha.
        while(ptAux->next->next != NULL){
            ptAux = ptAux->next;
        }
        // Subtrai os dois elementos e armazena no registrador $R.
        ptControl->reg = ptAux->next->top;
        ptControl->reg = ptControl->reg - ptAux->top;
    }
}

// Multiplica os dois elementos do topo da pilha e armazena o resultado em $R
ptSTCK* Mul(ptSTCK* ptStack, ptCNTL* ptControl, int a, int b, int c){
    ptSTCK *ptAux = ptStack;

    if(ptControl->counter < 2){
        printf("ERRO NA LINHA %d:SEM ELEMENTOS SUFICIENTES NA PILHA PARA REALIZAR A OPERAÇÃO.\n", a - b + c + 1);
    }
    else{
        // Percorre ela até o final da pilha.
        while(ptAux->next->next != NULL){
            ptAux = ptAux->next;
        }
        // Multiplica os dois elementos e armazena no registrador $R.
        ptControl->reg = ptAux->top;
        ptControl->reg = ptControl->reg * ptAux->next->top;
    }
}

// Divide os dois elementos do topo da pilha e armazena o resultado em $R
ptSTCK* Div(ptSTCK* ptStack, ptCNTL* ptControl, int a, int b, int c){
    ptSTCK *ptAux = ptStack;

    if(ptControl->counter < 2){
        printf("ERRO NA LINHA %d:SEM ELEMENTOS SUFICIENTES NA PILHA PARA REALIZAR A OPERAÇÃO.\n", a - b + c + 1);
    }
    else{
        // Percorre ela até o final da pilha.
        while(ptAux->next->next != NULL){
            ptAux = ptAux->next;
        }
        // Divide os dois elementos e armazena no registrador $R.
        if(ptAux->top == 0){
            printf("ERRO NA LINHA %d:DENOMIDOR COM ZERO.\n", a - b + c + 1);
        }
        else{
            ptControl->reg = ptAux->next->top;
            ptControl->reg = ptControl->reg / ptAux->top;
        }
    }
}

// Divide os dois elementos do topo da pilha e armazena o resto da divisão em $R
ptSTCK* Mod(ptSTCK* ptStack, ptCNTL* ptControl, int a, int b, int c){
    ptSTCK *ptAux = ptStack;

    if(ptControl->counter < 2){
        printf("ERRO NA LINHA %d:SEM ELEMENTOS SUFICIENTES NA PILHA PARA REALIZAR A OPERAÇÃO.\n", a - b + c + 1);
    }
    else{
        // Percorre ela até o final da pilha.
        while(ptAux->next->next != NULL){
            ptAux = ptAux->next;
        }
        // Calcula o resto da divisão dois elementos e armazena no registrador $R.
        if(ptAux->top == 0){
            printf("ERRO NA LINHA %d:DENOMIDOR COM ZERO.\n", a - b + c + 1);
        }
        else{
            ptControl->reg = ptAux->next->top;
            ptControl->reg = ptControl->reg % ptAux->top;
        }
    }
}

// Instruções que possuem parâmetro (apenas um operando).
// Inverte os bits do elemento no topo da pilha.
ptSTCK* Not(ptSTCK* ptStack, ptCNTL* ptControl, int a, int b, int c){
    ptSTCK *ptAux = ptStack;

    if(ptAux == NULL){
        printf("ERRO NA LINHA %d:SEM ELEMENTOS SUFICIENTES NA PILHA PARA REALIZAR A OPERAÇÃO.\n", a - b + c + 1);
    }
    else{
        // Percorre ela até o final da pilha.
        while(ptAux->next != NULL){
            ptAux = ptAux->next;
        }
        // Calcula o NOT do topo da pilha e coloca no registrador $R.       
        ptControl->reg = ~ptAux->top;       
    }
}

// Realiza um OR com os bits do número armazenado no topo da pilha.
ptSTCK* Or(ptSTCK* ptStack, ptCNTL* ptControl, int a, int b, int c){
    ptSTCK *ptAux = ptStack;

    if(ptControl->counter < 2){
        printf("ERRO NA LINHA %d:SEM ELEMENTOS SUFICIENTES NA PILHA PARA REALIZAR A OPERAÇÃO.\n", a - b + c + 1);
    }
    else{
        // Percorre ela até o final da pilha.
        while(ptAux->next->next != NULL){
            ptAux = ptAux->next;
        }
        // Calcula o OR do topo da pilha e coloca no registrador $R.       
        ptControl->reg = ptAux->top;
        ptControl->reg = ptControl->reg | ptAux->next->top;       
    }
}

// Realiza um AND com os bits do número armazenado no topo da pilha.
ptSTCK* And(ptSTCK* ptStack, ptCNTL* ptControl, int a, int b, int c){
    ptSTCK *ptAux = ptStack;

    if(ptControl->counter < 2){
        printf("ERRO NA LINHA %d:SEM ELEMENTOS SUFICIENTES NA PILHA PARA REALIZAR A OPERAÇÃO.\n", a - b + c + 1);
    }
    else{
        // Percorre ela até o final da pilha.
        while(ptAux->next->next != NULL){
            ptAux = ptAux->next;
        }
        // Calcula o AND do topo da pilha e coloca no registrador $R.       
        ptControl->reg = ptAux->top;
        ptControl->reg = ptControl->reg & ptAux->next->top;       
    }
}

// Espelha os bits do número armazenado no topo da pilha.
ptSTCK* Mir(ptSTCK* ptStack, ptCNTL* ptControl, int a, int b, int c){
    int vet_bin[50];
    int i = 0, j;
    int num_saida = 0, num;

    ptSTCK *ptAux = ptStack;

    if(ptAux == NULL){
        printf("ERRO NA LINHA %d:SEM ELEMENTOS SUFICIENTES NA PILHA PARA REALIZAR A OPERAÇÃO.\n", a - b + c + 1);
    }
    else{
        while(ptAux->next != NULL){
            ptAux = ptAux->next;
        }
        // transforma o numero do topo em binário
        num = ptAux->top;
        while (num > 0){
            vet_bin[i] = num % 2;
            i++;
            num = num / 2;
        }
        // percorrendo o vetor do indice menor, para o maior (indice, tanto do vetor, quanto dos bits)
        for (j = 0; j < i; j++){
            if (vet_bin[j] == 1){                       // se o bit for igual a 1
                num_saida = num_saida + pow(2, i-j-1);  // eleva 2 ao indice correspondente e soma ao resultado
            }
        }
        ptControl->reg = num_saida;
    }	
}

// Calcula a raiz quadrada do numero no topo da pilha.
ptSTCK* Sqrt(ptSTCK* ptStack, ptCNTL* ptControl, int a, int b, int c){
    ptSTCK *ptAux = ptStack;

    if(ptAux == NULL){
        printf("ERRO NA LINHA %d:SEM ELEMENTOS SUFICIENTES NA PILHA PARA REALIZAR A OPERAÇÃO.\n", a - b + c + 1);
    }
    else{
        // Percorre ela até o final da pilha.
        while(ptAux->next != NULL){
            ptAux = ptAux->next;
        }
        if (ptAux->top < 0){
            printf("ERRO NA LINHA %d:OPERANDO NEGATIVO.\n", a - b + c + 1);
        }
        else{
            // Calcula a raiz quadrada do topo da pilha e coloca no registrador $R.       
            ptControl->reg = sqrt(ptAux->top);
        }             
    }
}

// Imprime o topo da pilha na tela.
void Output(ptSTCK* ptStack){
    ptSTCK* ptAux = ptStack;
    // Testa se a pilha está vazia.
    if (ptAux == NULL){
        printf("\n PILHA VAZIA. \n");
    }
    else{
        // Percorre a pilha até o topo.
        while(ptAux->next != NULL){
        ptAux = ptAux->next;
        } 
        // Imprime o topo da pilha.
        printf("OUTPUT:%d\n", ptAux->top);        
    }    
}

// Destroí a pilha e limpa a memória alocada.
ptSTCK* Clear(ptSTCK* ptStack, ptCNTL* ptControl){
    ptSTCK *ptAux;
    // Enquanto a pilha não estiver vazia...
    while (ptStack != NULL) {
        ptAux = ptStack;
        ptStack = ptStack->next;
        // Desaloca a memória.
        free(ptAux);
        ptControl->counter = ptControl->counter - 1;
    }
    // Inicializa uma pilha nova com PC apontado para 0...
    ptStack = Initialize_Stack();
    // Após desalocar a memória, retorna NULL.
    return ptStack;
}