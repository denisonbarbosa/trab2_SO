	.section .data
scratch: .quad	0

	.text
	.globl	scheduler_entry
	.type scheduler_entry, %function
	
scheduler_entry:
	
	# pointer values: 
	# regs[0..14] = current_running .. current_running + 112
	# rflags      = current_running + 120
	# stack       = current_running + 128

	# preserving content of %rsp || It has the return address to go to after the scheduler_entry call
	movq %rsp, scratch
	
	# storing current_running flag address on %rsp
	movq current_running, %rsp
	leaq 136(%rsp), %rsp

	pushq scratch
	
	# saving context
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

	# restoring the original content of %rsp
	movq scratch, %rsp

	# changing to the next thread
	call scheduler
	
	# storing current_running address on %rsp
	movq current_running, %rsp
	
	# loading context
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
	# %rsp -> stack
	
	ret
