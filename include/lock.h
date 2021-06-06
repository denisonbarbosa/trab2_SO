#ifndef LOCK_H
#define LOCK_H

#include <queue.h>
typedef struct
{
    enum
    {
        UNLOCKED,
        LOCKED,
    } status;
    queue_t thread_queue;
} lock_t;

/**
 * @brief Initalizes a lock
 * 
 * @param l Lock to be initialized
 */
void lock_init(lock_t *);

/**
 * @brief Acquire a lock if available, blocks the thread otherwise
 * 
 * @param l Lock to be acquied
 */
void lock_acquire(lock_t *);

/**
 * @brief Releases a lock and unlock a thread from the lock's blocking list 
 * 
 * @param l Lock to be released
 */
void lock_release(lock_t *);

/**
 * @brief Blocks the current thread from joining the ready queue
 * 
 */
void block();

/**
 * @brief Removes a thread from the lock wait queue and add it to the ready queue
 * 
 */
void unblock(lock_t *);

#endif /* LOCK_H */
