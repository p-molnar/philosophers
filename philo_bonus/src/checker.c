/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/05 13:39:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/15 13:52:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <signal.h>

void	drop_forks(t_philo *philo)
{
	uint16_t	i;

	i = 0;
	while (i < philo->forks_in_hand)
	{
		sem_post(philo->sim_data->generic_sem[FORK]);
		i++;
	}
}

void	*child_status_checker(void *arg)
{	
	t_sim		*data;
	uint32_t	t_delta;

	data = arg;
	sem_wait(data->generic_sem[CHECKER_LOCK]);
	sem_post(data->generic_sem[CHECKER_LOCK]);
	while (1)
	{
		sem_wait(data->philo.self_lock);
		t_delta = time_delta_msec(data->philo.last_ate, get_time());
		sem_post(data->philo.self_lock);
		if (t_delta > (uint32_t) data->attr[T_DIE])
			log_status(&data->philo, DIED, get_time());
		usleep(200 - data->attr[N_PHILO]);
	}
	return (NULL);
}
