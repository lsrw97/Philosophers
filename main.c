#include "philo.h"

void*	timefunc(void *arg);


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
		// printf("%ld, %ld\n", get_time(), timenow);
		if (get_time() - timenow >= waittime)
			return (1);
	}
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

t_philo	*ft_newnode(int life, t_philo *prev, int index, t_status *status)
{
	t_philo	*table;
	struct timeval	current_time;

	table = malloc(sizeof(t_philo));
	if (!table)
		return (NULL);
	table->lifetime = life;
	table->mode = THINK;
	table->hasfork = 1;
	table->index = index;
	table->time = status->time;
	table->currtime = status->currtime;
	table->next = NULL;
	table->prev = prev;
	table->status = status;
	table->lastmeal = 0;
	return (table);
}

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

t_status	*init_status(char **argv, t_status *status, t_philo *table)
{
	status->lifetime = ft_atoi(argv[1]);
	status->eattime = ft_atoi(argv[2]);
	status->sleeptime = ft_atoi(argv[3]);
	status->running = 1;
	status->dead = 0;
	status->time = get_time();
	status->currtime = status->time;
	status->table = table;
	pthread_mutex_init(&status->mutex, NULL);
	return status;
}

t_philo	*createtable(int size, char **argv, t_status *status)
{
	t_philo	*table;
	t_philo	*tmp;
	int		i;

	// init_status(argv, &status);
	i = 1;
	table = ft_newnode(ft_atoi(argv[1]), NULL, 1, status);
	tmp = table;
	while (++i < size + 1)
	{
		tmp->next = ft_newnode(ft_atoi(argv[1]), tmp, i, status);
		tmp = tmp->next;
	}
	tmp->next = table;
	table->prev = tmp;
	return (table);
}

int	checkfordeadphilos(t_philo *table)
{
	t_philo	*philos;

	philos = table;
	while (philos->next->index != table->index)
	{
		if (philos->mode == DEAD)
			return (1);
		philos = philos->next;
	}
	return (0);
}

void*	execution(void *arg)
{
	t_philo	*philo;

	philo = arg;
	t_status *status;

	status = philo->status;
	while (1)
	{
		while (!philo->hasfork || !philo->next->hasfork)
		{
			if (philo->mode != THINKING)
			{
				philo->mode = THINKING;
				// if (checkfordeadphilos(philo))
				// 	return (NULL);
				printf("%d	Philo %d is Thinking			%d\n", get_time() - philo->status->time, philo->index, philo->lastmeal);
			}
		}
	pthread_mutex_lock(&status->mutex);
	// if (checkfordeadphilos(philo))
	// 	return (NULL);
	printf("%d	Philo %d takes Forks			%d\n", get_time() - philo->status->time, philo->index, philo->lastmeal);
	philo->hasfork = 0;
	philo->next->hasfork = 0;
	philo->mode = EAT;
	printf("%d	Philo %d is eating			%d\n", get_time() - philo->status->time, philo->index, philo->lastmeal);
	// if (checkfordeadphilos(philo))
	// 	return (NULL);
	ft_sleep(200, get_time());
	philo->lastmeal = get_time() - philo->status->time;
	pthread_mutex_unlock(&status->mutex);
	philo->meals++;
	philo->mode = SLEEP;
	philo->hasfork = 1;
	philo->next->hasfork = 1;
	// if (checkfordeadphilos(philo))
	// 	return (NULL);
	printf("%d	Philo %d is Sleeping			%d\n", get_time() - philo->status->time, philo->index, philo->lastmeal);
	ft_sleep(200, get_time());
	
	// printf("time: %d\n", (philo->status->time - get_time()));
	}
	return NULL;
}

// void*	timefunc(void *arg)
// {
// 	t_status *status;
// 	int		i;

// 	i = -1;
// 	status = (t_status *)arg;
// 	while (status->inttime < 1000000)
// 	{
// 		status->inttime = get_time() - status->time;
// 	}
// 	return (NULL);
// }

void*	updatetablelife(void *arg)
{
	t_philo	*table;

	table = (t_philo *)arg;
	while (get_time() - table->lastmeal < table->status->lifetime)
	{
		table = table->next;
	}
	table->mode = DEAD;
	printf("%d	Philo %d is Dead\n", (table->status->inttime), table->index);
}

int main (int argc, char **argv)
{
	t_philo				*table;
	t_status			*status;
	unsigned long long	tmp;
    pthread_t 			th[3];
	pthread_t 			timeth;
	pthread_t 			update;

	if (!checkargs(argv, argc))
		return (0);
	status = malloc(sizeof(t_status));
	status = init_status(argv, status, table);
	table = createtable(2, argv, status);

	// pthread_create(&timeth, NULL, &timefunc, status);
	pthread_create(&update, NULL, &updatetablelife, table);
	pthread_create(&th[0], NULL, &execution, table);
	pthread_create(&th[1], NULL, &execution, table->next);
	// pthread_create(&th[2], NULL, &execution, table->next->next);
	if (!pthread_join(update, NULL))
		return 0 ;
	
	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);
	// pthread_join(th[2], NULL);

	// pthread_join(timeth, NULL);
	// status->lifetime = 0;

	// pthread_create(&timeth[0], NULL, &timefunc, status);
	// pthread_join(timeth[0], NULL);
	return 0;
}

// if you run threads in loop catch them with join in another loop afterwards