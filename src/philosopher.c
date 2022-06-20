/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 11:44:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/20 12:44:46 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <philo_consts.h>

int	think(t_philo *philo)
{
	if (philo->g_attr->all_philo_alive == false)
		return (1);
	philo->status = THINKING;
	print_status(philo);
	return (0);
}

int	sleeping(t_philo *philo)
{	
	if (philo->g_attr->all_philo_alive == false)
		return (1);
	philo->status = SLEEPING;
	print_status(philo);
	usleep(philo->g_attr->sleep_duration);
	return (0);
}

static void	die(t_philo *philo)
{
	philo->g_attr->all_philo_alive = false;
	philo->status = DIED;
	print_status(philo);	
}

int	eat(t_philo *philo)
{
	if (philo->g_attr->all_philo_alive == false
		|| philo->eat_count == philo->g_attr->min_eat_count)
	{
		return (1);
	}
	if (time_delta_usec(philo->g_attr->start_time, philo->last_time_eaten)
		> (long) philo->g_attr->die_duration)
	{
		die(philo);
		return (1);
	}
	pick_up_fork(philo, philo->left_fork);
	pick_up_fork(philo, philo->right_fork);
	philo->status = EATING;
	philo->last_time_eaten = gen_timestamp();
	print_status(philo);
	usleep(philo->g_attr->eat_duration);
	put_down_fork(philo->right_fork);
	put_down_fork(philo->left_fork);
	philo->eat_count++;
	return (0);
}