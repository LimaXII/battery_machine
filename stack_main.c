#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack_header.h"
#define MAX_Strings 1000
#define MAX_Lenght  100


int main(void){
    ptSTCK* ptStack;
    ptCNTL* ptControl;

    // TESTANDO COISAS
    short int num;
    ptStack = Initialize_Stack();
    char lines[MAX_Strings][MAX_Lenght];
    char instruction[6];
    bool has_reg = false;
    bool has_num = false;
    int j = 0;
    const char* filename = "teste.asm";

    /*
    // Teste com o programa do sor...
    ptStack = Clear(ptStack, ptControl);
    ptStack = Push(ptStack, ptControl, 4);
    ptStack = Push(ptStack, ptControl, 8);
    Add(ptStack, ptControl);
    ptStack = Pop(ptStack, ptControl);
    ptStack = Pop(ptStack, ptControl);
    ptStack = Push(ptStack, ptControl, ptControl->reg);
    Output(ptStack);
    */
    
    // Algoritmo responsável por abrir o arquivo e armazenar as strings de cada linha no array 2D lines
    FILE* input_file = fopen(filename, "r");
    if (!input_file)
        exit(EXIT_FAILURE);

    char *buffer = NULL;
    size_t len = 0;
    while (getline(&buffer, &len, input_file) != -1){
        int i = 0;
        while (i <= strlen(buffer) + 1)
        {
            if (buffer[0] == ';'){
                break;
            } 
            else if (buffer[i] == ';' || buffer[i] == '\0'){
                strncpy(lines[j], buffer, i);
                lines[j][i+1] = '\0';
                j++;
                break;
            }
            else{
                i++;
            }
        } 
    }

    fclose(input_file);
    free(buffer);

    // Algoritmo responsável por armazenar e verificar a instrução informada. Realizando o controle de leitura e execução linha a linha.
    for (int k = 0; k < j; k++){
        for (int i = 0; i <= strlen(lines[k] + 1); i++){
            if ((lines[k][i] >= 'A' && lines[k][i] <= 'Z') || (lines[k][i] >= 'a' && lines[k][i] <= 'z') || lines[k][i] == '\0'){
                if (has_reg == false){
                    instruction[i] = lines[k][i];
                }
            }
            else if (lines[k][i] >= '0' && lines[k][i] <= '9'){
                num = lines[k][i] - '0';
                has_num = true;
            }
            else if (lines[k][i] == '$' && (lines[k][i+1] == 'R'|| lines[k][i+1] == 'r')){
                has_reg = true;
            }
        }


        if (strcmp(instruction, "CLEAR") == 0 || strcmp(instruction, "clear") == 0){
            ptStack = Clear(ptStack, ptControl);
            printf("executa CLEAR\n");
        }

        if ((strcmp(instruction, "PUSH") == 0 || strcmp(instruction, "push") == 0) && has_num == true){
            ptStack = Push(ptStack, ptControl, num);
            printf("executa PUSH N\n");
        }

        if ((strcmp(instruction, "PUSH") == 0 || strcmp(instruction, "push") == 0) && has_reg == true){
            ptStack = Push(ptStack, ptControl, ptControl->reg);
            printf("executa PUSH $R\n");
        }

        if (strcmp(instruction, "POP") == 0 || strcmp(instruction, "pop") == 0){
            ptStack = Pop(ptStack, ptControl);
            printf("executa POP\n");
        }

        if (strcmp(instruction, "ADD") == 0 || strcmp(instruction, "add") == 0){
            Add(ptStack, ptControl);
            printf("executa ADD\n");
        }

        if (strcmp(instruction, "SUB") == 0 || strcmp(instruction, "sub") == 0){
            printf("executa SUB\n");
        }

        if (strcmp(instruction, "MUL") == 0 || strcmp(instruction, "mul") == 0){
            printf("executa MUL\n");
        }

        if (strcmp(instruction, "DIV") == 0 || strcmp(instruction, "div") == 0){
            printf("executa DIV\n");
        }

        if (strcmp(instruction, "MOD") == 0 || strcmp(instruction, "mod") == 0){
            printf("executa MOD\n");
        }

        if (strcmp(instruction, "NOT") == 0 || strcmp(instruction, "not") == 0){
            printf("executa NOT\n");
        }

        if (strcmp(instruction, "OR") == 0 || strcmp(instruction, "or") == 0){
            printf("executa OR\n");
        }

        if (strcmp(instruction, "AND") == 0 || strcmp(instruction, "and") == 0){
            printf("executa AND\n");
        }

        if (strcmp(instruction, "MIR") == 0 || strcmp(instruction, "mir") == 0){
            printf("executa MIR\n");
        }

        if (strcmp(instruction, "OUT") == 0 || strcmp(instruction, "out") == 0){
            Output(ptStack);
            printf("\nexecuta OUT\n");
        }
        
        memset(instruction,0,sizeof(instruction));
        has_num = false;
        has_reg = false;
    }
    

    exit(EXIT_SUCCESS);
    return 0;
}