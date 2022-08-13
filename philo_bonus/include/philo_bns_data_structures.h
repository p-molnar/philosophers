/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bns_data_structures.h                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/13 23:55:30 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BNS_DATA_STRUCTURES_H
# define PHILO_BNS_DATA_STRUCTURES_H

# define SEM_SIZE 1
# define N_ATTR 5
# define QUEUE_SIZE 1024

# include <stdint.h>

typedef struct timeval	t_time;
typedef struct s_sim	t_sim;

typedef struct s_philo
{
	t_time		last_ate;
	uint16_t	id;
	t_sim		*sim_data;
	uint16_t	eat_count;

}	t_philo;

typedef struct s_log
{
	uint16_t	philo_id;
	int16_t		status;
	uint32_t	timestamp;
}	t_log;

typedef struct s_sim
{
	int16_t		attr[N_ATTR];
	sem_t		*sem[SEM_SIZE];
	t_philo		*philo;
	t_log		queue[QUEUE_SIZE];
	bool		is_running;
	t_time		start_time;
}	t_sim;

#endif
