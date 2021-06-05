#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <queue.h>
#include <thread.h>

node_t ready_queue;
tcb_t *current_running; // sempre aponta para a thread que está rodando no momento

int tid_global = 0;

/*
  TODO:  thread_init: initializes  the  thread library  and creates  a
  thread for  the main function. Returns  0 on success, or  -EINVAL if
  the library has already been initialized.
 */
int thread_init()
{
    tcb_t *main_tcb = malloc(sizeof(tcb_t));
    //criar uma ready queue

    current_running = main_tcb;

    return 0;
}

// TODO: creates a new thread and inserts in the ready queue.
int thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg)
{
    // criar um TCB e alocar região de memória para a pilha do TCB
    tcb_t *tcb = malloc(sizeof(tcb_t));

    tcb->stack = malloc(sizeof(stack_t));
    tcb->stack->top = NULL;
    tcb->stack->max_size = STACK_SIZE;
    tcb->stack->current_size = 0;

    tcb->regs = malloc(NUMBER_OF_REGISTERS * sizeof(uint64_t));

    tcb->current_exec_time = 0;

    thread->tcb = tcb;
    // e fazer com que este campo da estrutura TCP aponte para a pilha
    // Depois coloca no final da ready queue
    return 0;
}

// TODO: yields the CPU to another thread
int thread_yield()
{
    //liberar CPU, chama a função em assembly (scheduler_entry(troca de contexto))
    return 0;
}

// TODO: waits for a thread to finish
int thread_join(thread_t *thread, int *retval)
{
    //Pegar a thread que foi passada por parâmetro e verificar o status dela, se for EXITED, retorna
    //Se não for, tem que esperar a thread terminar, fazedo um yield da thread que chamou a thread join
    //desaloca memória
    return 0;
}

// TODO: marks a thread as EXITED and terminates the thread
void thread_exit(int status)
{
    // marcar a thread como terminada
}

// TODO: selects the next thread to execute
void scheduler()
{
    //seleciona a próxima thread que irá executar
    //(pega a primeira thread que está na fila e fazer que current_running aponte para essa thread)
}

// TODO: you must  make sure this function is called  if a thread does
// not call thread_exit
void exit_handler()
{
    //convenções de chamada de função -> parâmetros (os 4 primeiros são passados em registradores)
    //o primeiro registrador para passar parâmetro é o rdi
    //quando start_routine for invocada, precisamos passar o argumento da thread_create para o rdi
}
