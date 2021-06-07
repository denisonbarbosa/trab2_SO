#include <lock.h>
#include <threadu.h>
#include <stdlib.h>

enum
{
    SPIN = TRUE,
};

// TODO: lock_init()
void lock_init(lock_t *l)
{
    if (SPIN)
    {
        l->status = UNLOCKED;
    }
    else
    {
        l = (lock_t*)malloc(sizeof(lock_t));
        l->status = UNLOCKED;
        queue_init(&l->thread_queue);
    }
}

// TODO: lock_acquire()
void lock_acquire(lock_t *l)
{
    if (SPIN)
    {
        while (LOCKED == l->status)
            thread_yield();
        l->status = LOCKED;
    }
    else
    {
        while (l->status == LOCKED)
        {
            enqueue(&l->thread_queue, getcurrt());
            block();
        }
        l->status = LOCKED;
    }
}

// TODO: lock_release()
void lock_release(lock_t *l)
{
    if (SPIN)
    {
        l->status = UNLOCKED;
    }
    else
    {
        l->status = UNLOCKED;
        unblock(l);
    }
}

// TODO: blocks the running thread
void block()
{
    getcurrt()->status = BLOCKED;
    scheduler_entry();
}

// TODO: unblocks  a thread that is waiting on a lock.
void unblock(lock_t *l)
{
    node_t *tmp = dequeue(&l->thread_queue);

    if (tmp != NULL)
    {
        tmp->content->status = READY;
        enqueue(getreadyqueue(), tmp->content);
    }
}
