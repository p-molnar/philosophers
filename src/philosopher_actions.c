/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_actions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 11:44:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/27 15:14:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <philo_consts.h>

int	philo_think(t_philo *philo)
{
	t_log	*log = malloc(sizeof(t_log) * 1);

	create_log(philo, log, THINKING);
	add_log_to_queue(philo->g_attr, log);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	t_time	time_of_eat;
	t_log	*log = malloc(sizeof(t_log) * 1);

	pick_up_forks(philo);
	create_log(philo, log, EATING);
	add_log_to_queue(philo->g_attr, log);
	time_of_eat = get_time();
	philo->last_time_eaten = time_of_eat; 
	psleep(philo->g_attr->t_eat);
	put_down_forks(philo);
	philo->n_eat++;
	return (0);
}

int	philo_sleep(t_philo *philo)
{	
	t_log	*log = malloc(sizeof(t_log) * 1);

	create_log(philo, log, SLEEPING);
	add_log_to_queue(philo->g_attr, log);
	psleep(philo->g_attr->t_sleep);
	return (0);
}
