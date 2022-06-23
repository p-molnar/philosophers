/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:40:24 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/22 11:00:05 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void static	run_philo_life_cycle(t_philo *philo)
{
	philo->last_time_eaten = philo->g_attr->start_time;
	while (philo->g_attr->all_philo_alive)
	{
		if (think(philo))
			break ;
		if (eat(philo))
			break ;
		if (sleeping(philo))
			break ;
	}
	return ;
}

static int	create_threads(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, \
		(void *) &run_philo_life_cycle, (void *) philo))
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	join_threads(t_philo *philo)
{
	if (pthread_join(philo->thread, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	launch_simulation(t_philo *philo_arr, t_attr *attr)
{
	size_t	i;

	i = 0;
	gettimeofday(&attr->start_time, NULL);
	if (pthread_mutex_init(&attr->print_lock, NULL))
		return (error_handler(MUTEX_ERROR));
	while (i < (size_t)attr->philo_count)
	{
		if (pthread_mutex_init(attr->fork_arr[i], NULL))
			return (error_handler(MUTEX_ERROR));
		if (create_threads(&philo_arr[i]))
			return (error_handler(THREAD_ERROR));
		i++;
	}
	i = 0;
	while (i < (size_t)attr->philo_count)
	{
		if (join_threads(&philo_arr[i]))
			return (error_handler(THREAD_ERROR));
		if (pthread_mutex_destroy(attr->fork_arr[i]))
			return (error_handler(MUTEX_ERROR));
		i++;
	}
	if (pthread_mutex_destroy(&attr->print_lock))
		return (error_handler(MUTEX_ERROR));
	return (EXIT_SUCCESS);
}
