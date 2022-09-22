/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 16:51:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 09:51:09 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

void	drop_forks(t_philo *philo)
{
	uint16_t	i;

	i = 0;
	while (i < philo->n_forks_in_hand)
	{
		sem_post(philo->sim_data->generic_sem[FORK]);
		i++;
	}
}

static void	philo_think(t_philo *data)
{
	print_status(THINKING, get_time(), data);
}

static void	philo_eat(t_philo *data)
{
	t_time	eat_start;

	sem_wait(data->self_lock);
	sem_wait(data->sim_data->generic_sem[FORK]);
	print_status(TAKING_FORK, get_time(), data);
	data->n_forks_in_hand++;
	sem_wait(data->sim_data->generic_sem[FORK]);
	print_status(TAKING_FORK, get_time(), data);
	data->n_forks_in_hand++;
	eat_start = get_time();
	print_status(EATING, eat_start, data);
	data->last_ate = eat_start;
	precise_msleep(data->sim_data->attr[T_EAT]);
	if (++data->eat_count == data->sim_data->attr[N_EAT])
	{
		drop_forks(data);
		exit(FED);
	}
	sem_post(data->sim_data->generic_sem[FORK]);
	data->n_forks_in_hand--;
	sem_post(data->sim_data->generic_sem[FORK]);
	data->n_forks_in_hand--;
	sem_post(data->self_lock);
}

static void	philo_sleep(t_philo *data)
{
	print_status(SLEEPING, get_time(), data);
	precise_msleep(data->sim_data->attr[T_SLEEP]);
}

bool	simulate(t_philo *data)
{
	uint16_t	status;

	sem_wait(data->sim_data->generic_sem[START_LOCK]);
	sem_post(data->sim_data->generic_sem[START_LOCK]);
	sem_wait(data->self_lock);
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
