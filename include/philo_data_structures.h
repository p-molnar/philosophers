/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_data_structures.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/07 17:41:28 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_DATA_STRUCTURES_H
# define PHILO_DATA_STRUCTURES_H

# include <stddef.h>
# include <philo_consts.h>
# include <sys/time.h>


typedef struct s_philo
{
	size_t	id;
	int		state;
}	t_philo;

typedef struct s_data
{
	t_philo	*philo_arr;
	size_t	philo_count;
	size_t	die_duration;
	size_t	eat_duration;
	size_t	sleep_duration;
	size_t	required_eat_count;
	struct timeval	start_time;
	struct timeval	curr_time;
}	t_data;


#endif
