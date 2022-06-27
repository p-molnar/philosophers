/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_util.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:23:48 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/27 15:14:57 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	create_log(t_philo *philo, t_log *log, int status)
{
	log->status = status;
	log->philo_id = philo->id;
	log->time = get_time();
}

void	pick_up_fork(t_philo *philo, t_mutex *fork)
{
	t_log	*log = malloc(sizeof(t_log) * 1);

	pthread_mutex_lock(fork);
	create_log(philo, log, TAKING_FORK);
	add_log_to_queue(philo->g_attr, log);
}

void	put_down_fork(t_mutex *fork)
{
	pthread_mutex_unlock(fork);
}

void	pick_up_forks(t_philo *philo)
{
	if ((philo->id - 1) % 2 == 0)
	{
		pick_up_fork(philo, philo->left_fork);
		pick_up_fork(philo, philo->right_fork);
	}
	else
	{
		pick_up_fork(philo, philo->right_fork);
		pick_up_fork(philo, philo->left_fork);
	}
}

void	put_down_forks(t_philo *philo)
{
	put_down_fork(philo->right_fork);
	put_down_fork(philo->left_fork);
}