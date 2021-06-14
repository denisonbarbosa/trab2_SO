#include <queue.h>
#include <stdlib.h>
#include <stdio.h>

/*
  This   file    contains   a    function   definitions    for   queue
  manipulation. You  are free to  choose your own  implementation. You
  may need to define additional functions if you want to implement the
  extra-point functionality.
 */

/**
 * @brief Set to TRUE to enable fair scheduling | FALSE to disable
 * 
 */
bool_t sorted_queuing = FALSE;

void queue_init(queue_t *queue)
{
    queue = (queue_t *)malloc(sizeof(queue_t));
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

void enqueue(queue_t *queue, void *tcb)
{
    if (sorted_queuing)
        enqueue_sort(queue, tcb, comp_node_time);
    else
        enqueue_default(queue, tcb);
}

void enqueue_default(queue_t *queue, void *tcb)
{
    node_t *tmp = (node_t *)malloc(sizeof(node_t));
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

void enqueue_sort(queue_t *q, void *item, node_lte comp)
{
    node_t *node_item = (node_t *)malloc(sizeof(node_t));
    node_item->content = item;
    node_t *aux;

    if (is_empty(q))
    {
        q->back = q->front = node_item;
    }
    else
    {
        aux = q->front;
        if (comp(node_item, aux) == 1)
        {
            node_item->next = q->front;
            q->front = node_item;
        }
        else
        {
            while (comp(node_item, aux->next) == 0)
            {
                aux = aux->next;
                if (aux->next == NULL)
                {
                    q->back = node_item;
                    break;
                }
            }
            node_item->next = aux->next;
            aux->next = node_item;
        }
    }
}

void print_queue(queue_t *queue)
{
    printf("Queue Order = ");
    for (node_t *node = queue->front; node != NULL; node = node->next)
    {
        printf("%d ", ((tcb_t *)node->content)->tid);
    }
    printf("\n");
}

int comp_node_time(node_t *a, node_t *b)
{
    if (((tcb_t *)a->content)->current_exec_time <= ((tcb_t *)b->content)->current_exec_time)
        return 1;

    return 0;
}