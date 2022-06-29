/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_actions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 11:44:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/29 11:50:12 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <philo_consts.h>

int	philo_think(t_philo *philo)
{
	philo->status = THINKING;
	philo->last_action_time = get_time();
	if (queue_log(philo->sim_attr, philo))
		return (EXIT_FAILURE);
	return (0);
}

int	pick_up_forks(t_philo *philo)
{
	if ((philo->id - 1) % 2 == 0)
	{
		if (pick_up_fork(philo, philo->right_fork))
			return (EXIT_FAILURE);
		if (pick_up_fork(philo, philo->left_fork))
			return (EXIT_FAILURE);
	}
	else
	{
		if (pick_up_fork(philo, philo->left_fork))
			return (EXIT_FAILURE);
		if (pick_up_fork(philo, philo->right_fork))
			return (EXIT_FAILURE);
	}
	return (0);
}

int	philo_eat(t_philo *philo)
{
	t_time	eat_time;

	if (pick_up_forks(philo))
		return (EXIT_FAILURE);
	eat_time = get_time();
	philo->status = EATING;
	philo->last_action_time = eat_time;
	if (queue_log(philo->sim_attr, philo))
		return (EXIT_FAILURE);
	philo->last_time_eaten = eat_time; 
	precise_sleep(philo->sim_attr->t_eat);
	if (put_down_forks(philo))
		return (EXIT_FAILURE);
	philo->n_eat++;
	return (0);
}

int	philo_sleep(t_philo *philo)
{	
	philo->status = SLEEPING;
	philo->last_action_time = get_time();
	if (queue_log(philo->sim_attr, philo))
		return (EXIT_FAILURE);
	precise_sleep(philo->sim_attr->t_sleep);
	return (0);
}
