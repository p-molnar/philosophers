/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:30:53 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/16 00:14:56 by pmolnar       ########   odam.nl         */
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
bool	parse_input(int argc, char *argv[], t_attr *data);

// input_util.c
int	ft_atoi(char *str);

// error_handling.c
int	error_handling(int err_code);

// util.c
int	init_vars(t_philo **philo_arr, t_attr *attr);
int	create_threads(t_philo *philo_arr, t_attr *attr);

// philosopher.c
void	run_philo_life_cycle(t_philo *philo);

// philosopher_util.c
void	pick_up_fork(t_philo *philo, int *fork);
void	put_down_fork(int *fork);
void	print_status(t_philo *philo, t_timestamp ts);
size_t	gen_time_stamp(t_time time);

#endif