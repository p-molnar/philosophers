/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_data_structures.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/31 20:55:27 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DATA_STRUCTURES_H
# define PHILO_DATA_STRUCTURES_H

# define MUTEX_SIZE 5
# define QUEUE_SIZE 1024

# include <stdint.h>

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;
typedef struct s_sim	t_sim;

typedef struct s_philo
{
	pthread_t	thread;
	t_time		last_ate;
	uint16_t	id;
	t_sim		*sim_data;
	uint16_t	eat_count;
	t_mutex		*fork[2];
	t_mutex		self;

}	t_philo;

typedef struct s_log
{
	uint16_t	philo_id;
	int16_t		status;
	uint32_t	timestamp;
}	t_log;

typedef struct s_sim
{
	int16_t		attr[5];

	t_mutex		mutex[MUTEX_SIZE];
	t_mutex		*fork;
	t_philo		*philo;
	pthread_t	thread[2];
	t_log		queue[QUEUE_SIZE];
	bool		is_running;
	t_time		start_time;
}	t_sim;

#endif
