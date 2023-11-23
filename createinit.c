#include "philo2.h"

t_status	*init_status(char **argv, t_status *status, t_philo *table, int argc)
{
	status->pcount = ft_atoi(argv[1]);
	status->lifetime = ft_atoi(argv[2]);
	status->eattime = ft_atoi(argv[3]);
	status->sleeptime = ft_atoi(argv[4]);
	if (argc == 6)
		status->meals = ft_atoi(argv[5]);
	else
		status->meals = INT_MAX;
	status->time = get_time();
	status->table = table;
	status->dead = 0;
	status->currenttime = status->time;
	status->forks = malloc(sizeof(int) * ft_atoi(argv[1]));
	status->forks = createforks(status->forks, ft_atoi(argv[1]));
	pthread_mutex_init(&status->deathmutex, NULL);
	pthread_mutex_init(&status->mutex_time, NULL);
	pthread_mutex_init(&status->mutex_fork, NULL);
	pthread_mutex_init(&status->mutex_currenttime, NULL);
	pthread_mutex_init(&status->mutex_msg, NULL);
	return status;
}

t_philo	*ft_newnode(int life, t_philo *prev, int index, t_status *status)
{
	t_philo	*philo;
	struct timeval	current_time;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->status = status;
	if (!(index % 2))
		philo->mode = EAT;
	else
		philo->mode = THINK;
	pthread_mutex_init(&philo->mutex_fork, NULL);
	pthread_mutex_init(&philo->mutex_printf, NULL);
	pthread_mutex_init(&philo->mutex_mode, NULL);
	pthread_mutex_init(&philo->mutex_philo, NULL);
	pthread_mutex_init(&philo->mutex_index, NULL);
	philo->hasfork = 0;
	philo->meals = 0;
	philo->index = index;
	philo->next = NULL;
	philo->prev = prev;
	philo->lastmeal = 0;
	philo->dead = 0;
	return (philo);
}

t_philo	*createtable(int size, char **argv, t_status *status)
{
	t_philo	*table;
	t_philo	*tmp;
	int		i;

	i = 1;
	table = ft_newnode(ft_atoi(argv[1]), NULL, 1, status);
	tmp = table;
	while (++i <= size)
	{
		tmp->next = ft_newnode(ft_atoi(argv[1]), tmp, i, status);
		tmp = tmp->next;
	}
	tmp->next = table;
	table->prev = tmp;
	return (table);
}

int	createthreads(t_philo *table, pthread_t *philos)
{
	t_philo	*tmp;
	int		i;

	i = -1;
	tmp = table;
	while (tmp->next->index != table->index)
	{
		pthread_create(&philos[++i], NULL, &routine, tmp);
		tmp = tmp->next;
	}
	pthread_create(&philos[++i], NULL, &routine, tmp);
	return (1);
}

int	*createforks(int *forks, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		forks[i] = 1;
	return (forks);
}