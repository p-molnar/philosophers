/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/05 13:39:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/05 11:45:54 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <signal.h>

static bool	is_philo_fed(t_sim *data)
{
	bool	is_fed;

		is_fed = data->philo.eat_count >= (uint16_t) data->attr[N_EAT];
		if (data->attr[N_EAT] == UNDEFINED || !is_fed)
			return (false);
	return (true);
}

void	drop_forks(t_sim *data)
{
	uint16_t	i;

	i = 0;
	sem_wait(data->philo.self);
	while (i < data->philo.forks_in_hand)
	{
		sem_post(data->sem[FORK]);
		i++;
	}
	sem_wait(data->philo.self);
}

void	*checker_thread(void *arg)
{	
	t_sim		*data;
	uint32_t	t_delta;

	data = arg;
	sem_wait(data->sem[CHECKER_LOCK]);
	sem_post(data->sem[CHECKER_LOCK]);
	while (1)
	{
		sem_wait(data->philo.self);
		t_delta = time_delta_msec(data->philo.last_ate, get_time());
		sem_post(data->philo.self);
		if (t_delta > (uint32_t) data->attr[T_DIE])
			log_status(&data->philo, DIED, get_time());
		else if (is_philo_fed(data))
		{
			sem_wait(data->philo.self);
			data->philo.status = FED;
			sem_post(data->philo.self);
			// printf("RETURNED FROM CHECKER\n");
			// printf("FED\n");
		}
		usleep(500);
	}
	return (NULL);
}
