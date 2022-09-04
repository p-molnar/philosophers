/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 20:58:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/04 23:00:15 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

void	init_resources(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < QUEUE__SIZE)
	{
		data->queue[i].status = UNDEFINED;
		i++;
	}
	i = 0;
	while (i < data->attr[N_PHILO])
		data->philo_exited[i++] = false;
}

sem_t	*gen_philo_sem(t_sim *data)
{
	
}

void	init_philo(t_sim *data, uint16_t i)
{
		data->philo.id = i + 1;
		data->philo.forks_in_hand = 0;
		data->philo.eat_count = 0;
		data->philo.sim_data = data;
		data->philo.sim_data->sim_running = true;
		data->philo.self = gen_philo_sem(data);
}
