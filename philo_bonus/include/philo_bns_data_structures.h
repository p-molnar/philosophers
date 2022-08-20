/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bns_data_structures.h                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/20 13:42:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BNS_DATA_STRUCTURES_H
# define PHILO_BNS_DATA_STRUCTURES_H

# define QUEUE_SIZE 1024

# include <stdint.h>

enum e_arg
{
	N_PHILO,
	T_DIE,
	T_EAT,
	T_SLEEP,
	N_EAT,
	ARG__COUNT
};

enum e_name_sem
{
	START_LOCK,
	FORK,
	SEM__COUNT,	
};

enum e_philo_status
{
	THINKING,
	EATING,
	SLEEPING,
	STATUS__COUNT,
	TAKING_FORK,
	DIED,
	ALL_FED,
	UNDEFINED = -1,
};

enum e_util_thread
{
	CHECKER,
	PRINTER,
};

typedef struct timeval	t_time;
typedef struct s_sim	t_sim;

typedef struct s_sem_ht
{
	char		*name;
	uint16_t	init_val;

}	t_sem_ht;

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
	int16_t		attr[ARG__COUNT];
	sem_t		*sem[SEM__COUNT];
	t_sem_ht	sem_attr[SEM__COUNT];
	t_philo		*philo;
	uint32_t	*philo_pid;
	t_log		queue[QUEUE_SIZE];
	bool		is_running;
	t_time		start_time;
}	t_sim;

#endif
