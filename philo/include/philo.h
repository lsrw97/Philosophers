/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:47:58 by eelisaro          #+#    #+#             */
/*   Updated: 2023/12/07 16:30:00 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef enum t_mode
{
	THINK,
	THINKING,
	SLEEP,
	EAT,
	DEAD,
}	t_mode;

typedef struct t_status
{
	unsigned long long	time;
	struct t_philo		*table;
	pthread_mutex_t		deathmutex;
	pthread_mutex_t		mutex_time;
	pthread_mutex_t		mutex_msg;
	pthread_mutex_t		mutex_joined;
	pthread_mutex_t		mutex_meals;
	int					pcount;
	int					meals;
	int					lt;
	int					eattime;
	int					sleeptime;
	int					dead;
	int					joined;
}	t_status;

typedef struct t_philo
{
	struct t_philo		*next;
	struct t_philo		*prev;
	struct t_status		*status;
	pthread_mutex_t		mutex_lastmeal;
	pthread_mutex_t		mutex_fork;
	int					fork;
	int					meals;
	int					mode;
	int					index;
	unsigned long long	lastmeal;	
}	t_philo;

int					getphilofork(t_philo *philo);
unsigned long long	get_time(void);
int					getstatusdead(t_status *status);
unsigned long long	getstatustime(t_status *status);
void				setstatusdead(t_status *status);
void				togglephilofork(t_philo *philo);
int					getlm(t_philo *philo);
void				setlastmeal(t_philo *philo);
int					getmeals(t_philo *philo);
void				incrementmeals(t_philo *philo);
unsigned int		ft_atoi(const char *nptr);
int					checkforint(char *str);
int					checkargs(char **argv, int argc);
void				ft_sleep(unsigned long long wait, unsigned long long now);
void				print_msg(t_philo *philo, int index, char *msg);
t_status			*instatus(char **av, t_status *status, t_philo *ph, int i);
t_philo				*newnode(t_philo *prev, int i, t_status *status);
t_philo				*createtable(int size, t_status *status);
int					allfull(t_philo *table);
int					getfork(t_philo *philo, int i);
int					getforks(t_philo *philo);
void				takeforks(t_philo *philo);
void				*checker(void *arg);
int					jointhreads(pthread_t *threads, int size, t_philo *philo);
void				*routine(void *arg);
int					createthreads(t_philo *table, pthread_t *philos);
void				setjoined(t_philo *philo);
int					getjoined(t_philo *philo);
int					ft_strlen(char *str);
#endif
