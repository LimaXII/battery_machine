#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack_header.h"
#define MAX_Strings 1000
#define MAX_Lenght  100

    

int main(void){
    // Inicializa as variáveis de controle e vetores de strings.
    int total_lines = 0;
    int valid_lines = 0;
    short int num = 0;
    bool has_reg;
    bool has_num;
    bool stop;
    bool overflow;
    char lines[MAX_Strings][MAX_Lenght] = {0};
    char instruction[6] = {0};
    char number_string[6] = {0};
    const char* filename = "teste.asm";
    //char filename[MAX_Lenght] = {0}; Variável para armazenar uma string com o nome do arquivo dado pelo usuário.

    // Inicializa a pilha
    ptSTCK* ptStack;
    ptCNTL* ptControl;
    ptStack = Initialize_Stack();
    
    /* Código para receber um arquivo dado pelo usuário mas por algum motivo não funciona quando executado.
    printf("Insira o nome do arquivo com a extensao:");
    scanf("%s", filename);
    */

    // Algoritmo responsável por abrir o arquivo e armazenar as strings de cada linha no array 2D lines
    // Realiza a abertura do arquivo no modo leitura e imprime o erro caso não consiga abrir.
    FILE* input_file = fopen(filename, "r");
    if (!input_file){
        printf("Falha ao abrir o arquivo!");
        return -1;
    }
    // Inicializa um buffer de string, responsável por armazenar cada linha e auxiliar no controle.
    char *buffer = NULL;
    size_t len = 0;
    // Realiza a leitura de cada linha do arquivo.
    while (getline(&buffer, &len, input_file) != -1){
        int i = 0;
        // Iteração responsável por ler cada caractere da linha armazenada no buffer e guardar somente a parte do código sem os comentários.
        while (i <= strlen(buffer) + 1)
        {
            if (buffer[0] == ';'){
                total_lines++;
                break;
            } 
            // Armazena o código anterior ao comentário no array 2d lines[valid_lines][i].
            else if (buffer[i] == ';' || buffer[i] == '\0'){
                strncpy(lines[valid_lines], buffer, i);
                lines[valid_lines][i+1] = '\0';
                total_lines++;
                valid_lines++;
                break;
            }
            // Caso o caractere não seja um ';' ou NULL, continua para o próximo caractere.
            else{
                i++;
            }
        } 
    }
    // Realiza o fechamento do arquivo e libera o espaço alocado para o buffer.
    fclose(input_file);
    free(buffer);

    // Algoritmo responsável por armazenar e verificar a instrução informada. Realizando o controle de leitura e execução linha a linha.
    // Iteração que percorre cada linha do array 2D
    for (int k = 0; k < valid_lines; k++){
        // Reseta as variáveis para a linha
        memset(instruction,0,sizeof(instruction));
        has_num = false;
        has_reg = false;
        overflow = false;
        stop = false;
        num = 0;
        //Incializa a variável auxiliar m para a string de números
        int m = 0;                      
        // Iteração que percorre cada caractere da linha e armazena na string auxiliar instruction {Matheus: Na linha abaixo consta o erro do reg}               
        for (int l = 0; l <= strlen(lines[k]) + 1; l++){           
            if ((lines[k][l] >= 'A' && lines[k][l] <= 'Z') || (lines[k][l] >= 'a' && lines[k][l] <= 'z') || lines[k][l] == '\0'){
                if (has_reg == false){
                    instruction[l] = lines[k][l];
                }
            }
            // Verifica a existência de um número inteiro e armazena em um string para posterior conversão em inteiro.
            // Caso o valor seja maior que 32767 ou menor que -32768, isto é o maior e menor valor em complemento de 2 para 16 bits.
            else if (lines[k][l] >= '0' && lines[k][l] <= '9'){
                number_string[m] = lines[k][l];
                num = atoi(number_string);
                if (num > 32767 || num < -32768){
                    overflow = true;
                    break;
                }
                has_num = true;
                m++;
            }
            // Verifica a existência do parametro "$R", caso encontre mais de uma vez o torna inválido e imprime o erro.
            else if (lines[k][l] == '$' && (lines[k][l+1] == 'R'|| lines[k][l+1] == 'r') && lines[k][l-1] != '$'){
                if (stop == true){
                    has_reg = false;
                }
                else{
                    has_reg = true;
                    stop = true;
                }
            }
        }
        // Controle das intruções lidas
        // ERRO EXTRA:Caso haja stop seja true e o registrador seja falso(operando $R informado mais de uma vez), imprime o erro no registrador e para a iteração.
        // ERRO EXTRA:Caso o valor do operando seja maior que a representação em complemento de 2 de 16 bits, imprime o erro de overflow.
        // Condicionais que comparam a string instruction com os possíveis comandos e também realiza o tratamento de erros da linha.
        // Caso as variáveis booleanas de número e registrador sejam verdadeiras para instruções que não as esperam, os condicionais printam o erro na tela.
        // Caso nenhuma das instruções seja reconhecida, imprime o erro de instrução inválida no final.
        // A linha informada é resultado da operação que subtrai as linhas totais das válidas e incremenda baseado em k + 1.
        if (stop == true && has_reg == false){
            printf("ERRO NA LINHA %d: ERRO DE SINTAXE NO OPERANDO $R\n", total_lines - valid_lines + k + 1);
            break;
        }
        else if (overflow == true){
            printf("ERRO NA LINHA %d: OVERFLOW NO VALOR INFORMADO\n", total_lines - valid_lines + k + 1);
            break;
        }
        else if (strcmp(instruction, "CLEAR") == 0 || strcmp(instruction, "clear") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ERRO DE SINTAXE\n", total_lines - valid_lines + k + 1);
                break;
            }
            ptStack = Clear(ptStack, ptControl);
            printf("executou CLEAR\n");     // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
        }
        else if ((strcmp(instruction, "PUSH") == 0 || strcmp(instruction, "push") == 0)){
            //printf("%d\n", num);          // DEBUG:Testa o valor de num antes de passar para o push
            if ((has_num == false && has_reg == false) || (has_num == true && has_reg == true)){
                printf("ERRO NA LINHA %d: ERRO DE SINTAXE\n", total_lines - valid_lines + k + 1);
                break;
            }
            if (has_num == true && has_reg == false) {
                ptStack = Push(ptStack, ptControl, num, total_lines, valid_lines, k);
                printf("executou PUSH N\n");
            }
            if (has_num == false && has_reg == true) {
            ptStack = Push(ptStack, ptControl, ptControl->reg, total_lines, valid_lines, k);
            printf("executou PUSH $R\n");   // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
            }
        }
        else if (strcmp(instruction, "POP") == 0 || strcmp(instruction, "pop") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ERRO DE SINTAXE\n", total_lines - valid_lines + k + 1);
                break;
            }
            ptStack = Pop(ptStack, ptControl, total_lines, valid_lines, k);
            printf("executou POP\n");       // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
        }
        else if (strcmp(instruction, "ADD") == 0 || strcmp(instruction, "add") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ARGUMENTO INVALIDO\n", total_lines - valid_lines + k + 1);
                break;
            }
            Add(ptStack, ptControl);
            printf("executou ADD\n");       // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
        }
        else if (strcmp(instruction, "SUB") == 0 || strcmp(instruction, "sub") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ARGUMENTO INVALIDO\n", total_lines - valid_lines + k + 1);
                break;
            }
            Sub(ptStack, ptControl);
            printf("executou SUB\n");       // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
        }
        else if (strcmp(instruction, "MUL") == 0 || strcmp(instruction, "mul") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ARGUMENTO INVALIDO\n", total_lines - valid_lines + k + 1);
                break;
            }
            Mul(ptStack, ptControl);
            printf("executou MUL\n");        // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA;
        }
        else if (strcmp(instruction, "DIV") == 0 || strcmp(instruction, "div") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ARGUMENTO INVALIDO\n", total_lines - valid_lines + k + 1);
                break;
            }
            Div(ptStack, ptControl);
            printf("executou DIV\n");       // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
        }
        else if (strcmp(instruction, "MOD") == 0 || strcmp(instruction, "mod") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ARGUMENTO INVALIDO\n", total_lines - valid_lines + k + 1);
                break;
            }
            Mod(ptStack, ptControl);
            printf("executou MOD\n");       // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
        }
        else if (strcmp(instruction, "NOT") == 0 || strcmp(instruction, "not") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ARGUMENTO INVALIDO\n", total_lines - valid_lines + k + 1);
                break;
            }
            Not(ptStack, ptControl);
            printf("executou NOT\n");       // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
        }
        else if (strcmp(instruction, "OR") == 0 || strcmp(instruction, "or") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ARGUMENTO INVALIDO\n", total_lines - valid_lines + k + 1);
                break;
            }
            Or(ptStack, ptControl);
            printf("executou OR\n");        // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
        }
        else if (strcmp(instruction, "AND") == 0 || strcmp(instruction, "and") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ARGUMENTO INVALIDO\n", total_lines - valid_lines + k + 1);
                break;
            }
            And(ptStack, ptControl);
            printf("executou AND\n");       // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
        }
        else if (strcmp(instruction, "MIR") == 0 || strcmp(instruction, "mir") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ARGUMENTO INVALIDO\n", total_lines - valid_lines + k + 1);
                break;
            }
            // Mir(ptStack, ptControl)                                                          Falta implementar
            printf("executou MIR\n");       // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
        }
        else if (strcmp(instruction, "SQRT") == 0 || strcmp(instruction, "sqrt") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ARGUMENTO INVALIDO\n", total_lines - valid_lines + k + 1);
                break;
            }
            Sqrt(ptStack, ptControl);
            printf("executou SQRT\n");
        }
        else if (strcmp(instruction, "OUT") == 0 || strcmp(instruction, "out") == 0){
            if (has_num == true || has_reg == true){
                printf("ERRO NA LINHA %d: ERRO DE SINTAXE\n", total_lines - valid_lines + k + 1);
                break;
            }
            Output(ptStack);
            printf("executou OUT\n");       // DEBUG:IMPRIME A INSTRUÇÃO EXECUTADA
        }
        else{
            printf("ERRO NA LINHA %d: INSTRUCAO INVALIDA\n", total_lines - valid_lines + k + 1);
            break;
        }
        printf("%d\n", ptControl->reg);         //DEBUG: IMPRIME O VALOR DO REGISTRADOR
    }
    return 0;
}