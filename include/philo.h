/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:30:53 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/29 12:35:42 by pmolnar       ########   odam.nl         */
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
int		error_handler(int err_code, char *func_name);

// util.c
int		set_up_simulation(t_philo **philo_arr, t_attr *attr);

// simulation.c
int		close_simulation(t_philo *philo_arr, t_attr *attr);
int		launch_simulation(t_philo *philo_arr, t_attr *attr);

// philosopher.c
int		philo_eat(t_philo *philo);
int		philo_think(t_philo *philo);
int		philo_sleep(t_philo *philo);

// philosopher_util.c
int		pick_up_forks(t_philo *philo);
int		pick_up_fork(t_philo *philo, t_mutex *fork);
int		put_down_forks(t_philo *philo);
t_log	*create_log(t_philo *philo, int status);

// monitoring.c
void	status_monitoring(t_philo *philo_arr);

// time.c
t_time	get_time(void);
long	time_delta_msec(t_time t1, t_time t2);
void	precise_sleep(long duration);

// printing.c
int	queue_log(t_attr *attr, t_philo *philo);
void	print_queue(t_attr *attr);

#endif