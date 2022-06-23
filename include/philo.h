/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:30:53 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/23 23:15:29 by pmolnar       ########   odam.nl         */
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
int	philo_eat(t_philo *philo);
int	philo_think(t_philo *philo);
int	philo_sleep(t_philo *philo);

// philosopher_util.c
void	pick_up_fork(t_philo *philo, t_mutex *fork);
void	put_down_fork(t_mutex *fork);
void	print_status(t_philo *philo);

// die_checker.c
void	philo_checker(t_philo *philo_arr);

// time.c
t_time	get_time(void);
long	time_delta_usec(t_time t1, t_time t2);
void	psleep(long usec);

#endif