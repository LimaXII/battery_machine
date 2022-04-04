;Algoritmo para cáculo da raiz quadrada

CLEAR		;limpa a pilha e configura o pc para 0	
PUSH 9		;empurra o número 9 na pilla, pilha é[9]
SQRT		;faz o calculo da raiz quadrada
POP		;remove o primeiro operando da pilha
PUSH $R		;empurra o resultado para a pilha
OUT		;imprime o topo da pilha