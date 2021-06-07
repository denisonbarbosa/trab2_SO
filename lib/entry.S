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
	# saving context
	movq current_running, %rsp
	pushfq
	pushq %rax
	pushq %rbx
	pushq %rcx
	pushq %rdx
	pushq %rbp
	pushq %rsi
	pushq %rdi
	pushq %r8
	pushq %r9
	pushq %r10
	pushq %r11
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	
	call scheduler
	movq current_running, %rsp
	# restoring context
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %r11
	popq %r10
	popq %r9
	popq %r8
	popq %rdi
	popq %rsi
	popq %rbp
	popq %rdx
	popq %rcx
	popq %rbx
	popq %rax
	popfq
	ret

