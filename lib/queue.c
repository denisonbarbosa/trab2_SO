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

void enqueue_sort(queue_t *q, node_t *item, node_lte comp)
{
    node_t *front = item; // item turns front
    node_t *aux;
    if (is_empty(q))
    {
        q->back = q->front = item;
    }
    else
    {
        item->next = q->front;
        // continues if item > item->next and has next
        while (comp(item, item->next) == 0 && item->next != NULL)
        {
            front = q->front; // "restore" front
            aux = item->next;
            item->next = item->next->next;
            aux->next = item;
        }
        q->front = front;
    }
}
