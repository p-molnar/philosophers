/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_consts.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 16:40:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/07/22 00:50:25 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_CONSTS_H
# define PHILO_CONSTS_H

enum e_arg
{
	N_PHILO,
	T_DIE,
	T_EAT,
	T_SLEEP,
	N_EAT
};

enum e_error_msg {
	INVALID_INPUT=1,
	MALLOC_ERROR,
	MUTEX_ERROR,
	THREAD_ERROR,
};
#endif