/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/05 13:39:17 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/26 17:14:14 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <signal.h>

static bool	is_philo_fed(t_sim *data)
{
	bool	is_fed;

		// pthread_mutex_lock(&data->philo[i].self);
		is_fed = data->philo.eat_count >= (uint16_t) data->attr[N_EAT];
		// pthread_mutex_unlock(&data->philo[i].self);
		if (data->attr[N_EAT] == UNDEFINED || !is_fed)
			return (false);
	return (true);
}

void	drop_forks(t_sim *data)
{
	uint16_t	i;

	i = 0;
	while (i < data->philo.forks_in_hand)
	{
		sem_post(data->sem[FORK]);
		i++;
	}
}

static void	die_action(t_sim *data)
{
	log_status(&data->philo, DIED, get_time());
	drop_forks(data);
	data->philo.status = DIED;
	data->sim_running = false;
}

static void	all_fed_action(t_sim *data)
{
	log_status(&data->philo, FED, get_time());
}

void	*checker_thread(void *arg)
{	
	t_sim		*data;

	data = arg;
	sem_wait(data->sem[CHECKER_LOCK]);
	sem_post(data->sem[CHECKER_LOCK]);
	while (1)
	{
		// printf("checker_spinning\n");
		if (time_delta_msec(data->philo.last_ate, get_time())
			> (uint32_t) data->attr[T_DIE])
		{
			die_action(data);
			usleep(100);
			sem_wait(data->sem[DIE]);
			return (NULL);
		}
		if (is_philo_fed(data))
		{
			all_fed_action(data);
			return (NULL);
		}
		usleep(300);
	}
	return (NULL);
}
