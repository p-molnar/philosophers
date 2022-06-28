/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 09:46:18 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/28 12:47:13 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_philo(t_philo *philo, t_attr *attr, size_t i)
{
	philo->id = i + 1;
	philo->status = UNDEFINED;
	philo->n_eat = 0;
	philo->g_attr = attr;
	philo->left_fork = attr->fork_arr[i % attr->n_philo];
	philo->right_fork = attr->fork_arr[(i + 1) % attr->n_philo];
	i++;
}

int	init_simulation_attributes(t_attr **attr)
{
	t_mutex	**mutex_arr;
	size_t	i;

	mutex_arr = malloc((*attr)->n_philo * sizeof(t_mutex *));
	if (mutex_arr == NULL)
		return (error_handler(MALLOC_ERROR));
	i = 0;
	while (i < (size_t)(*attr)->n_philo)
		mutex_arr[i++] = malloc(sizeof(t_mutex));
	(*attr)->fork_arr = mutex_arr;
	(*attr)->all_philo_alive = true;
	return (EXIT_SUCCESS);
}

static int	set_up_philos(t_philo **philo, t_attr *attr)
{
	t_philo	*philo_arr;
	size_t	i;

	philo_arr = malloc(attr->n_philo * sizeof(t_philo));
	if (philo_arr == NULL)
		return (error_handler(MALLOC_ERROR));
	i = 0;
	while (i < (size_t) attr->n_philo)
	{
		init_philo(&philo_arr[i], attr, i);
		i++;
	}
	*philo = philo_arr;
	return (EXIT_SUCCESS);
}

int	set_up_queue(t_attr *attr)
{
	size_t	n_philo;
	size_t	i;

	n_philo = attr->n_philo;
	attr->queue_arr = malloc(QUEUE_SIZE * n_philo * sizeof(t_log *));
	if (attr->queue_arr == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	while (i < QUEUE_SIZE * n_philo)
		attr->queue_arr[i++] = NULL;
	return (0);
}

int	set_up_simulation(t_philo **philo, t_attr *attr)
{
	if (init_simulation_attributes(&attr))
		return (EXIT_FAILURE);
	if (set_up_philos(philo, attr))
	{
		free (attr->fork_arr);
		return (EXIT_FAILURE);
	}
	if (set_up_queue(attr))
	{
		free (attr->fork_arr);
		free (philo);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
