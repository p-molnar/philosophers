/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 21:20:35 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/26 23:02:01 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	philo_think(t_philo *data)
{
	log_status(data, THINKING, get_time());
}

void	philo_eat(t_philo *data)
{
	(void) data;
}

void	philo_sleep(t_philo *data)
{
	(void) data;
}

uint16_t	simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim_data->mutex[INIT]);
	// printf("philo id: %d\n", philo->id);
	pthread_mutex_unlock(&philo->sim_data->mutex[INIT]);
	while (true)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (EXIT_SUCCESS);
}
