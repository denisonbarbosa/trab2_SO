#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>
#include <threadu.h>

#define NUMBER_OF_REGISTERS	15
#define STACK_SIZE		2048

void scheduler_entry();
void exit_handler();

typedef enum {
	      FIRST_TIME,
	      READY,
	      BLOCKED,
	      EXITED
} status_t;

typedef struct tcb {
	// TODO: define the fields for you TCB
	//precisa ter espaço para guardar um thread quando ela for retirada da CPU
	uint64_t regs[NUMBER_OF_REGISTERS]; //espaço para registradores da CPU: rax, rbx, rcx, rdx, rbp, rsi
										// rdi, r8, r9, r10, r11, r12, r13, r14, r15, rsp (ponteiro para pilha)
	uint64_t rflags; //registrador de flags pushfq e popfq
	// PRECISA ter uma pilha exclusiva para a thread STACK_SIZE 2048 	
	// tid -> identificador da thread
	//movq %rax, %rbx = %rbx = %rax
	//pushq %rax = armazena o valor de rax no topo da pilha
	//popq (reg ou mem) 
	//leaq 
	
} tcb_t;

#endif /* THREAD_H */
