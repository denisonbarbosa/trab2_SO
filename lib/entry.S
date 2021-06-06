	.section .data
scratch: .quad	0
	
	.text
	.globl	scheduler_entry
	
# TODO: This function executes the following steps:
# 1. saves the context of the running thread
# 2. calls the scheduler to select the thread to be executed
# 	call scheduler
# 3. restores the context of the selected thread
# movq %rax, %rbx = %rbx = %rax
	# pushq %rax = armazena o valor de rax no topo da pilha
	# popq (reg ou mem) 
	# leaq 
scheduler_entry: # rsp aponta para a pilha da thread que está executando
	
	ret

