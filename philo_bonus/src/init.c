/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/26 20:58:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/05 10:24:31 by pmolnar       ########   odam.nl         */
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

void	gen_philo_sem(t_sim *data)
{
	char		name[32];
	char		*id;
	uint16_t	i;

	id = ft_itoa(data->philo.id);
	i = 0;
	while (i < 7)
	{
		name[i] = "/philo_"[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(id))
	{
		name[i + 7] = id[i];
		i++;
	}
	name[i + 7] = '\0';
	free (id);
	data->philo.self = sem_open(name, O_CREAT | O_EXCL, 000664, 1);
	if (data->philo.self == SEM_FAILED)
		thrw_err(SEM_ERR_MSG, __FILE__, __LINE__);
	sem_unlink(name);
}

void	init_philo(t_sim *data, uint16_t i)
{
	data->philo.id = i + 1;
	data->philo.forks_in_hand = 0;
	data->philo.eat_count = 0;
	data->philo.sim_data = data;
	data->philo.sim_data->sim_running = true;
	gen_philo_sem(data);
}
