/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:30:53 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/27 14:46:22 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <philo_data_structures.h>

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>

# include <pthread.h>

# ifndef FORMAT_STR
#  define FORMAT_STR "%zu %zu %s\n"
# endif 

// input.c
int		parse_args(int argc, char *argv[], t_attr *data);

// input_util.c
int		ft_atoi(char *str);

// error_handling.c
int		error_handler(int err_code);

// util.c
int		set_up_simulation(t_philo **philo_arr, t_attr *attr);
int		launch_simulation(t_philo *philo_arr, t_attr *attr);

// philosopher.c
int		philo_eat(t_philo *philo);
int		philo_think(t_philo *philo);
int		philo_sleep(t_philo *philo);

// philosopher_util.c
void	pick_up_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);
void	print_status(t_philo *philo);
void	create_log(t_philo *philo, t_log *log, int status);

// monitoring.c
void	philo_checker(t_philo *philo_arr);

// time.c
t_time	get_time(void);
long	time_delta_msec(t_time t1, t_time t2);
void	psleep(long duration);

// printing.c
void	add_log_to_queue(t_attr *attr, t_log *log);
void	print_queue(t_attr *sim_attr);

#endif