// memset,
// printf,
// malloc,
// free,
// write,
// usleep,
// gettimeofday,
// pthread_create,
// pthread_detach, 
// pthread_join, 
// pthread_mutex_init,
// pthread_mutex_destroy, 
// pthread_mutex_lock,
// pthread_mutex_unlock;

#include <sys/time.h>
#include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

int	get_time()
{
	int 			time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_usec / 1000 + current_time.tv_sec * 1000;
	return time;
}

int	ft_sleep(int waittime, int timenow)
{
	while(1)
	{
		if (get_time() - timenow >= waittime)
			return (1);
	}
}

int main() {
	int now = get_time();
  
  //  printf("seconds : %ld\nmicro seconds : %ld",
  //   current_time.tv_sec, current_time.tv_usec);
  ft_sleep(400, now);
  printf("%d\n", get_time() - now);

  return 0;
}