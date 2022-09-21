/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/05 13:39:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/21 17:34:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <signal.h>

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

void	*child_status_checker(void *arg)
{	
	t_sim		*data;
	uint32_t	t_delta;

	data = arg;
	sem_wait(data->generic_sem[CHECKER_LOCK]);
	sem_post(data->generic_sem[CHECKER_LOCK]);
	while (1)
	{
		t_delta = time_delta_msec(data->philo.last_ate, get_time());
		if (t_delta > (uint32_t) data->attr[T_DIE])
			print_status(DIED, get_time(), &data->philo);
		usleep(200 - data->attr[N_PHILO]);
	}
	return (NULL);
}
