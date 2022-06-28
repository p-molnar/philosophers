/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_actions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 11:44:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/28 13:59:59 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <philo_consts.h>

int	philo_think(t_philo *philo)
{
	t_log	*log;

	log = create_log(philo, THINKING);
	if (log == NULL)
		return (EXIT_FAILURE);
	queue_log(philo->g_attr, log);
	return (0);
}

int	pick_up_forks(t_philo *philo)
{
	if ((philo->id - 1) % 2 == 0)
	{
		if (pick_up_fork(philo, philo->left_fork))
			return (EXIT_FAILURE);
		if (pick_up_fork(philo, philo->right_fork))
			return (EXIT_FAILURE);
	}
	else
	{
		if (pick_up_fork(philo, philo->right_fork))
			return (EXIT_FAILURE);
		if (pick_up_fork(philo, philo->left_fork))
			return (EXIT_FAILURE);
	}
	return (0);
}

int	philo_eat(t_philo *philo)
{
	t_log	*log;

	if (pick_up_forks(philo))
		return (EXIT_FAILURE);
	log = create_log(philo, EATING);
	if (log == NULL)
		return (EXIT_FAILURE);
	queue_log(philo->g_attr, log);
	philo->last_time_eaten = get_time(); 
	psleep(philo->g_attr->t_eat);
	put_down_forks(philo);
	philo->n_eat++;
	return (0);
}

int	philo_sleep(t_philo *philo)
{	
	t_log	*log;

	log = create_log(philo, SLEEPING);
	if (log == NULL)
		return (EXIT_FAILURE);
	queue_log(philo->g_attr, log);
	psleep(philo->g_attr->t_sleep);
	return (0);
}
