/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_data_structures.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/30 13:44:12 by pmolnar       ########   odam.nl         */
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

typedef struct s_log
{
	int		log_status;
	t_time	log_time;
	int		philo_status;
	size_t	philo_id;
}	t_log;

typedef struct s_sim_data
{
	int			n_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			min_n_eat;
	bool		all_philo_alive;
	pthread_t	checker;
	pthread_t	printer;
	t_log		*log_queue;
	t_time		start_time;
	t_mutex		queue_lock;
	t_mutex		monitoring_lock;
	t_mutex		start_lock;
	t_mutex		**forks;
}	t_sim_data;

typedef struct s_philo
{
	size_t		id;
	int			status;
	int			n_eat;	
	t_time		last_time_eaten;
	t_time		last_action_time;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	pthread_t	thread;
	t_sim_data		*sim_attr;
}	t_philo;

#endif
