/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 22:56:41 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/26 19:42:09 by pmolnar       ########   odam.nl         */
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
		usleep(1);
	}
}

long	time_delta_msec(t_time t_old, t_time t_new)
{
	long	t_new_msec;
	long	t_old_msec;
	long	delta;

	t_old_msec = t_old.tv_sec * 1000 + t_old.tv_usec / 1000;
	t_new_msec = t_new.tv_sec * 1000 + t_new.tv_usec / 1000;
	delta = t_new_msec - t_old_msec;
	return (delta);
}

t_time	get_time(void)
{
	t_time	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time);
}
