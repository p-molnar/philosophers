/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 09:46:18 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/20 14:01:18 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_philo(t_philo *philo, t_attr *attr, size_t i)
{
	philo->id = i + 1;
	philo->status = UNDEFINED;
	philo->eat_count = 0;
	philo->g_attr = attr;
	philo->left_fork = attr->fork_arr[i % attr->philo_count];
	philo->right_fork = attr->fork_arr[(i + 1) % attr->philo_count];
	i++;
}

// int	init_lock_arr(t_attr **attr)
// {
// 	t_mutex	**locks;
// 	size_t	i;

// 	locks = malloc(((*attr)->philo_count / 2) * sizeof(t_mutex *));
// 	i = 0;
// 	while (i < (size_t)(*attr)->philo_count)
// 		locks[i++] = malloc(sizeof(t_mutex));
// 	(*attr)->eat_lock_arr = locks;
// }

// protect malloc
int	init_simulation_attributes(t_attr **attr)
{
	t_mutex	**mutex_arr;
	size_t	i;

	mutex_arr = malloc((*attr)->philo_count * sizeof(t_mutex *));
	if (mutex_arr == NULL)
		return (error_handler(MALLOC_ERROR));
	i = 0;
	while (i < (size_t)(*attr)->philo_count)
		mutex_arr[i++] = malloc(sizeof(t_mutex));
	(*attr)->fork_arr = mutex_arr;
	(*attr)->all_philo_alive = true;
	return (EXIT_SUCCESS);
}

static int	set_up_philos(t_philo **philo, t_attr *attr)
{
	t_philo	*philo_arr;
	size_t	i;

	philo_arr = malloc(attr->philo_count * sizeof(t_philo));
	if (philo_arr == NULL)
		return (error_handler(MALLOC_ERROR));
	i = 0;
	while (i < (size_t) attr->philo_count)
	{
		init_philo(&philo_arr[i], attr, i);
		i++;
	}
	*philo = philo_arr;
	return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
}
