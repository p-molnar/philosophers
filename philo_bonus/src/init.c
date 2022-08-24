/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 20:58:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/24 12:50:20 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

static void	init_philos(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].sim_data = data;
		i++;
	}
}

static void	init_queue(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < QUEUE__SIZE)
		data->queue[i++].status = UNDEFINED;
}

void	init_resources(t_sim *data)
{
	init_philos(data);
	init_queue(data);
	data->is_running = true;
}
