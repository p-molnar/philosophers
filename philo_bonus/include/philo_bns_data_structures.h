/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bns_data_structures.h                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/04 22:39:40 by pmolnar       ########   odam.nl         */
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
	LOG_RW,
	QUEUE_RW,
	DIE,
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
	sem_t		*self;

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
	t_philo		philo;
	int32_t		*pid_arr;
	t_log		queue[QUEUE__SIZE];
	pthread_t	thread[THREAD__COUNT];
	t_time		start_time;
	bool		sim_running;
	bool		*philo_exited;
}	t_sim;

#endif
