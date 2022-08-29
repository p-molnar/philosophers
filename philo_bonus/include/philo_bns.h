/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bns.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 13:28:32 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/08/29 23:55:20 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BNS_H
# define PHILO_BNS_H

# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/shm.h>
# include <pthread.h>

# include <philo_bns_data_structures.h>

# ifdef PRETTY_PRINT
#  define LOG_FMT "%-8d %-4d %s\n"
# else
#  define LOG_FMT "%-d %d %s\n"
# endif

# define INPUT_ERR_MSG "invalid input"
# define PROCESS_ERR_MSG "process error"
# define MALLOC_ERR_MSG "malloc error"
# define SEM_ERR_MSG "semaphore error"
# define SIG_ERR_MSG "semaphore error"

# define USAGE_MSG "usage: ./philo <philo count> <die duration> \
<eat duration> <sleep duration> [<min eat count by each philo>]\n"

// input.c
uint16_t	parse_args(int argc, char *argv[], t_sim *data);

// error_handling.c
uint16_t	thrw_err(char *err_msg, char *err_file, int err_line);
void		free_all(t_sim *data);

// time.c
t_time		get_time(void);
uint32_t	time_delta_msec(t_time t_old, t_time t_new);
void		precise_msleep(uint32_t duration);

// init.c
void		init_resources(t_sim *data);
void		init_philo(t_sim *data, uint16_t id);

// checker_thread.c
void		*checker_thread(void *arg);

// printer_thread.c
void		*printer_thread(void *arg);
void		log_status(t_philo *data, uint16_t status, t_time time);

// process.c
bool		create_child_processes(t_sim *data);
bool		wait_child_processes(t_sim *data);

// semaphore.c
bool		semaphore_op(t_sim *data, uint8_t mode);

// philo.c
bool		simulate(t_philo *philo);

// printer.c
bool		start_aux_threads(t_sim *data);
bool		join_aux_threads(t_sim *data);

// alloc.c
bool		alloc_resources(t_sim *data);
#endif