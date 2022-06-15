/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:40:24 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/16 01:14:23 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
void	assign_forks(t_philo **philo, t_attr *attr, size_t i)
{
	(*philo)[i].left_fork = &attr->fork_arr[i % attr->philo_count];
	(*philo)[i].right_fork = &attr->fork_arr[(i + 1) % attr->philo_count];
}

// protect and free mallocs!
int	init_vars(t_philo **philo, t_attr *attr)
{
	t_philo	*philo_arr;
	int		*fork_arr;
	size_t	i;

	philo_arr = malloc(sizeof(t_philo) * attr->philo_count);
	if (philo_arr == NULL)
		return (EXIT_FAILURE);
	*philo = philo_arr;
	fork_arr = malloc(sizeof(int) * attr->philo_count);
	if (fork_arr == NULL)
		return (EXIT_FAILURE);
	attr->fork_arr = fork_arr;
	i = 0;
	while (i < (size_t) attr->philo_count)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].state = UNDEFINED;
		(*philo)[i].eat_count = 0;
		(*philo)[i].g_attr = attr;
		(*philo)[i].last_time_eaten = 0;
		assign_forks(philo, attr, i);
		i++;
	}
	return (0);
}

int	create_threads(t_philo *philo_arr, t_attr *attr)
{
	size_t	i;

	i = 0;
	pthread_mutex_init(&attr->mutex, NULL);
	gettimeofday(&attr->start_time, NULL);
	while (i < (size_t) attr->philo_count)
	{
		pthread_create(&(philo_arr[i].thread), NULL, (void *) &run_philo_life_cycle,
						(void *) &philo_arr[i]);
		i++;
	}
	i = 0;
	while (i < (size_t) attr->philo_count)
	{
		pthread_join(philo_arr[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&attr->mutex);
	return (1);
}
