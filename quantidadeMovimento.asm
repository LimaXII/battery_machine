; Algoritmo para cálculo de quantidade de movimento
; Q = m * v
CLEAR			; limpa a pilha e configura o PC para o endereço zero
PUSH 2		; empurra o número 2 na pilha, a pilha é [2]
PUSH 5		; empurra o número 5 na pilha, a pilha é [2, 5]
MUL			; multiplica os dois valores no topo da pilha e empurra o resultado
POP			; remove o primeiro operando da pilha
POP			; remove o segundo operando da pilha
PUSH $R		; empurra o resultado para a pilha
OUT			; imprime o topo da pilha na tela