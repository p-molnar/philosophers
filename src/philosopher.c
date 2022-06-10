/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/10 11:44:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/11 00:26:15 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <philo_consts.h>

void	thinking(t_philo *philo)
{
	struct timeval	curr_time;
	struct timeval	start_time;
	int				diff;

	start_time = philo->sim_attr->start_time;
	philo->state = THINKING;
	gettimeofday(&curr_time, NULL);
	diff = (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000) - \
			(start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
	printf("%-6.0d Philosopher %zu is thinking\n", diff, philo->id);
}

void	sleeping(t_philo *philo)
{
	struct timeval	curr_time;
	struct timeval	start_time;
	int				diff;

	start_time = philo->sim_attr->start_time;
	philo->state = SLEEPING;
	gettimeofday(&curr_time, NULL);
	usleep(philo->sim_attr->sleep_duration);
	diff = (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000) - \
			(start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
	printf("%-6.0d Philosopher %zu is sleeping\n", diff, philo->id);
}

void	pick_up_fork(int *fork)
{
	if (fork != NULL)
		*fork = IN_USE;
}

void	put_down_fork(int *fork)
{
	if (fork != NULL)
		*fork = AVAILABLE;
}

void	eating(t_philo *philo)
{
	struct timeval	curr_time;
	struct timeval	start_time;
	int				diff;

	start_time = philo->sim_attr->start_time;
	pthread_mutex_lock(&philo->sim_attr->mutex);
	pick_up_fork(philo->left_fork);
	pick_up_fork(philo->right_fork);
	philo->state = EATING;
	gettimeofday(&curr_time, NULL);
	usleep(philo->sim_attr->eat_duration);
	diff = (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000) - \
			(start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
	printf("%-6.0d Philosopher %zu is eating\n", diff, philo->id);
	put_down_fork(philo->left_fork);
	put_down_fork(philo->right_fork);	
	pthread_mutex_unlock(&philo->sim_attr->mutex);
}

void	simulate_philo_life_circle(t_philo *philo)
{
	while (true)
	{
		eating(philo);
		thinking(philo);
		sleeping(philo);
	}
}