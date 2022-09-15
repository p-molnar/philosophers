/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 16:51:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/15 13:55:54 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

static void	philo_think(t_philo *data)
{
	log_status(data, THINKING, get_time());
}

static void	philo_eat(t_philo *data)
{
	t_time	t_eat;

	sem_wait(data->self_lock);
	sem_wait(data->sim_data->generic_sem[FORK]);
	log_status(data, TAKING_FORK, get_time());
	data->forks_in_hand++;
	sem_wait(data->sim_data->generic_sem[FORK]);
	log_status(data, TAKING_FORK, get_time());
	data->forks_in_hand++;
	t_eat = get_time();
	log_status(data, EATING, t_eat);
	data->last_ate = t_eat;
	precise_msleep(data->sim_data->attr[T_EAT]);
	if (data->eat_count++ == data->sim_data->attr[N_EAT])
	{
		drop_forks(data);
		exit(FED);
	}
	sem_post(data->sim_data->generic_sem[FORK]);
	data->forks_in_hand--;
	sem_post(data->sim_data->generic_sem[FORK]);
	data->forks_in_hand--;
	sem_post(data->self_lock);
}

static void	philo_sleep(t_philo *data)
{
	log_status(data, SLEEPING, get_time());
	precise_msleep(data->sim_data->attr[T_SLEEP]);
}

bool	simulate(t_philo *data)
{
	uint16_t	status;

	sem_wait(data->sim_data->generic_sem[START_LOCK]);
	sem_post(data->sim_data->generic_sem[START_LOCK]);
	sem_wait(data->self_lock);
	data->sim_data->start_time = get_time();
	data->last_ate = data->sim_data->start_time;
	sem_post(data->self_lock);
	philo_think(data);
	if (data->id % 2)
		precise_msleep(1);
	status = EATING;
	while (1)
	{
		if (status == THINKING)
			philo_think(data);
		else if (status == EATING)
			philo_eat(data);
		else if (status == SLEEPING)
			philo_sleep(data);
		status = (status + 1) % STATUS__COUNT;
	}
	return (EXIT_SUCCESS);
}
