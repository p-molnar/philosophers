/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:30:53 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/30 15:08:31 by pmolnar       ########   odam.nl         */
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
int		parse_args(int argc, char *argv[], t_sim_data *data);

// input_util.c
int		ft_atoi(char *str);

// error_handling.c
int		error_handler(int err_code, char *func_name);

// util.c
int		set_up_simulation(t_philo **philo_arr, t_sim_data *attr);

// simulation.c
int		close_simulation(t_philo *philo_arr, t_sim_data *attr);
int		launch_simulation(t_philo *philo_arr, t_sim_data *attr);

// philosopher.c
void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	put_down_forks(t_philo *philo);

// monitoring.c
void	check_status(t_philo *philo_arr);

// time.c
t_time	get_time(void);
long	time_delta_msec(t_time t1, t_time t2);
void	precise_sleep(long duration);

// printing.c
void	queue_log(t_sim_data *attr, t_philo *philo);
void	print_queue(t_sim_data *attr);

#endif