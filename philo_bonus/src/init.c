/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 20:58:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/25 20:29:32 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

void	init_queue(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < QUEUE__SIZE)
	{
		data->queue[i].status = UNDEFINED;
		i++;
	}
}

void	init_philo(t_sim *data, uint16_t id)
{
		data->philo.id = id;
		data->philo.forks_in_hand = 0;
		data->philo.eat_count = 0;
		data->philo.sim_data = data;
		data->philo.sim_data->sim_running = true;
}
