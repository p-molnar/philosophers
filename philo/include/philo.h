/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 12:30:53 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/22 00:33:46 by pmolnar       ########   odam.nl         */
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
int		parse_args(int argc, char *argv[], t_data *data);

// input_util.c
int		ft_atoi(char *str);

// error_handling.c
int		error_handler(int err_code, char *func_name);

// time.c
t_time	get_time(void);
long	time_delta_msec(t_time t1, t_time t2);
void	precise_sleep(long duration);

#endif