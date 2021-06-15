#ifndef THREADU_H
#define THREADU_H

typedef enum
{
    FALSE,
    TRUE
} bool_t;

typedef struct thr
{
    void *tcb;
} thread_t;

/**
 * @brief Creates a new thread and inserts in the ready queue.
 * 
 * @param thread Thread pointer to receive the tcb
 * @param start_routine Initial routine to execute
 * @param arg Arguments of the start_routine
 * @return int 
 */
int thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg);

/**
 * @brief Yields the CPU to another thread 
 * 
 * @return int 
 */
int thread_yield();

/**
 * @brief Waits for a thread to finish 
 * 
 * @param thread Specified thread pointer
 * @param retval value to be checked
 * @return int 
 */
int thread_join(thread_t *thread, int *retval);

/**
 * @brief initializes the thread library and creates a thread for the main function.
 * 
 * @return 0 on sucess || -EINVAL if the library has already been initialized
 */
int thread_init();

/**
 * @brief Marks a thread as EXITED and terminates the thread 
 * 
 * @param status 
 */
void thread_exit(int status);

void set_fair_schedular(bool_t status);

#endif /* THREADU_H */
