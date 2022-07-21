/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log_printer.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:46:56 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/21 19:13:42 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	queue_log(t_sim_data *attr, t_philo *philo)
{
	static size_t	i;
	size_t			queue_size;

	pthread_mutex_lock(&attr->queue_lock);
	queue_size = attr->n_philo * QUEUE_SIZE;
	attr->log_queue[i].philo_id = philo->id;
	attr->log_queue[i].philo_status = philo->status;
	attr->log_queue[i].log_time = philo->last_action_time;
	attr->log_queue[i].log_status = CREATED;
	if (++i == queue_size)
		i = 0;
	pthread_mutex_unlock(&attr->queue_lock);
}

void	print_queue_item(t_log queue, t_time start_time)
{
	const char	*status_msg[6] = {"has taken a fork", "is eating",	\
					"is sleeping", "is thinking", "died",			\
					"all philosophers have eaten - simulation finished"};
	long		ts;

	ts = time_delta_msec(start_time, queue.log_time);
	// if (queue.philo_status != ALL_EATEN)
	printf(FORMAT_STR, ts, queue.philo_id, status_msg[queue.philo_status]);
}

void	print_queue(t_sim_data *attr)
{
	size_t	i;
	size_t	queue_size;
	t_log	*queue;

	queue = attr->log_queue;
	queue_size = attr->n_philo * QUEUE_SIZE;
	i = 0;
	while (true)
	{
		usleep(50);
		if (queue[i].log_status == CREATED)
		{
			print_queue_item(queue[i], attr->start_time);
			queue[i].log_status = PRINTED;
			if (++i == queue_size)
				i = 0;
		}
		if (attr->all_philo_alive == false)
			break ;
	}
}
