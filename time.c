#include "philo2.h"

unsigned long long	get_time()
{
	unsigned long long 			time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_usec / 1000 + current_time.tv_sec * 1000;
	return (time);
}

void	ft_sleep(int waittime, unsigned long long timenow)
{
	while(1)
	{
		if (get_time() - timenow >= waittime)
			return ;
		usleep(20);
	}
}
