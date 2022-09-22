/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 20:58:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 10:18:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

void	init_resources(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < data->attr[N_PHILO])
	{
		data->philo_sem[i] = gen_philo_sem(i);
		i++;
	}
}

void	init_philo(t_sim *data, uint16_t i)
{
	data->philo.id = i + 1;
	data->philo.n_forks_in_hand = 0;
	data->philo.eat_count = 0;
	data->philo.sim_data = data;
	data->philo.self_lock = data->philo_sem[i];
}
