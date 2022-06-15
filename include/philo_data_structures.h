/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_data_structures.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/16 01:06:40 by pmolnar       ########   odam.nl         */
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
typedef size_t			t_timestamp;

typedef struct s_attr
{
	size_t	philo_count;
	size_t	die_duration;
	size_t	eat_duration;
	size_t	sleep_duration;
	size_t	required_eat_count;
	int		*fork_arr;
	char	**status_msg;
	t_time	start_time;
	t_mutex	mutex;
}	t_attr;

typedef struct s_philo
{
	size_t		id;
	int			state;
	int			*left_fork;
	int			*right_fork;
	size_t	eat_count;	
	size_t		last_time_eaten;
	pthread_t	thread;
	t_attr		*g_attr;
}	t_philo;


#endif
