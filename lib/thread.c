#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread.h>

queue_t ready_queue;
tcb_t *current_running; // sempre aponta para a thread que está rodando no momento

int tid_global = 0;

int thread_init()
{
    if (current_running != NULL)
        return -EINVAL;

    tcb_t *main_tcb = (tcb_t *)malloc(sizeof(tcb_t));
    init_tcb(&main_tcb);

    queue_init(&ready_queue);

    current_running = main_tcb;
    return 0;
}

void init_tcb(tcb_t **tcb)
{
    *tcb = (tcb_t *)malloc(sizeof(tcb_t));
    (*tcb)->tid = tid_global++;
    (*tcb)->stack = malloc(STACK_SIZE);
    (*tcb)->current_exec_time = 0;
}

int thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg)
{
    init_tcb((tcb_t **)(&thread->tcb));

    ((tcb_t *)thread->tcb)->stack = start_routine;
    ((tcb_t *)thread->tcb)->regs[5] = *(uint64_t *)arg;
    ((tcb_t *)thread->tcb)->regs[7] = (uint64_t) &((tcb_t *)thread->tcb)->stack;

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->content = thread->tcb;
    
    enqueue(&ready_queue, thread->tcb);

    return 0;
}

// TODO: thread_yield()
int thread_yield()
{
    enqueue(&ready_queue, current_running);
    //printf("first thread in queue id: %d\n", ((tcb_t*)ready_queue.front->content)->tid);
    //pega a primeira thread que está na fila e faz current running apontar para esta thread
    //chama o escalonador para pegar a thread que está no início da fila de thread prontas e coloca para executar
    //escalonador -> pega a fila de thread prontas(ready queue)
    scheduler_entry();
    //liberar CPU, chama a função em assembly (scheduler_entry(troca de contexto))
    return 0;
}

// TODO: thread_join()
int thread_join(thread_t *thread, int *retval)
{
    while (((tcb_t *)thread->tcb)->status != EXITED)
        thread_yield();

    *retval = ((tcb_t *)thread->tcb)->retval;
    //Pegar a thread que foi passada por parâmetro e verificar o status dela, se for EXITED, retorna
    //Se não for, tem que esperar a thread terminar, fazedo um yield da thread que chamou a thread join
    //desaloca memória
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
    current_running = ((tcb_t *)dequeue(&ready_queue)->content);
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