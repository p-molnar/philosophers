/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 15:37:41 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/27 14:28:55 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_checker(t_philo *philo_arr)
{
	size_t	i;
	size_t	philo_count;
	long	die_duration;
	t_log	log;

	philo_count = philo_arr[0].g_attr->n_philo;
	die_duration = philo_arr[0].g_attr->t_die;
	i = 0;
	while (true)
	{
		if (time_delta_msec(philo_arr[i].last_time_eaten, get_time()) > die_duration)
		{
			create_log(&philo_arr[i], &log, DIED);
			add_log_to_queue(philo_arr[i].g_attr, &log);
			philo_arr[i].g_attr->all_philo_alive = false;
			break ;
		}
		if (i == philo_count - 1)
			i = 0;
		i++;
		usleep(200);
	}
}
