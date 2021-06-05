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
	uint64_t *regs; //espaço para registradores da CPU: rax, rbx, rcx, rdx, rbp, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15, rsp (ponteiro para pilha)
	uint64_t rflags;
	stack_t *stack;
	int tid;
	int exec_time_left;
} tcb_t;

typedef struct stack {
	stack_element_t *top;
    int max_size;
	int current_size;
} stack_t;

typedef struct stack_element {
	void *command;
	stack_element_t *next;
} stack_element_t;

#endif /* THREAD_H */
