/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:30:53 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/14 22:32:07 by pmolnar       ########   odam.nl         */
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
bool	parse_input(int argc, char *argv[], t_sim_attr *data);

// input_util.c
int	ft_atoi(char *str);

// error_handling.c
int	error_handling(int err_code);

// util.c
int	set_up_sim_vars(t_philo **philo_arr, t_sim_attr *attr);
int	create_threads(t_philo *philo_arr, t_sim_attr *attr);

// philosopher.c
void	run_philo_life_cycle(t_philo *philo);

#endif