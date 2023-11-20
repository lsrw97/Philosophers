#ifndef PUSH_H
# define PUSH_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

typedef enum	s_mode
{
	THINK,
	THINKING,
	SLEEP,
	SLEEPING,
	EAT,
	EATING,
	DEAD,
}	s_mode;

typedef struct	t_status
{
	unsigned long long	time;
	unsigned long long	currenttime;
    struct t_philo		*table;
	pthread_mutex_t		mutex;
	int					meals;
	int					lifetime;
	int					eattime;
	int					sleeptime;
}	t_status;

typedef struct t_philo
{
	struct t_philo		*next;
	struct t_philo		*prev;
	struct t_status		*status;
	pthread_mutex_t		mutex_fork;
	int					meals;
	int					hasfork;
	int					mode;
	int					index;
	int					lastmeal;
}	t_philo;

#endif
