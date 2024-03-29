/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bns.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/07 13:28:32 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/09/22 10:31:48 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BNS_H
# define PHILO_BNS_H

# include <stdlib.h>
# include <stdbool.h>

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

// alloc.c
bool		alloc_resources(t_sim *data);

// checker.c
void		*child_status_checker(void *arg);
bool		start_aux_threads(t_sim *data);
bool		join_aux_threads(t_sim *data);

// clean_up.c
void		clean_up(t_sim *data);

// error_handling.c
uint16_t	handle_err(char *msg, char *file_name, int line_no, t_sim *data);

// init.c
void		init_resources(t_sim *data);
void		init_philo(t_sim *data, uint16_t i);
sem_t		*gen_philo_sem(uint16_t philo_idx);

// parse.c
uint16_t	parse_args(int argc, char *argv[], t_sim *data);

// philo.c
bool		simulate(t_philo *philo);
void		drop_forks(t_philo *philo);

// printer.c
void		print_status(uint8_t status, t_time curr_time, t_philo *philo_data);

// process.c
void		create_child_processes(t_sim *data);
bool		wait_and_check_child_processes(t_sim *data);
void		kill_all_child_process(t_sim *data);

// semaphore.c
bool		semaphore_op(t_sim *data, uint8_t mode);
void		unlock_gen_semaphores(t_sim *data);

// string_util.c
uint32_t	ft_strlen(char *s);
char		*ft_itoa(int16_t num);
uint16_t	ft_isspace(int c);
uint16_t	ft_isdigit(int c);
int32_t		ft_atoi(char *str);

// time.c
t_time		get_time(void);
uint32_t	time_delta_msec(t_time t_old, t_time t_new);
void		precise_msleep(uint32_t duration);

#endif