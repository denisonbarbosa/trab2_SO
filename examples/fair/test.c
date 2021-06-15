#include <stdio.h>
#include <unistd.h>
#include <threadu.h>
#include <util.h>

void *f1(void *p)
{
	int i;
	int *one = (int *)p;
	u_int64_t time = get_timer();
	u_int64_t time_runnig = 0;

	for (i = 0; i < 3; i++)
	{
		printf("thread %d total running time: %lu\n", *one, time_runnig);
		printf("f1 will sleep! %d\n", *one);
		usleep(100 * (*one));
		time_runnig += get_timer() - time;
		printf("f1 will yield!\n\n");
		thread_yield();
		time = get_timer();
	}
	thread_exit(*one);
}

int main()
{
	thread_t thd[6];
	int params[6], rv[6], i;

	thread_init();
	set_fair_schedular(TRUE);
	printf("BEGIN: Time stamp: %ld\n", get_timer());
	for (i = 0; i < 6; i++)
	{
		params[i] = i;
		thread_create(&thd[i], f1, &params[i]);
	}

	for (i = 0; i < 6; i++)
	{
		thread_join(&thd[i], &rv[i]);
		printf("Thread %d finished with exit status %d\n\n", i, rv[i]);
	}
	printf("END: Time stamp: %ld\n", get_timer());
}