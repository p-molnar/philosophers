/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 15:37:41 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/30 15:08:00 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	all_philos_eaten(t_philo *philo_arr, t_sim_data *sim_attr)
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

void	drop_forks(t_philo *philo_arr)
{
	size_t	i;
	size_t	n_philo;

	i = 0;
	n_philo = philo_arr[0].sim_attr->n_philo;
	while(i < n_philo)
	{
		if ((philo_arr[i].id - 1) % 2)
		{
			put_down_forks(&philo_arr[i]);
		}
		else
		{
			put_down_forks(&philo_arr[i]);
		}
		i++;
	}
}

void	check_status(t_philo *philo_arr)
{
	size_t		i;
	t_sim_data	*sim_attr;
	t_time		curr_time;

	sim_attr = philo_arr[0].sim_attr;
	i = 0;
	while (true)
	{
		curr_time = get_time();
		if (all_philos_eaten(philo_arr, sim_attr) == true)
		{
			philo_arr[i].status = ALL_EATEN;
			philo_arr[i].last_action_time = get_time();
			queue_log(sim_attr, &philo_arr[i]);
			sim_attr->all_philo_alive = false;
			break ;
		}
		if (time_delta_msec(philo_arr[i].last_time_eaten, curr_time) > sim_attr->t_die)
		{
			philo_arr[i].status = DIED;
			philo_arr[i].last_action_time = get_time();
			queue_log(sim_attr, &philo_arr[i]);
			sim_attr->all_philo_alive = false;
			drop_forks(philo_arr);
			break ;
		}
		if (++i >= (size_t)(sim_attr->n_philo - 1))
			i = 0;
		usleep(500);
	}
}
