#include <errno.h>
#include <stdlib.h>
#include <thread.h>
#include <util.h>
#include <stdio.h>

queue_t ready_queue;
tcb_t *current_running; // sempre aponta para a thread que está rodando no momento
uint64_t entry_time = 0;

int tid_global = 0;

int thread_init()
{
    init_tcb(&current_running);

    queue_init(&ready_queue);

    entry_time = get_timer();

    return 0;
}

void init_tcb(tcb_t **tcb)
{
    *tcb = (tcb_t *)malloc(sizeof(tcb_t));
    (*tcb)->tid = tid_global++;
    (*tcb)->stack = (uint64_t *)malloc(STACK_SIZE);
    (*tcb)->stack = (*tcb)->stack + ((STACK_SIZE / sizeof(uint64_t)) - 1);
    (*tcb)->current_exec_time = 0;
    (*tcb)->retval = 0;
}

int thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg)
{
    init_tcb((tcb_t **)(&thread->tcb));

    // Stores the arg on the %rdi position of the regs[]
    ((tcb_t *)thread->tcb)->regs[5] = (uint64_t)arg;

    // Stores the pointer of the stack base in regs[6](%rbp)
    ((tcb_t *)thread->tcb)->regs[6] = (uint64_t)((tcb_t *)thread->tcb)->stack;

    // Stacking the routines of the thread in the correct order
    *((tcb_t *)thread->tcb)->stack = (uint64_t)exit_handler;
    ((tcb_t *)thread->tcb)->stack--;
    *((tcb_t *)thread->tcb)->stack = (uint64_t)start_routine;

    ((tcb_t *)thread->tcb)->status = READY;

    enqueue(&ready_queue, thread->tcb);
    
    return 0;
}

int thread_yield()
{
    current_running->current_exec_time += get_timer() - entry_time;
    printf("thread %u \ncurrent_exec_time: %u\nentry_time: %u\n\n",
        current_running->tid, current_running->current_exec_time, entry_time);
    
    enqueue(&ready_queue, current_running);
    
    scheduler_entry();
}

int thread_join(thread_t *thread, int *retval)
{
    while (((tcb_t *)thread->tcb)->status != EXITED)
    {   
        sleep(1);
        thread_yield();
    }
    *retval = ((tcb_t *)thread->tcb)->retval;
    free_thread(thread);
    return 0;
}

void thread_exit(int status)
{
    current_running->retval = status;
    current_running->status = EXITED;
    scheduler_entry();
}

void scheduler()
{
    current_running = ((tcb_t *)dequeue(&ready_queue)->content);
    entry_time = get_timer();
}

// TODO: exit_handler()
void exit_handler()
{
    current_running->status = EXITED;
    scheduler_entry();
    //convenções de chamada de função -> parâmetros (os 4 primeiros são passados em registradores)
    //o primeiro registrador para passar parâmetro é o rdi
    //quando start_routine for invocada, precisamos passar o argumento da thread_create para o rdi
}

void free_thread(thread_t *t)
{
    free(((tcb_t *)t->tcb)->stack);
    free(t->tcb);
    //free(t);
}

tcb_t *getcurrt()
{
    return current_running;
}

void *getreadyqueue()
{
    return &ready_queue;
}