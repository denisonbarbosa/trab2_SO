#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <thread.h>

typedef struct node
{
    void *content;
    struct node *next;
} node_t;

typedef struct queue
{
    node_t *front;
    node_t *back;
} queue_t;


/**
 * @brief Set the fair scheduling variable
 * 
 * @param status Set to TRUE to enable fair scheduling | FALSE to disable
 */
void set_sorted_queuing(bool_t status, queue_t *q);

/**
 * @brief Initializes a queue pointer
 * 
 * @param queue Pointer to be initialized
 */
void queue_init(queue_t *queue);

/**
 * @brief Remove and return the item at the front of the queue
 * 
 * @param queue 
 * @return node_t* that was removed || NULL if queue is empty
 */
node_t *dequeue(queue_t *queue);

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
 * @brief Enqueue the tcb using the correct method
 * 
 * @param queue 
 * @param item 
 */
void enqueue(queue_t *queue, void *tcb);

/**
 * @brief Standard queuing method: Adds at the end of the queue
 * 
 * @param queue 
 * @param tcb 
 */
void enqueue_default(queue_t *queue, void *tcb);

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
void enqueue_sorted(queue_t *q, void *item, node_lte comp);

/**
 * @brief Compares the current_exec_time of the given nodes
 * 
 * @param a 
 * @param b 
 * @return int 1 if a is less-than-or-equal-to b || 0 otherwise.
 */
int comp_node_time(node_t *a, node_t *b);

void print_queue(queue_t *q);

#endif /* QUEUE_H */
