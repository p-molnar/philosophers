/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   die_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 15:37:41 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/24 00:00:49 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_checker(t_philo *philo_arr)
{
	size_t	i;
	size_t	philo_count;
	long	die_duration;

	philo_count = philo_arr[0].g_attr->philo_count;
	die_duration = philo_arr[0].g_attr->die_duration;
	i = 0;
	while (true)
	{
		if (time_delta_usec(philo_arr[i].last_time_eaten, get_time()) / 1000 > die_duration / 1000)
		{
			philo_arr[i].status = DIED;
			print_status(&philo_arr[i]);
			philo_arr[i].g_attr->all_philo_alive = false;
			break ;
		}
		if (i == philo_count - 1)
			i = 0;
		i++;
	}
}
