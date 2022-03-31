typedef struct Stack ptSTCK;
typedef struct Stack_Control ptCNTL;

// Struct definindo a estrutura da pilha.
struct Stack{
    // Cada nodo da pilha terá um campo que irá guardar um número inteiro (short, de 2 bytes), que será o top da pilha.
    short int top;
    // Além do número, terá um ponteiro que apontará para o próximo nodo da pilha.
    ptSTCK *next;
};

// Struct para controle das variáveis internas da pilha.
struct Stack_Control{
    // Variável short inteira que irá armazenar o tamanho atual da pilha (até um máximo de 128 palavras de tamanho)
    short int counter;
    // Variável que representa o registrador $R da pilha.
    short int reg;
};

// Inicializa a pilha.
ptSTCK* Initialize_Stack(ptCNTL* ptControl);
// Coloca um elemento no topo da pilha.
ptSTCK* Push(ptSTCK* ptStack, ptCNTL* ptControl, short int num);
// Retira o elemento do topo da lista.
ptSTCK* Pop(ptSTCK* ptStack, ptCNTL* ptControl);

// Instruções que não possuem parâmetro.
// Soma os dois elementos do topo da pilha e armazena o resultado em $R
ptSTCK* Add(ptSTCK* ptStack, ptCNTL* ptControl);
// Subtrai os dois elementos do topo da pilha e armazena o resultado em $R
ptSTCK* Sub(ptSTCK* ptStack, ptCNTL* ptControl);
// Multiplica os dois elementos do topo da pilha e armazena o resultado em $R
ptSTCK* Mul(ptSTCK* ptStack, ptCNTL* ptControl);
// Divide os dois elementos do topo da pilha e armazena o resultado em $R
ptSTCK* Div(ptSTCK* ptStack, ptCNTL* ptControl);
// Divide os dois elementos do topo da pilha e armazena o resto da divisão em $R
ptSTCK* Mod(ptSTCK* ptStack, ptCNTL* ptControl);

// Instruções que possuem parâmetro (apenas um operando).
// Inverte os bits do elemento no topo da pilha.
ptSTCK* Not(ptSTCK* ptStack);
// Realiza um OR com os bits do número armazenado no topo da pilha.
ptSTCK* Or(ptSTCK* ptStack);
// Realiza um AND com os bits do número armazenado no topo da pilha.
ptSTCK* And(ptSTCK* ptStack);
// Espelha os bits do número armazenado no topo da pilha.
ptSTCK* Mir(ptSTCK* ptStack);

// Printa na tela o valor no topo da pilha.
void Output(ptSTCK* ptStack);

// Destroí a pilha e limpa a memória.
ptSTCK* Clear(ptSTCK* ptStack);