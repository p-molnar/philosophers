/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_util.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:23:48 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/29 18:26:31 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	pick_up_fork(t_philo *philo, t_mutex *fork)
{
	if ((philo->id - 1) % 2 == 0)
		usleep(10);
	if (pthread_mutex_lock(fork))
		return (error_handler(MUTEX_ERROR, "pick_up_fork"));
	philo->status = TAKING_FORK;
	philo->last_action_time = get_time();
	queue_log(philo->sim_attr, philo);
	return (EXIT_SUCCESS);
}

int	put_down_fork(t_mutex *fork)
{
	if (pthread_mutex_unlock(fork))
		return (error_handler(MUTEX_ERROR, "put_down_fork"));
	return (EXIT_SUCCESS);
}


int	put_down_forks(t_philo *philo)
{
if ((philo->id - 1) % 2 == 0)
	{
		if (put_down_fork(philo->right_fork))
			return (EXIT_FAILURE);
		if (put_down_fork(philo->left_fork))
			return (EXIT_FAILURE);
	}
	else
	{
		if (put_down_fork(philo->left_fork))
			return (EXIT_FAILURE);
		if (put_down_fork(philo->right_fork))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}