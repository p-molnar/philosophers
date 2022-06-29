/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log_printer.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 10:46:56 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/29 13:41:19 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	queue_log(t_attr *attr, t_philo *philo)
{
	if (pthread_mutex_lock(&attr->queue_lock))
		return (error_handler(MUTEX_ERROR, "queue_log, m_lock"));
	static size_t i;
	size_t queue_size;

	queue_size = attr->n_philo * QUEUE_SIZE;
	attr->log_queue[i].philo_id = philo->id;
	attr->log_queue[i].philo_status = philo->status;
	attr->log_queue[i].log_time = philo->last_action_time;
	attr->log_queue[i].log_status = CREATED;
	if (++i == queue_size)
		i = 0;
	if (pthread_mutex_unlock(&attr->queue_lock))
		return (error_handler(MUTEX_ERROR, "queue_log, m_unlock"));
	return (EXIT_SUCCESS);
}

void	print_queue_item(t_log queue, t_time start_time)
{
	const char	*status_msg[6] = {"has taken a fork", "is eating", \
					"is sleeping", "is thinking", "died",
					"all philosophers have eaten - simulation finished"};
	long	ts;

	ts = time_delta_msec(start_time, queue.log_time);
	if (queue.philo_status != ALL_EATEN)
		printf(FORMAT_STR, ts, queue.philo_id, status_msg[queue.philo_status]);
	else
		printf("%s\n", status_msg[queue.philo_status]);
}

void	print_queue(t_attr *attr)
{
	size_t	i;
	size_t	queue_size;
	t_log	*queue;
	t_time	start_time;

	queue = attr->log_queue;
	queue_size = attr->n_philo * QUEUE_SIZE;
	start_time = attr->start_time;
	i = 0;
	while (true)
	{
		if (queue[i].log_status == CREATED)
		{
			print_queue_item(queue[i], start_time);
			queue[i].log_status = PRINTED;
			if (++i == queue_size)
			 	i = 0;
		}
		if (attr->all_philo_alive == false)
			break ;
		usleep(20);
	}
}