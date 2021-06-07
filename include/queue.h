#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <thread.h>
#include <thread.h>

typedef struct node
{
    tcb_t *content;
    node_t *next;
} node_t;

typedef struct queue{
   node_t *front;
   node_t *back;
} queue_t;

/**
 * @brief Initializes a queue pointer
 * 
 * @param queue Pointer to be initialized
 */
void queue_init(queue_t * queue);

/**
 * @brief Remove and return the item at the front of the queue
 * 
 * @param queue 
 * @return node_t* that was removed || NULL if queue is empty
 */
node_t *dequeue(queue_t * queue);

/**
 * @brief Add item to the back of the queue
 * 
 * @param queue 
 * @param item 
 */
void enqueue(queue_t * queue, tcb_t* tcb);

/**
 * @brief Determine if the queue is empty.
 * 
 * @param queue 
 * @return int: 1 if is empty || 0 otherwise.
 */
int is_empty(queue_t *queue);

/**
 * @brief Returns the first item in the queue
 * 
 * @param queue 
 * @return node_t* of the item || NULL if queue is empty
 */
node_t *peek(queue_t *queue);

/**
 * @brief A comparison function
 * 
 * @return int 1 if a is less-than-or-equal-to b || 0 otherwise.
 */
typedef int (*node_lte)(node_t *a, node_t *b);

/* Insert this item /elt/ into the queue /q/
 * in ascending order with the less-than-or-equal-to
 * inequality /comp/.
 * If /q/ was sorted (w.r.t. /comp/) before the
 * call, then /q/ is sorted after the call.
 * This is the simple linear-time algorithm.
 */

/**
 * @brief Insert item into the queue with less-or-equal-to inequality
 * 
 * @param q Queue to receive the item
 * @param item Item to be inserted
 * @param comp Comparison function
 */
void enqueue_sort(queue_t *q, node_t *item, node_lte comp);

#endif /* QUEUE_H */
