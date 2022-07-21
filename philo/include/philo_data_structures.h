/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_data_structures.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/22 00:35:15 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DATA_STRUCTURES_H
# define PHILO_DATA_STRUCTURES_H

# include <stddef.h>
# include <philo_consts.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
}	t_philo;

typedef struct s_data
{
	int		arg[5];
	t_philo	*philo;
}	t_data;

#endif
