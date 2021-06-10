#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread.h>

queue_t ready_queue;
tcb_t *current_running; // sempre aponta para a thread que está rodando no momento

int tid_global = 0;

int thread_init()
{
    init_tcb(&current_running);

    queue_init(&ready_queue);

    return 0;
}

void init_tcb(tcb_t **tcb)
{
    *tcb = (tcb_t *)malloc(sizeof(tcb_t));
    (*tcb)->tid = tid_global++;
    (*tcb)->stack = (uint64_t*) malloc(STACK_SIZE);
    (*tcb)->stack = (*tcb)->stack + ((STACK_SIZE/sizeof(uint64_t))-1);
    (*tcb)->current_exec_time = 0;
    (*tcb)->retval = 0;
}

int thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg)
{
    init_tcb((tcb_t **)(&thread->tcb));
    
    // order: exit_handler -> start_routine -> rsp (return address)
    ((tcb_t *)thread->tcb)->regs[5] = arg;
    ((tcb_t *)thread->tcb)->regs[6] = ((tcb_t *)thread->tcb)->stack;
    
    *((tcb_t *)thread->tcb)->stack = (uint64_t*)exit_handler;
    ((tcb_t *)thread->tcb)->stack--;
    *((tcb_t *)thread->tcb)->stack = (uint64_t*)start_routine;
    
    ((tcb_t *)thread->tcb)->status = READY;

    enqueue(&ready_queue, thread->tcb);

    return 0;
}

// TODO: thread_yield()
int thread_yield()
{

    enqueue(&ready_queue, current_running);
    scheduler_entry();
}

// TODO: thread_join()
int thread_join(thread_t *thread, int *retval)
{
    while (((tcb_t *)thread->tcb)->status != EXITED)
        thread_yield();

    *retval = ((tcb_t *)thread->tcb)->retval;
    return 0;
}

// TODO: thread_exit()
void thread_exit(int status)
{
    current_running->status = EXITED;
    scheduler_entry();
}

// TODO: scheduler()
void scheduler()
{
    // printf("SCHEDULAR\n");
    current_running = ((tcb_t *)dequeue(&ready_queue)->content);
    //return;
}

// TODO: exit_handler()
void exit_handler()
{
    //convenções de chamada de função -> parâmetros (os 4 primeiros são passados em registradores)
    //o primeiro registrador para passar parâmetro é o rdi
    //quando start_routine for invocada, precisamos passar o argumento da thread_create para o rdi
}

tcb_t *getcurrt()
{
    return current_running;
}

void *getreadyqueue()
{
    return &ready_queue;
}