#include <philo.h>

void	add_log_to_queue(t_attr *attr, t_log *log)
{
	static size_t i;

	pthread_mutex_lock(&attr->queue_lock);
	attr->queue[i] = log;
	if (++i == (size_t) (attr->n_philo * 64 - 1))
		i = 0;
	pthread_mutex_unlock(&attr->queue_lock);
}

void	print_queue_item(t_log *queue, t_time start_time, int item)
{
	const char	*status_msg[5] = {"has taken a fork", "is eating", \
								"is sleeping", "is thinking", "died"};
	long	ts;

	ts = time_delta_msec(start_time, queue->time);	
	printf("item :%d, %zu philo %zu %s\n", item, ts, queue->philo_id, status_msg[queue->status]);
}

void	print_queue(t_attr *sim_attr)
{
	size_t	i;
	size_t	n_philo;
	t_log	**queue;

	n_philo = sim_attr->n_philo;
	queue = sim_attr->queue;
	i = 0;
	while (true)
	{
		usleep(500);
		if (queue != NULL)
		{
			if (queue[i] != NULL)
			{
				print_queue_item(queue[i], sim_attr->start_time, i);
				free(queue[i]);
				queue[i] = NULL;
			}
			if (++i == n_philo * 64 - 1)
				i = 0;
		}
		else
		{
			break;
		}
	}
}