/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_util.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:23:48 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/16 00:41:47 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_status(t_philo *philo, t_timestamp ts)
{
	const char *status_msg[5] = {
								"has taken a fork",
								"is eating",
								"is sleeping",
								"is thinking",
								"died"
								};
	int	status;

	status  = philo->state;
	printf("%-8zu %zu %s\n", ts, philo->id, status_msg[status]);
}

size_t	gen_time_stamp(t_time time)
{
	t_time	curr_time;
	size_t	start_time_ms;
	size_t	curr_time_ms;
	size_t	delta;

	gettimeofday(&curr_time, NULL);
	start_time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	curr_time_ms = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	delta = curr_time_ms - start_time_ms;
	return (delta);
}

void	pick_up_fork(t_philo *philo, int *fork)
{
	t_timestamp ts;

	if (fork != NULL)
		*fork = IN_USE;
	philo->state = TAKING_FORK;
	ts = gen_time_stamp(philo->g_attr->start_time);
	print_status(philo, ts);
}

void	put_down_fork(int *fork)
{
	if (fork != NULL)
		*fork = AVAILABLE;
}