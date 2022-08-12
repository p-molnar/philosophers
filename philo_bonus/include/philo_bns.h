/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bns.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 13:28:32 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/12 14:10:12 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BNS_H
# define PHILO_BNS_H

# include <sys/time.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>

# include <philo_bns_data_structures.h>

# ifdef PRETTY_PRINT
#  define LOG_FMT "%-8d %-4d %s\n"
# else
#  define LOG_FMT "%-d %d %s\n"
# endif

# define INPUT_ERR_MSG "invalid input"
# define PROCESS_ERR_MSG "process error"
# define MALLOC_ERR_MSG "malloc error"
# define THREAD_ERR_MSG "thread error"

# define USAGE_MSG "usage: ./philo <philo count> <die duration> \
<eat duration> <sleep duration> [<min eat count by each philo>]\n"

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

enum e_philo_status
{
	THINKING,
	EATING,
	SLEEPING,
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

// input.c
uint16_t	parse_args(int argc, char *argv[], t_sim *data);

// error_handling.c
uint16_t	thrw_err(char *err_msg, char *err_file, int err_line);
void		free_all(t_sim *data);

// time.c
t_time		get_time(void);
uint32_t	time_delta_msec(t_time t_old, t_time t_new);
void		precise_sleep(long duration);

// init.c
void		init_resources(t_sim *data);

// checker_thread.c
void		*checker_thread(void *arg);

// printer_thread.c
void		*printer_thread(void *arg);
void		log_status(t_philo *data, uint16_t status, t_time time);

// process.c
bool		start_processes(t_sim *data);

// alloc.c
bool		alloc_resources(t_sim *data);
#endif