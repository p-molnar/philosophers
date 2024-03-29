/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 13:16:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 10:32:16 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bns.h>
#include <unistd.h>
#include <sys/time.h>

void	precise_msleep(uint32_t duration)
{
	t_time	start_time;

	start_time = get_time();
	while (true)
	{
		if (time_delta_msec(start_time, get_time()) >= duration)
			break ;
		usleep(5);
	}
}

uint32_t	time_delta_msec(t_time t_old, t_time t_new)
{
	uint32_t	t_new_msec;
	uint32_t	t_old_msec;
	uint32_t	delta;

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
