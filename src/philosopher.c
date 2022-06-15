/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 11:44:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/16 01:04:51 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <philo_consts.h>

void	think(t_philo *philo)
{
	philo->state = THINKING;
	print_status(philo, gen_time_stamp(philo->g_attr->start_time));
}

void	sleeping(t_philo *philo)
{
	philo->state = SLEEPING;
	print_status(philo, gen_time_stamp(philo->g_attr->start_time));
	usleep(philo->g_attr->sleep_duration);
}

int	eat(t_philo *philo)
{
	t_timestamp ts;

	pthread_mutex_lock(&philo->g_attr->mutex);
	pick_up_fork(philo, philo->left_fork);
	pick_up_fork(philo, philo->right_fork);
	philo->state = EATING;
	philo->eat_count++;
	ts = gen_time_stamp(philo->g_attr->start_time);
	if (ts - philo->last_time_eaten > philo->g_attr->die_duration)
		return (1);
	philo->last_time_eaten = ts;
	print_status(philo, ts);
	usleep(philo->g_attr->eat_duration);
	put_down_fork(philo->left_fork);
	put_down_fork(philo->right_fork);
	if (philo->eat_count == philo->g_attr->required_eat_count)
		return (1);
	pthread_mutex_unlock(&philo->g_attr->mutex);
	return (0);
}

void	run_philo_life_cycle(t_philo *philo)
{
	while (true)
	{
		if (eat(philo))
			return ;
		think(philo);
		sleeping(philo);
	}
}