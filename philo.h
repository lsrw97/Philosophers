#ifndef PUSH_H
# define PUSH_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

typedef enum s_mode
{
    THINK,
	THINKING,
    SLEEP,
	SLEEPING,
    EAT,
	EATING,
	DEAD,
}	s_mode;

typedef struct t_status
{
    int					running;
	int					dead;
	int					lifetime;
	int					sleeptime;
	int 				eattime;
	unsigned long long	inttime;
	pthread_mutex_t 	mutex;
	int					currtime;
	unsigned long long	time;
	struct t_philo		*table;
}	t_status;

typedef struct t_philo
{
    struct t_philo		*next;
    struct t_philo		*prev;
	struct t_status 	*status;
	int					timems;
	int					currtime;
	int					time;
	int					mutex;
	int					lastmeal;
    int     			hasfork;
    int     			mode;
    int     			lifetime;
    int     			meals;
    int     			index;
}	t_philo;

#endif
