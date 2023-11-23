#ifndef PUSH_H
# define PUSH_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>

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
	pthread_mutex_t		deathmutex;
	pthread_mutex_t		mutex_time;
	pthread_mutex_t		mutex_fork;
	pthread_mutex_t		mutex_currenttime;
	pthread_mutex_t		mutex_msg;
	int					pcount;
	int					meals;
	int					lifetime;
	int					eattime;
	int					sleeptime;
	int					dead;	// mutex
	int					*forks;
}	t_status;

typedef struct t_philo
{
	struct t_philo		*next;
	struct t_philo		*prev;
	struct t_status		*status;
	pthread_mutex_t		mutex_fork;
	pthread_mutex_t		mutex_printf;
	pthread_mutex_t		mutex_mode;
	pthread_mutex_t		mutex_philo;
	pthread_mutex_t		mutex_lastmeal;
	pthread_mutex_t		mutex_meals;
	pthread_mutex_t		mutex_index;
	pthread_mutex_t		mutex_msg;
	unsigned long long	currenttime;
	int					meals;
	int					hasfork;	//mutex
	int					mode;		// mutex
	int					index;
	unsigned long long	lastmeal;	
	int					dead;		// we can use mode to identify death
}	t_philo;

unsigned long long	get_time();
int					getstatusdead(t_status *status);
unsigned long long 	getstatustime(t_status *status);
unsigned long long	getstatuscurrenttime(t_status *status);
void				setstatuscurrenttime(t_status *status);
void				setstatusdead(t_status *status);
t_philo				*getphilo(t_philo *philo);
int					getindex(t_philo *philo);
void				togglefork(t_philo *philo, int i);
int					getlastmeal(t_philo *philo);
void				setlastmeal(t_philo *philo);
int					getmeals(t_philo *philo);
void				incrementmeals(t_philo *philo);
int					ft_atoi(const char *nptr);
int					checkforint(char *str);
int					checkargs(char **argv, int argc);
unsigned long long	get_time();
void				ft_sleep(int waittime, unsigned long long timenow);
int 				getms(unsigned long long time);
int					*createforks(int *forks, int size);
void				print_msg(t_philo *philo, int index, char *msg);
void				print_mut(t_philo *philo, char *msg);
t_status			*init_status(char **argv, t_status *status, t_philo *table, int argc);
t_philo				*ft_newnode(int life, t_philo *prev, int index, t_status *status);
t_philo				*createtable(int size, char **argv, t_status *status);
int					allfull(t_philo *table);
int					getfork(t_philo *philo, int i);
int					getforks(t_philo *philo);
int					takeforks(t_philo *philo);
void    			*checker(void *arg);
int					jointhreads(pthread_t   *threads, int size);
void				*routine(void *arg);
int					createthreads(t_philo *table, pthread_t *philos);


#endif
