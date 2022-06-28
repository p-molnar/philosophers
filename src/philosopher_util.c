/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_util.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:23:48 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/28 12:20:16 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_log	*create_log(t_philo *philo, int status)
{
	t_log	*log;
	
	log = malloc(sizeof(t_log));
	if (log == NULL)
		return (NULL);
	log->status = status;
	log->philo_id = philo->id;
	log->time = get_time();
	return (log);
}

int	pick_up_fork(t_philo *philo, t_mutex *fork)
{
	t_log	*log;

	pthread_mutex_lock(fork);
	log = create_log(philo, TAKING_FORK);
	if (log == NULL)
		return (EXIT_FAILURE);
	queue_log(philo->g_attr, log);
	return (0);
}

void	put_down_fork(t_mutex *fork)
{
	pthread_mutex_unlock(fork);
}


void	put_down_forks(t_philo *philo)
{
	put_down_fork(philo->right_fork);
	put_down_fork(philo->left_fork);
}