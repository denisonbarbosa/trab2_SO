#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <queue.h>
#include <thread.h>
#include <threadu.h>

queue_t *ready_queue;
tcb_t *current_running; // sempre aponta para a thread que está rodando no momento

int tid_global = 0;

int thread_init()
{
    if (ready_queue != NULL)
        return -EINVAL;

    tcb_t *main_tcb = (tcb_t*)malloc(sizeof(tcb_t));
    init_tcb(main_tcb);

    queue_init(ready_queue);

    current_running = main_tcb;

    return 0;
}

// TODO: init_tcb()
void init_tcb(tcb_t *tcb)
{
    tcb = (tcb_t*)malloc(sizeof(tcb_t));
    tcb->stack = malloc(STACK_SIZE);
    tcb->current_exec_time = 0;
}

// TODO: thread_create()
int thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg)
{
    init_tcb(((tcb_t*)thread->tcb));

    ((tcb_t*)thread->tcb)->stack = start_routine(arg);
    
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    new_node->content = thread->tcb;

    enqueue(&ready_queue, thread->tcb);

    return 0;
}

// TODO: thread_yield()
int thread_yield()
{
    enqueue(ready_queue, current_running);
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
    // marcar a thread como terminada
}

// TODO: scheduler()
/**
 * @brief Selects the next thread to execute 
 * 
 */
void scheduler()
{
    current_running = dequeue(ready_queue);
}

// TODO: exit_handler()
/**
 * @brief This function must be called if a thread does not call thread_exit()
 * 
 */
void exit_handler()
{
    //convenções de chamada de função -> parâmetros (os 4 primeiros são passados em registradores)
    //o primeiro registrador para passar parâmetro é o rdi
    //quando start_routine for invocada, precisamos passar o argumento da thread_create para o rdi
}

tcb_t* getcurrt()
{
    return current_running;
}

void* getreadyqueue()
{
    return &ready_queue;
}