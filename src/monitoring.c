/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 15:37:41 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/29 13:20:40 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	all_philos_eaten(t_philo *philo_arr, t_attr *sim_attr)
{
	size_t	i;

	i = 0;
	if (sim_attr->min_n_eat == UNDEFINED)
		return (false);
	while (i < (size_t)sim_attr->n_philo)
	{
		if (philo_arr[i].n_eat < sim_attr->min_n_eat)
			return (false);
		i++;
	}
	return (true);
}

void	status_monitoring(t_philo *philo_arr)
{
	size_t	i;
	t_attr	*sim_attr;

	sim_attr = philo_arr[0].sim_attr;
	i = 0;
	while (true)
	{
		if (all_philos_eaten(philo_arr, sim_attr) == true)
		{
			philo_arr[i].status = ALL_EATEN;
			philo_arr[i].last_action_time = get_time();
			queue_log(sim_attr, &philo_arr[i]);
			sim_attr->all_philo_alive = false;
			break ;
		}
		if (time_delta_msec(philo_arr[i].last_time_eaten, get_time()) > sim_attr->t_die)
		{
			philo_arr[i].status = DIED;
			philo_arr[i].last_action_time = get_time();
			queue_log(sim_attr, &philo_arr[i]);
			sim_attr->all_philo_alive = false;
			break ;
		}
		if (i == (size_t)(sim_attr->n_philo - 1))
			i = 0;
		i++;
		usleep(500);
	}
}
