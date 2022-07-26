/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:30:53 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/26 13:12:07 by pmolnar       ########   odam.nl         */
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

# ifndef FORMAT_STR
#  define FORMAT_STR "%zu %zu %s\n"
# endif 

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
	START,
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
int		parse_args(int argc, char *argv[], t_sim *data);

// input_util.c
int		ft_atoi(char *str);

// error_handling.c
int		thrw_err(char *err_msg, char *err_file, int err_line);

// time.c
t_time	get_time(void);
long	time_delta_msec(t_time t1, t_time t2);
void	precise_sleep(long duration);

// thread.c
int		create_threads(t_sim *data);
int		join_threads(t_sim *data);

// mutex.c
int		init_mutexes(t_sim *data);
int		destroy_mutexes(t_sim *data);

// simulation.c
int		alloc_sim_resources(t_sim *data);

// philo.c
int		simulation(t_philo *philo);

// util_threads.c
int		checker(t_sim *data);
int		printer(t_sim *data);
#endif