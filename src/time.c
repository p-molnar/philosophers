/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 22:56:41 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/29 13:55:05 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	precise_sleep(long duration)
{
	t_time	start_time;

	start_time = get_time();
	while (true)
	{
		if (time_delta_msec(start_time, get_time()) >= duration)
			break ;
		usleep(50);
	}
}

long	time_delta_msec(t_time t1, t_time t2)
{
	long	t1_msec;
	long	t2_msec;
	long	delta;

	t1_msec = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	t2_msec = t2.tv_sec * 1000 + t2.tv_usec / 1000;
	delta = t2_msec - t1_msec;
	return (delta);
}

t_time	get_time(void)
{
	t_time	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time);
}
