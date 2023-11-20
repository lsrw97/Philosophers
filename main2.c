#include "philo2.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	unsigned int	num;

	i = 0;
	num = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)(num));
}

int	checkforint(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

int	checkargs(char **argv, int argc)
{
	int	i;

	i = 0;
	if (argc < 4 || argc > 6)
	{
		write(1, "you need 3 or 4 arguments!", 26);
		return (0);
	}
	while (argv[++i])
	{
		if (!checkforint(argv[i]))
			return (0);
	}
	return (1);
}

unsigned long long	get_time()
{
	unsigned long long 			time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_usec / 1000 + current_time.tv_sec * 1000;
	return (time);
}

int	ft_sleep(int waittime, unsigned long long timenow)
{
	while(1)
	{
		if (get_time() - timenow >= waittime)
			return (1);
	}
}

int getms(unsigned long long time)
{
    return (get_time() - time);
}

t_status	*init_status(char **argv, t_status *status, t_philo *table)
{
	status->lifetime = ft_atoi(argv[2]);
	status->eattime = ft_atoi(argv[3]);
	status->sleeptime = ft_atoi(argv[4]);
	status->meals = ft_atoi(argv[5]);
	status->time = get_time();
	status->table = table;
	status->dead = 0;
	status->currenttime = status->time;
	pthread_mutex_init(&status->deathmutex, NULL);
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
	philo->hasfork = 0;
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

int	allfull(t_philo *table)
{
	t_philo *tmp;

	tmp = table;
	if (tmp->meals != tmp->status->meals)
		return (0);
	tmp = tmp->next;
	while (tmp != table)
	{
		if (tmp->meals != tmp->status->meals)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	takeforks(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->mutex_fork);
		// pthread_mutex_lock(&philo->next->mutex_fork);
		if (!philo->hasfork && !philo->next->hasfork)
		{
			printf("%lld %d has taken a fork\n", philo->status->currenttime, philo->index);
			printf("%lld %d has taken a fork\n", philo->status->currenttime, philo->index);
			philo->hasfork = 1;
			philo->next->hasfork = 1;
			pthread_mutex_unlock(&philo->mutex_fork);
			// pthread_mutex_unlock(&philo->next->mutex_fork);
			break ;
		}
		pthread_mutex_unlock(&philo->mutex_fork);
		// pthread_mutex_unlock(&philo->next->mutex_fork);
	}
}


void    *checker(void *arg)
{
	t_philo *table;

	table = (t_philo *)arg;
	// pthread_mutex_lock(&table->status->mutex);
	while (getms(table->status->time) - table->lastmeal < table->status->lifetime)
	{
		table = table->next;
		table->status->currenttime = getms(table->status->time);
	}
	printf("%lld %d died\n", table->status->currenttime, table->index);
	// pthread_mutex_lock(&table->status->mutex);
	// pthread_mutex_lock(&table->mutex_printf);
	table->mode = DEAD;
	table->status->dead = 1;
	// pthread_mutex_unlock(&table->mutex_printf);
	return NULL;
}

int	jointhreads(pthread_t   *threads, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		// printf("%d joined\n", i);
		pthread_join(threads[i], NULL);
	}
	return (1);
}

int	checkforrunning(t_philo *table)
{
	t_philo *tmp;
	
	tmp = table;
	pthread_mutex_lock(&table->status->deathmutex);
	if (!tmp->dead)
		return (0);
	pthread_mutex_unlock(&table->status->deathmutex);
	tmp = tmp->next;
	while (tmp != table)
	{
		pthread_mutex_lock(&table->status->deathmutex);
		if (!tmp->dead)
			return (0);
		pthread_mutex_unlock(&table->status->deathmutex);
		tmp = tmp->next;
	}

	return (1);	
}

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	while (1)
	{
		// if (philo->status->dead)
		// 	{
		// 		// printf("%d died\n", philo->index);
		// 		philo->dead = 1;
		// 		return (0);
		// 	}
		// pthread_mutex_lock(&philo->status->mutex);
		// while (philo->next->mode == EAT || philo->next->hasfork || philo->index % 2 &&
		//  philo->prev->mode == EAT && philo->next->index % 2)
		// {
		// 	if (philo->status->dead)
		// 	{
		// 		philo->dead = 1;
		// 		return (0);
		// 	}
		// 	if (philo->mode != THINKING)
		// 	{
		// 		philo->mode = THINKING;
		// 		printf("%lld %d is thinking\n", philo->status->currenttime, philo->index);
		// 	}
		// }
		// pthread_mutex_lock(&philo->status->mutex);		
		// if (!philo->hasfork && !philo->next->hasfork && philo->meals != philo->status->meals)
		// {
		// 	takeforks(philo);
		// 	philo->mode = EAT;
		// 	printf("%lld %d is eating\n", philo->status->currenttime, philo->index);
		// 	ft_sleep(philo->status->eattime, get_time());
		// 	philo->lastmeal = get_time() - philo->status->time;
		// 	philo->meals++;
		// 	// printf("meal: %d, %d\n", philo->meals, philo->index);
		// 	if (allfull(philo))
		// 	{
		// 		// printf("full");
		// 		return (NULL);
		// 	}
		// 	philo->hasfork = 0;
		// 	philo->next->hasfork = 0;
		// 	philo->mode = SLEEP;
		// 	printf("%lld %d is sleeping\n", philo->status->currenttime, philo->index);
		// 	ft_sleep(philo->status->sleeptime, get_time());
		
		// }
			// pthread_mutex_unlock(&philo->status->mutex);
	pthread_mutex_lock(&philo->status->deathmutex);
	philo->dead = 1;
	pthread_mutex_unlock(&philo->status->deathmutex);
	return NULL;
	}
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

int main (int argc, char **argv)
{
	pthread_t   *philos;
	pthread_t	check;
	t_status    *status;
	t_philo     *table;

	if (!checkargs(argv, argc))
		return (0);

	philos = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	if (!philos)
		return (0);
	status = malloc(sizeof(t_status));

	table = createtable(ft_atoi(argv[1]), argv, status);
	status = init_status(argv, status, table);

    // Thread that checks if any philo is DEAD

	pthread_create(&check, NULL, &checker, table);

	createthreads(table, philos);

	while (1)
	{
		if (checkforrunning(table));
		{
			jointhreads(philos, ft_atoi(argv[1]));
			break ;
		}
	}
	pthread_join(check, NULL);
	free(philos);

	return 0;
}
