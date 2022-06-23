/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_util.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:23:48 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/22 10:59:14 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_status(t_philo *philo)
{
	int			status;
	long		timestamp;
	const char	*status_msg[5] = {"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};

	pthread_mutex_lock(&philo->g_attr->print_lock);
	timestamp = time_delta_usec(philo->g_attr->start_time, gen_timestamp());
	status = philo->status;
	if (status == EATING)
		timestamp = time_delta_usec(philo->g_attr->start_time, philo->last_time_eaten);
	printf("%-8zu %zu %s\n", timestamp, philo->id, status_msg[status]);
	pthread_mutex_unlock(&philo->g_attr->print_lock);
}

long	time_delta_usec(t_time t1, t_time t2)
{
	long	t1_usec;
	long	t2_usec;
	long	delta;

	t1_usec = t1.tv_sec * 1000000 + t1.tv_usec;
	t2_usec = t2.tv_sec * 1000000 + t2.tv_usec;
	delta = t2_usec - t1_usec;
	return (delta);
}

t_time	gen_timestamp(void)
{
	t_time	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time);
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
