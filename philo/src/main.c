/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/06 22:40:26 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/30 15:11:00 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	clean_up(t_sim_data *attr)
{
	size_t	i;

	if (pthread_mutex_destroy(&attr->queue_lock))
		return (error_handler(MUTEX_ERROR, "clean_up, m_destroy"));
	if (pthread_mutex_destroy(&attr->monitoring_lock))
		return (error_handler(MUTEX_ERROR, "clean_up, m_destroy"));
	if (pthread_mutex_destroy(&attr->start_lock))
		return (error_handler(MUTEX_ERROR, "clean_up, m_destroy"));
	i = 0;
	while (i < (size_t)attr->n_philo)
	{
		if (pthread_mutex_destroy(attr->forks[i]))
			return (error_handler(MUTEX_ERROR, "clean_up, m_destroy"));
		free(attr->forks[i]);
		i++;
	}
	free(attr->forks);
	free(attr->log_queue);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_sim_data	attr;
	t_philo		*philo_arr;

	philo_arr = NULL;
	if (argc == 5 || argc == 6)
	{
		if (parse_args(argc, argv, &attr))
			return (EXIT_FAILURE);
		if (set_up_simulation(&philo_arr, &attr))
			return (EXIT_FAILURE);
		if (launch_simulation(philo_arr, &attr))
			return (EXIT_FAILURE);
		clean_up(&attr);
		usleep(10000);
		//system("leaks philo");
	}
	else
		return (error_handler(INVALID_INPUT, NULL));
	return (EXIT_SUCCESS);
}
