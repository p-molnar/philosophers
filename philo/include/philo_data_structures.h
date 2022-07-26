/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_data_structures.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/26 13:53:38 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DATA_STRUCTURES_H
# define PHILO_DATA_STRUCTURES_H

# define MUTEX_SIZE 1

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	pthread_t	thread;
	uint16_t	id;
	t_mutex		*m;
}	t_philo;

typedef struct s_sim
{
	int			attr[5];
	t_mutex		mutex[MUTEX_SIZE];
	t_mutex		*fork;
	t_philo		*philo;
	pthread_t	thread[2];
}	t_sim;

#endif
