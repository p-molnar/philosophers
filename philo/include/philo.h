/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:30:53 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/01 11:13:46 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>

# include <philo_data_structures.h>

# ifndef LOG_FMT
#  define LOG_FMT "%-d %d %s\n"
# endif

# define RGHT 1
# define LEFT 0
# define N_MAIN_STATUS 3

enum e_arg
{
	N_PHILO,
	T_DIE,
	T_EAT,
	T_SLEEP,
	N_EAT,
};

enum e_mutex
{
	SIM_INIT,
	LOG_RW,
	QUEUE_RW,
	UTIL_THREAD_START,
	SIM_RUN,
};

enum e_philo_status
{
	THINKING,
	EATING,
	SLEEPING,
	TAKING_FORK,
	DIED,
	UNDEFINED,
};

enum e_util_thread
{
	CHECKER,
	PRINTER,
};

# define INPUT_ERR_MSG "invalid input"
# define MUTEX_ERR_MSG "mutex error"
# define MALLOC_ERR_MSG "malloc error"
# define THREAD_ERR_MSG "thread error"

# define USAGE_MSG "usage: ./philo <philo count> <die duration> \
<eat duration> <sleep duration> [<min eat count by each philo>]\n"

// input.c
uint16_t	parse_args(int argc, char *argv[], t_sim *data);

// error_handling.c
uint16_t	thrw_err(char *err_msg, char *err_file, int err_line);
void		free_all(t_sim *data);
void		clean_up(t_sim *data);

// time.c
t_time		get_time(void);
uint32_t	time_delta_msec(t_time t_old, t_time t_new);
void		precise_sleep(long duration);

// init.c
void		init_resources(t_sim *data);

// thread.c
uint16_t	create_threads(t_sim *data);
uint16_t	join_threads(t_sim *data);

// mutex.c
uint16_t	init_mutexes(t_sim *data);
uint16_t	destroy_mutexes(t_sim *data);
void		unlock_all(t_sim *data);

// simulation.c
uint16_t	alloc_sim_resources(t_sim *data);

// philo.c
void		*simulation(void *arg);

// util_threads.c
void		*checker(void *arg);
void		*printer(void *arg);

// printer.c
void		log_status(t_philo *data, uint16_t status, t_time time);
void		print_status(t_log log);

#endif