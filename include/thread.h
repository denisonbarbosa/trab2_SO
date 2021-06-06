#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>
#include <threadu.h>

#define NUMBER_OF_REGISTERS 15
#define STACK_SIZE 2048

void scheduler_entry();
void exit_handler();

typedef enum
{
    FIRST_TIME,
    READY,
    BLOCKED,
    EXITED
} status_t;

typedef struct tcb
{
    status_t status;
    uint64_t *regs;
    uint64_t rflags;
    stack_t *stack;
    int tid;
    int current_exec_time;
    int retval;
} tcb_t;

typedef struct stack
{
    stack_element_t *top;
    int max_size;
    int current_size;
} stack_t;

typedef struct stack_element
{
    void *command;
    stack_element_t *next;
} stack_element_t;

/**
 * @brief Initializes the tcb and allocates necessary memory
 * 
 * @param tcb Pointer to a tcb_t
 */
void init_tcb(tcb_t *tcb);

/**
 * @brief Removes and returns the top of the stack
 * 
 * @param stack 
 * @return stack_element_t* 
 */
stack_element_t* pop_stack(stack_t *stack);

/**
 * @brief Adds the specified element to the top of the stack
 * 
 * @param stack 
 * @param element 
 */
void push_stack(stack_t *stack, stack_element_t *element);

/**
 * @brief Returns the pointer to the current running thread
 * 
 * @return tcb_t* 
 */
tcb_t* getcurrt();

/**
 * @brief Returns the pointer to the ready queue
 * 
 * @return queue_t*
 */
queue_t* getreadyqueue();
#endif /* THREAD_H */
