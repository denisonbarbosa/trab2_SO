	.section .data
scratch: .quad	0

	.text
	.globl	scheduler_entry
	.type scheduler_entry, %function
	
# TODO: This function executes the following steps:
# 1. saves the context of the running thread
# 2. calls the scheduler to select the thread to be executed
# 	call scheduler
# 3. restores the context of the selected thread
# movq %rax, %rbx == %rbx = %rax
	# pushq %rax = armazena o valor de rax no topo da pilha
	# popq (reg ou mem) 
	# leaq 
scheduler_entry: # rsp aponta para a pilha da thread que está executando

	# preserving content of %rsp
	movq %rsp, scratch
	leaq current_running, %rsp
	
	# storing current_running flag address on %rsp
	leaq 136(%rsp), %rsp # rsp = current + ($136 * 1)
	
	# storing stack content
	pushq scratch
	
	# emplacing registers on the respective addresses
	pushfq
	pushq %r15
	pushq %r14
	pushq %r13
	pushq %r12
	pushq %r11
	pushq %r10
	pushq %r9
	pushq %r8
	pushq %rbp
	pushq %rdi
	pushq %rsi
	pushq %rdx
	pushq %rcx
	pushq %rbx
	pushq %rax

	movq scratch, %rsp
	# changing to the next thread
	call scheduler

	# loading context
	leaq current_running, %rsp
	
	popq %rax
	popq %rbx
	popq %rcx
	popq %rdx
	popq %rsi
	popq %rdi
	popq %rbp
	popq %r8
	popq %r9
	popq %r10
	popq %r11
	popq %r12
	popq %r13
	popq %r14
	popq %r15

	popfq

	popq %rsp

	ret
