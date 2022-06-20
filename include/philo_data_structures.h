/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_data_structures.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/20 13:12:02 by pmolnar       ########   odam.nl         */
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

typedef struct s_attr
{
	int		philo_count;
	int		die_duration;
	int		eat_duration;
	int		sleep_duration;
	int		min_eat_count;
	t_mutex	**fork_arr;
	t_mutex	**eat_lock_arr;
	char	**status_msg;
	bool	all_philo_alive;
	t_time	start_time;
}	t_attr;

typedef struct s_philo
{
	size_t		id;
	t_time		last_time_eaten;
	int			status;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_mutex		*eat_lock;
	int			eat_count;	
	pthread_t	thread;
	t_attr		*g_attr;
}	t_philo;

#endif
