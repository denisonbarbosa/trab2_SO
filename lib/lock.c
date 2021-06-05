#include <lock.h>
#include <threadu.h>

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
    }
}

// TODO: blocks the running thread
void block()
{
}

// TODO: unblocks  a thread that is waiting on a lock.
void unblock(lock_t *l)
{
}
