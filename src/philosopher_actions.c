/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_actions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 11:44:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/30 14:55:30 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <philo_consts.h>

void	philo_think(t_philo *philo)
{
	philo->status = THINKING;
	philo->last_action_time = get_time();
	queue_log(philo->sim_attr, philo);
}

void	put_down_forks(t_philo *philo)
{
	if ((philo->id - 1) % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	pick_up_forks(t_philo *philo)
{
	if ((philo->sim_attr->n_philo % 2 != 0) && ((philo->id - 1) % 2 != 0))
		usleep(5);
	if ((philo->id - 1) % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		philo->status = TAKING_FORK;
		philo->last_action_time = get_time();
		queue_log(philo->sim_attr, philo);
		pthread_mutex_lock(philo->left_fork);
		philo->status = TAKING_FORK;
		philo->last_action_time = get_time();
		queue_log(philo->sim_attr, philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		philo->status = TAKING_FORK;
		philo->last_action_time = get_time();
		queue_log(philo->sim_attr, philo);
		pthread_mutex_lock(philo->right_fork);
		philo->status = TAKING_FORK;
		philo->last_action_time = get_time();
		queue_log(philo->sim_attr, philo);
	}
}

void	philo_eat(t_philo *philo)
{
	t_time	eat_time;

	pick_up_forks(philo);
	eat_time = get_time();
	philo->status = EATING;
	philo->last_action_time = eat_time;
	queue_log(philo->sim_attr, philo);
	philo->last_time_eaten = eat_time;
	precise_sleep(philo->sim_attr->t_eat);
	put_down_forks(philo);
	philo->n_eat++;
}

void	philo_sleep(t_philo *philo)
{	
	philo->status = SLEEPING;
	philo->last_action_time = get_time();
	queue_log(philo->sim_attr, philo);
	precise_sleep(philo->sim_attr->t_sleep);
}
