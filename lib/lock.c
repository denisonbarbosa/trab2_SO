#include <lock.h>
#include <threadu.h>
#include <stdlib.h>

enum
{
    SPIN = FALSE,
};

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
            enqueue_default(&l->thread_queue, getcurrt());
            block();
        }
        l->status = LOCKED;
    }
}

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

void block()
{
    getcurrt()->status = BLOCKED;
    scheduler_entry();
}

void unblock(lock_t *l)
{
    node_t *tmp = dequeue(&l->thread_queue);

    if (tmp != NULL)
    {
        ((tcb_t*)tmp->content)->status = READY;
        enqueue(getreadyqueue(), tmp->content);
    }
}
