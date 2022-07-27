/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 20:58:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/27 13:36:29 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init_resources(t_sim *data)
{	
	uint16_t	i;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		data->philo[i].id = i + 1;
		data->philo[i].sim_data = data;
		data->philo[i].last_ate = data->start_time;
		i++;
	}
	i = 0;
	while (i < QUEUE_SIZE)
		data->queue[i++].status = UNDEFINED;
	data->is_running = true;
}
