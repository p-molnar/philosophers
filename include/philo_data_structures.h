/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_data_structures.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/15 00:02:00 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DATA_STRUCTURES_H
# define PHILO_DATA_STRUCTURES_H

# include <stddef.h>
# include <philo_consts.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>


typedef struct s_sim_attr
{
	int		philo_count;
	int		die_duration;
	int		eat_duration;
	int		sleep_duration;
	int		required_eat_count;
	int		*fork_arr;
	struct timeval	start_time;
	pthread_mutex_t	mutex;
}	t_sim_attr;

typedef struct s_philo
{
	size_t		id;
	int			state;
	int			*left_fork;
	int			*right_fork;
	int			eat_count;	
	int			last_time_eaten;
	pthread_t	thread;
	t_sim_attr	*sim_attr;
}	t_philo;


#endif
