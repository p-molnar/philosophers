/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_util.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:23:48 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/23 22:57:24 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_status(t_philo *philo)
{
	int			status;
	long		timestamp;
	const char	*status_msg[5] = {"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};
	
	if (philo->g_attr->all_philo_alive == true)
	{
		pthread_mutex_lock(&philo->g_attr->print_lock);
		timestamp = time_delta_usec(philo->g_attr->start_time, get_time());
		status = philo->status;
		if (status == EATING)
			timestamp = time_delta_usec(philo->g_attr->start_time, philo->last_time_eaten);
		printf("%-8zu %zu %s\n", timestamp / 1000, philo->id, status_msg[status]);
		pthread_mutex_unlock(&philo->g_attr->print_lock);
	}
}

void	pick_up_fork(t_philo *philo, t_mutex *fork)
{
	pthread_mutex_lock(fork);
	philo->status = TAKING_FORK;
	print_status(philo);
}

void	put_down_fork(t_mutex *fork)
{
	pthread_mutex_unlock(fork);
}
