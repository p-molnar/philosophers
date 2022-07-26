/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 21:20:35 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/25 20:18:00 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	p_think(t_philo *data)
{
	(void) data;
}

void	p_eat(t_philo *data)
{
	(void) data;
}

void	p_sleep(t_philo *data)
{
	(void) data;
}

void	simulation(t_philo *philo)
{
	// usleep(philo->sim_data->attr[N_PHILO] + (philo->id - 1) * 50);
	pthread_mutex_lock(&philo->sim_data->mutex[START]);
	// usleep((philo->id - 1) * 1000);
	printf("philo id: %u\n", philo->id);
	pthread_mutex_unlock(&philo->sim_data->mutex[START]);
	// while (true)
	// {
	// 	think(data);
	// 	eat(data);
	// 	sleep(data);
	// }
}
