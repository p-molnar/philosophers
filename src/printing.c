#include <philo.h>

void	queue_log(t_attr *attr, t_log *log)
{
	pthread_mutex_lock(&attr->queue_lock);
	static size_t i;
	size_t queue_size;

	queue_size = attr->n_philo * QUEUE_SIZE;
	attr->queue_arr[i++] = log;
	if (i == queue_size)
		i = 0;
	pthread_mutex_unlock(&attr->queue_lock);
}

void	print_queue_item(t_log *queue, t_time start_time)
{
	const char	*status_msg[5] = {"has taken a fork", "is eating", \
								"is sleeping", "is thinking", "died"};
	long	ts;

	ts = time_delta_msec(start_time, queue->time);	
	printf(FORMAT_STR, ts, queue->philo_id, status_msg[queue->status]);
}

void	print_queue(t_attr *attr)
{
	size_t	i;
	size_t	queue_size;
	t_log	**queue_arr;
	t_time	start_time;

	queue_arr = attr->queue_arr;
	queue_size = attr->n_philo * QUEUE_SIZE;
	start_time = attr->start_time;
	i = 0;
	while (true)
	{
		if (queue_arr[i] != NULL)
		{
			print_queue_item(queue_arr[i], start_time);
			free(queue_arr[i]);
			queue_arr[i] = NULL;
			if (++i == queue_size)
			 	i = 0;
			if (attr->all_philo_alive == false)
				break ;
		}
		usleep(20);
	}
}