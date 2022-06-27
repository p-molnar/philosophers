#include <philo.h>

void	add_log_to_queue(t_attr *attr, t_log *log)
{
	static size_t;
	pthread_mutex_lock(&attr->queue_lock);
	attr->queue[log->status][log->philo_id - 1] = *log;
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

void	print_queue(t_attr *attr)
{
	size_t	i;
	size_t	n_philo;

	n_philo = sim_attr->n_philo;
	i = 0;
	while (true)
	{
				print_queue_item(queue[i], sim_attr->start_time, i);
				queue[i]
				i++;
			if (i == n_philo * 64)
				i = 0;
		}
		else
		{
			break;
		}
	}
}