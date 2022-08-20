/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 16:51:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/20 13:19:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>

static void	philo_think(t_philo *philo)
{
	// log_status(philo, THINKING, get_time());
	(void) philo;
}

static void	philo_eat(t_philo *philo)
{
	(void) philo;
}

static void	philo_sleep(t_philo *philo)
{
	(void) philo;
}

bool	simulate(t_philo *philo)
{
	uint16_t	status;

	sem_wait(philo->sim_data->sem[START_LOCK]);
	sem_post(philo->sim_data->sem[START_LOCK]);
	philo_think(philo);
	if (philo->id % 2)
		precise_sleep(1000);
	status = EATING;
	while (1)
	{
		if (status == THINKING)
			philo_think(philo);
		else if (status == EATING)
			philo_eat(philo);
		else if (status == SLEEPING)
			philo_sleep(philo);
		status = (status + 1) % STATUS__COUNT;
	}
	return (EXIT_SUCCESS);
}
