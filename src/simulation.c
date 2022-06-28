/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:40:24 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/28 14:03:16 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void static	run_philo_life_cycle(t_philo *philo)
{
	philo->last_time_eaten = philo->g_attr->start_time;

	if ((philo->id - 1) == 0)
		usleep (philo->g_attr->n_philo * 2);
	while (philo->g_attr->all_philo_alive)
	{
		if (philo_think(philo))
			break ;
		if (philo_eat(philo))
			break ;
		if (philo_sleep(philo))
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
	size_t		i;
	pthread_t	status;
	pthread_t	print;
	
	i = 0;
	gettimeofday(&attr->start_time, NULL);
	if (pthread_mutex_init(&attr->queue_lock, NULL))
		return (error_handler(MUTEX_ERROR));
	while (i < (size_t)attr->n_philo)
	{
		if (pthread_mutex_init(attr->fork_arr[i], NULL))
			return (error_handler(MUTEX_ERROR));
		if (create_threads(&philo_arr[i]))
			return (error_handler(THREAD_ERROR));
		i++;
	}
	if (pthread_create(&status, NULL, (void *) &philo_checker, (void *)philo_arr))
		return (error_handler(THREAD_ERROR));
	if (pthread_create(&print, NULL, (void *) &print_queue, (void *)attr))
		return (error_handler(THREAD_ERROR));	
	i = 0;
	while (i < (size_t)attr->n_philo)
	{
		if (join_threads(&philo_arr[i]))
			return (error_handler(THREAD_ERROR));
		if (pthread_mutex_destroy(attr->fork_arr[i]))
			return (error_handler(MUTEX_ERROR));
		i++;
	}
	if (pthread_join(status, NULL))
		return (error_handler(THREAD_ERROR));
	if (pthread_join(print, NULL))
		return (error_handler(THREAD_ERROR));
	if (pthread_mutex_destroy(&attr->queue_lock))
		return (error_handler(MUTEX_ERROR));
	return (EXIT_SUCCESS);
}
