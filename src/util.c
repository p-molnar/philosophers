/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 14:40:24 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/11 00:02:31 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
void	assign_forks(t_philo **philo, t_sim_attr *attr, size_t i)
{
	if (attr->philo_count == 1)
	{
		(*philo)[i].left_fork = &attr->fork_arr[i];
		(*philo)[i].right_fork = NULL;
	}
	else
	{
		if (i != (size_t)(attr->philo_count - 1))	
		{
			(*philo)[i].left_fork = &attr->fork_arr[i];
			(*philo)[i].right_fork = &attr->fork_arr[i + 1];	
		}
		else
		{
			(*philo)[i].left_fork = &attr->fork_arr[i];
			(*philo)[i].right_fork = &attr->fork_arr[0];
		}
	}
}

// protect and free mallocs!
int	set_up_sim_vars(t_philo **philo, t_sim_attr *attr)
{
	t_philo	*philo_arr;
	int		*fork_arr;
	size_t	i;

	philo_arr = malloc(sizeof(t_philo) * attr->philo_count);
	if (philo_arr == NULL)
		return (1);
	*philo = philo_arr;
	fork_arr = malloc(sizeof(int) * attr->philo_count);
	if (fork_arr == NULL)
		return (1);
	attr->fork_arr = fork_arr;
	i = 0;
	while (i < (size_t) attr->philo_count)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].state= UNDEFINED;
		(*philo)[i].eat_count = 0;
		(*philo)[i].sim_attr = attr;
		assign_forks(philo, attr, i);
		i++;
	}
	return (0);
}

int	create_threads(t_philo *philo_arr, t_sim_attr *attr)
{
	size_t	i;

	i = 0;
	pthread_mutex_init(&attr->mutex, NULL);
	gettimeofday(&attr->start_time, NULL);
	while (i < (size_t) attr->philo_count)
	{
		pthread_create(&(philo_arr[i].thread), NULL, (void *) &simulate_philo_life_circle,
						(void *) &philo_arr[i]);
		i++;
	}
	i = 0;
	while (i < (size_t) attr->philo_count)
	{
		pthread_join(philo_arr[i].thread, NULL);
		i++;
	}
	return (1);
	pthread_mutex_destroy(&attr->mutex);
}
