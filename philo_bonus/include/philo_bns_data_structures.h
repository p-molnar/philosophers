/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bns_data_structures.h                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/15 11:56:46 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BNS_DATA_STRUCTURES_H
# define PHILO_BNS_DATA_STRUCTURES_H

# define QUEUE__SIZE 1024
# define STATUS__COUNT 3

# include <stdint.h>

enum e_sem_option
{
	OPEN,
	CLOSE,
	UNLINK
};

enum e_lock_options
{
	LOCK,
	UNLOCK
};

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
	PRINTER_LOCK,
	CHECKER_LOCK,
	FORK,
	SEM__COUNT,
};

enum e_philo_status
{
	THINKING,
	EATING,
	SLEEPING,
	TAKING_FORK,
	DIED,
	FED,
	ALL_FED,
	UNDEFINED = -1,
};

enum e_util_thread
{
	CHECKER,
	PRINTER,
	THREAD__COUNT,
};

typedef struct timeval	t_time;
typedef struct s_sim	t_sim;

typedef struct s_sem_attr
{
	const char	*name;
	int16_t		init_val;
}	t_sem_attr;

typedef struct s_philo
{
	uint16_t	id;
	uint8_t		status;
	t_time		last_ate;
	t_sim		*sim_data;
	uint16_t	eat_count;
	uint16_t	forks_in_hand;
	bool		is_fed;
	sem_t		*self_lock;

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
	sem_t		*generic_sem[SEM__COUNT];
	sem_t		**philo_sem;
	t_philo		philo;
	pid_t		*child_pid_arr;
	t_log		queue[QUEUE__SIZE];
	pthread_t	thread[THREAD__COUNT];
	pthread_t	*checker_thread;
	t_time		start_time;
}	t_sim;

typedef struct s_data_coll
{
	t_sim		*data;
	int16_t		philo_pid;
	uint16_t	philo_idx;
}	t_data_coll;

#endif
