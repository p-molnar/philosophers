/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 09:46:18 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/21 18:56:46 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_philo(t_philo *philo, t_sim_data *attr, size_t i)
{
	philo->id = i + 1;
	philo->status = UNDEFINED;
	philo->n_eat = 0;
	philo->sim_attr = attr;
	philo->left_fork = attr->forks[i % attr->n_philo];
	philo->right_fork = attr->forks[(i + 1) % attr->n_philo];
	i++;
}

int	init_simulation_attributes(t_sim_data **attr)
{
	t_mutex	**fork_arr;
	size_t	i;

	fork_arr = malloc((*attr)->n_philo * sizeof(t_mutex *));
	if (fork_arr == NULL)
		return (error_handler(MALLOC_ERROR, "init_simulation_attributes"));
	i = 0;
	while (i < (size_t)(*attr)->n_philo)
		fork_arr[i++] = malloc(sizeof(t_mutex));
	(*attr)->forks = fork_arr;
	(*attr)->all_philo_alive = true;
	return (EXIT_SUCCESS);
}

static int	set_up_philos(t_philo **philo, t_sim_data *attr)
{
	t_philo	*philo_arr;
	size_t	i;

	philo_arr = malloc(attr->n_philo * sizeof(t_philo));
	if (philo_arr == NULL)
		return (error_handler(MALLOC_ERROR, "set_up_philos"));
	i = 0;
	while (i < (size_t) attr->n_philo)
	{
		init_philo(&philo_arr[i], attr, i);
		i++;
	}
	*philo = philo_arr;
	return (EXIT_SUCCESS);
}

int	set_up_queue(t_sim_data *attr)
{
	size_t	n_philo;
	size_t	i;

	n_philo = attr->n_philo;
	attr->log_queue = malloc(QUEUE_SIZE * n_philo * sizeof(t_log));
	if (attr->log_queue == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < QUEUE_SIZE * n_philo)
		attr->log_queue[i++].log_status = NO_CONTENT;
	return (0);
}

int	set_up_simulation(t_philo **philo, t_sim_data *attr)
{
	if (init_simulation_attributes(&attr))
		return (EXIT_FAILURE);
	if (set_up_philos(philo, attr))
	{
		free (attr->forks);
		return (EXIT_FAILURE);
	}
	if (set_up_queue(attr))
	{
		free (attr->forks);
		free (philo);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
