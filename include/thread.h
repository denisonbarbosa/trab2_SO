#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>
#include <threadu.h>

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
    status_t status;
    uint64_t regs[NUMBER_OF_REGISTERS];
    uint64_t rflags;
    void *stack;
    int tid;
    int current_exec_time;
    int retval;
} tcb_t;

/**
 * @brief Initializes the tcb and allocates necessary memory
 * 
 * @param tcb Pointer to a tcb_t
 */
void init_tcb(tcb_t *tcb);

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

void scheduler_entry();
void exit_handler();

#endif /* THREAD_H */
