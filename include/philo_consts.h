/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_consts.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 16:40:19 by pmolnar       #+#    #+#                 */
/*   Updated: 2022/06/16 00:07:38 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_CONSTS_H
# define PHILO_CONSTS_H

enum e_status {
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	UNDEFINED,
};

enum {
	INVALID_INPUT=1,
	MEM_ERROR=2,
};

enum {
	AVAILABLE=0,
	IN_USE=1,
};
#endif