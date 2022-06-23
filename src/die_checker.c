/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   die_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 15:37:41 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/23 17:56:57 by pmolnar       ########   odam.nl         */
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
		if (time_delta_usec(philo_arr[i].last_time_eaten, gen_timestamp()) > die_duration)
		{
			philo_arr[i].status = DIED;
			philo_arr[i].g_attr->all_philo_alive = false;
			print_status(&philo_arr[i]);
			break ;
		}
		if (i == philo_count - 1)
			i = 0;
		i++;
	}
}
