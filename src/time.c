/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/23 22:56:41 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/24 00:02:27 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	psleep(long usec)
{
	t_time	start_time;

	start_time = get_time();
	while (true)
	{
		if (time_delta_usec(start_time, get_time()) / 1000 == usec / 1000)
			break ;
		usleep(100);
	}
}

long	time_delta_usec(t_time t1, t_time t2)
{
	long	t1_usec;
	long	t2_usec;
	long	delta;

	t1_usec = t1.tv_sec * 1000000 + t1.tv_usec;
	t2_usec = t2.tv_sec * 1000000 + t2.tv_usec;
	delta = t2_usec - t1_usec;
	return (delta);
}

t_time	get_time(void)
{
	t_time	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time);
}
