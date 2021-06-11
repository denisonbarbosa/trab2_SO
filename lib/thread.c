#include <errno.h>
#include <stdlib.h>
#include <thread.h>
#include <util.h>

/**
 * @brief Compares the current exec time of given nodes
 * 
 * @param a 
 * @param b 
 * @return 1 if a <= b || 0 if b > a
 */
int comp_node_time(node_t *a, node_t *b)
{   
    if (((tcb_t*)a->content)->current_exec_time 
        <= ((tcb_t*)b->content)->current_exec_time)
        return 1;
    
    return 0;
}

queue_t ready_queue;
tcb_t *current_running; // sempre aponta para a thread que está rodando no momento
bool_t fair_schedular = TRUE;
uint64_t entry_time = 0;

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
    ((tcb_t *)thread->tcb)->regs[5] = (uint64_t)arg;
    ((tcb_t *)thread->tcb)->regs[6] = (uint64_t)((tcb_t *)thread->tcb)->stack;
    
    *((tcb_t *)thread->tcb)->stack = (uint64_t)exit_handler;
    ((tcb_t *)thread->tcb)->stack--;
    *((tcb_t *)thread->tcb)->stack = (uint64_t)start_routine;
    
    ((tcb_t *)thread->tcb)->status = READY;

    if (fair_schedular)
        enqueue_sort(&ready_queue, thread->tcb, comp_node_time);
    else
        enqueue(&ready_queue, thread->tcb);

    return 0;
}

// TODO: thread_yield()
int thread_yield()
{
    current_running->current_exec_time += get_timer() - entry_time;
    if (fair_schedular)
        enqueue_sort(&ready_queue, current_running, comp_node_time);
    else
        enqueue(&ready_queue, current_running);

    scheduler_entry();
    entry_time = get_timer();
}

// TODO: thread_join()
int thread_join(thread_t *thread, int *retval)
{
    while (((tcb_t *)thread->tcb)->status != EXITED)
        thread_yield();

    *retval = ((tcb_t *)thread->tcb)->retval;
    free_thread(thread);
    return 0;
}

// TODO: thread_exit()
void thread_exit(int status)
{
    current_running->retval = status;
    current_running->status = EXITED;
    scheduler_entry();
}

// TODO: scheduler()
void scheduler()
{
    current_running = ((tcb_t *)dequeue(&ready_queue)->content);
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

void set_fair_schedular(bool_t fair)
{
    /*queue_t *new_queue;
    if (!fair_schedular  && fair)
    {
        queue_init(new_queue);
        while (!is_empty(&ready_queue))
            enqueue_sort(new_queue, dequeue(&ready_queue), comp_node_time);
        ready_queue = *new_queue;
    }*/
    fair_schedular = fair;
}

void free_thread(thread_t* t)
{
    free(((tcb_t*)t->tcb)->stack);
    free(t->tcb);
    free(t);
}

tcb_t *getcurrt()
{
    return current_running;
}

void *getreadyqueue()
{
    return &ready_queue;
}