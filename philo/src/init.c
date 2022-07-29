/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 20:58:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/29 11:15:36 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init_resources(t_sim *data)
{	
	uint16_t	i;
	u_int16_t	n_philo;

	n_philo = data->attr[N_PHILO];
	i = 0;
	data->is_running = true;
	while (i < n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].sim_data = data;
		data->philo[i].last_ate = data->start_time;
		data->philo[i].fork[LEFT] = data->fork[i % n_philo];
		data->philo[i].fork[RGHT] = data->fork[(i + 1) % n_philo];
		i++;
	}
	i = 0;
	while (i < QUEUE_SIZE)
		data->queue[i++].status = UNDEFINED;
}
