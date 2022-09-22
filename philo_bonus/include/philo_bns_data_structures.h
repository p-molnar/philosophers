/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bns_data_structures.h                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:19:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 10:35:52 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BNS_DATA_STRUCTURES_H
# define PHILO_BNS_DATA_STRUCTURES_H

# define STATUS__COUNT 3

# include <stdint.h>
# include <semaphore.h>

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
	THREAD__COUNT,
};

typedef struct timeval	t_time;
typedef struct s_sim	t_sim;

typedef struct s_sem_ht
{
	const char	*name;
	int16_t		init_val;
}	t_sem_ht;

typedef struct s_philo
{
	uint16_t	id;
	uint8_t		status;
	t_time		last_ate;
	t_sim		*sim_data;
	uint16_t	eat_count;
	uint16_t	n_forks_in_hand;
	sem_t		*self_lock;

}	t_philo;

typedef struct s_sim
{
	int16_t		attr[ARG__COUNT];
	sem_t		*generic_sem[SEM__COUNT];
	sem_t		**philo_sem;
	t_philo		philo;
	pid_t		*child_pid_arr;
	pthread_t	thread[THREAD__COUNT];
	pthread_t	*checker_thread;
	t_time		start_time;
}	t_sim;

#endif
