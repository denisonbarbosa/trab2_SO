#include <queue.h>
#include <stdlib.h>
#include <stdio.h>

/*
  This   file    contains   a    function   definitions    for   queue
  manipulation. You  are free to  choose your own  implementation. You
  may need to define additional functions if you want to implement the
  extra-point functionality.
 */

void queue_init(queue_t *queue)
{
    queue = (queue_t *) malloc(sizeof(queue_t));
    queue->front = NULL;
    queue->back = NULL;
}

node_t *dequeue(queue_t *queue)
{
    node_t *node = NULL;
    if (is_empty(queue) == 0)
    {
        node = queue->front;
        queue->front = queue->front->next;
    }
    return node;
}

void enqueue(queue_t *queue, void *tcb)
{
    node_t *tmp = (node_t*)malloc(sizeof(node_t));
    tmp->next = NULL;
    tmp->content = tcb;
    if (is_empty(queue))
    {
        queue->front = queue->back = tmp;
    }
    else
    {
        queue->back->next = tmp;
        queue->back = tmp;
    }
}

int is_empty(queue_t *queue)
{
    if (queue->front == NULL)
        return 1;
    return 0;
}

node_t *peek(queue_t *queue)
{
    return queue->front;
}

void enqueue_sort(queue_t *q, void *item, node_lte comp)
{
    node_t *node_item = (node_t*)malloc(sizeof(node_t));
    node_item->content = item;
    // node_t *front = node_item; // item turns front
    node_t *aux;
    
    if (is_empty(q))
    {
        q->back = q->front = node_item;
    }
    else
    {
        //node_item->next = q->front;
        aux = q->front;
        if (comp(node_item, aux) == 1)
        {
            printf("Entrando no começo da fila\n");
            node_item->next = q->front;
            q->front = node_item;
        }
        else
        {
            printf("Começando a percorrer a fila\n");
            while (comp(node_item, aux->next) == 0)
            {
                printf("tid_aux: %d \ntid_next: %d\n", ((tcb_t*)aux->content)->tid, ((tcb_t*)aux->next->content)->tid);
                aux = aux->next;
                if (aux->next== NULL)
                    break;
            }
            node_item->next = aux->next;
            aux->next = node_item;
        }
        /*
        // continues if item > item->next and has next
        while (comp(node_item, node_item->next) == 0 && node_item->next != NULL)
        {
            
            
            front = q->front; // "restore" front
            aux = node_item->next;
            node_item->next = node_item->next->next;
            aux->next = node_item;
        }
        q->front = front;
        */
    }
}

void print_queue(queue_t *queue)
{
    printf("Queue Order = ");
    for (node_t* node = queue->front; node != NULL; node = node->next)
    {
        printf("%d ", ((tcb_t*)node->content)->tid);
    }
    printf("\n");
}
