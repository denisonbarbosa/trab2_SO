#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>
#include <threadu.h>
#include <queue.h>

#define NUMBER_OF_REGISTERS 15
#define STACK_SIZE 2048

typedef enum
{
    FIRST_TIME,
    READY,
    BLOCKED,
    EXITED
} status_t;

typedef struct tcb
{
    uint64_t regs[15];
    uint64_t rflags;
    uint64_t *stack;
    int tid;
    uint64_t current_exec_time;
    int retval;
    status_t status;
    uint64_t *stack_address;
} tcb_t;

/**
 * @brief Initializes the tcb and allocates necessary memory
 * 
 * @param tcb Pointer to a tcb_t
 */
void init_tcb(tcb_t **tcb);

/**
 * @brief Allocates memory for the tcb->stack
 * 
 * @param stack 
 */
void stack_allocate(void **stack);

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
void* getreadyqueue();

/**
 * @brief Selects the next thread to execute 
 * 
 */
extern void scheduler_entry();

/**
 * @brief Makes current_running point to the next thread of the queue
 * 
 */
void scheduler();

/**
 * @brief This function must be called if a thread does not call thread_exit()
 * 
 */
void exit_handler();

/**
 * @brief Frees the memory allocated for the thread t
 * 
 * @param t 
 */
void free_thread(thread_t* t);

#endif /* THREAD_H */
